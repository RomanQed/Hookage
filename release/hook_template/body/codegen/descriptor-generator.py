import os
import re
import sys

HOOK_PATTERN = r"HOOK\((\S+),\s*(\S+)\)"
FUNC_PATTERN = r"(\S+)\([^\(\)]{0,}\)\s*(?:;|{)\s*$"
DESCRIPTOR = "DESCRIPTOR"
DESCRIPTOR_ADD = "DESCRIPTOR_ADD(%lib, %func, %hook)"
DESCRIPTOR_FILE = "descriptor.cpp"
INCLUDE = "#include \"Api.h\""
PREPROC = "#"
INCLUDE_PROC = "#include"
HEADERS = "include"
SOURCES = "src"


def make_add(lib, func, hook):
    return DESCRIPTOR_ADD \
        .replace("%lib", '"' + lib + '"') \
        .replace("%func", '"' + func + '"') \
        .replace("%hook", hook)


def make_descriptor(entries):
    ret = DESCRIPTOR + " {\n"
    for entry in entries:
        line = make_add(*entry)
        ret += " " * 4 + line + ";\n"
    ret += "}\n"
    return ret


def walkDirectory(directory, consumer):
    found = os.walk(directory)
    for cortege in found:
        root = cortege[0]
        for file in cortege[2]:
            path = os.path.join(root, file)
            path = path.replace(directory, '')
            if path.startswith('\\'):
                path = path[1:]
            consumer(path)


def clearLine(line):
    return line \
        .replace('{', '') \
        .replace(';', '') \
        .strip()


def extractHook(line):
    found = re.search(HOOK_PATTERN, line)
    if found is None:
        return None
    lib = found.group(1).replace('"', "")
    func = found.group(2).replace('"', "")
    return lib + ":" + func, [lib, func], line.replace(found.group(0), "")


def extractFunc(line):
    found = re.search(FUNC_PATTERN, line)
    if found is None:
        return None
    func = found.group(1)
    declaration = clearLine(line)
    return func, declaration


def processFile(file, buffer: dict, deps: set):
    pending = None
    temp = set()
    flag = False
    for line in file.readlines():
        line = line.strip()
        if line.startswith(INCLUDE_PROC):
            temp.add(line)
            continue

        if line.startswith(PREPROC):
            continue

        if pending is not None:
            found = extractFunc(line)
            if found is None:
                continue
            buffer[pending][0].append(found[0])
            buffer[pending].append(found[1])
            flag = True
            pending = None
            continue

        found = extractHook(line)
        if found is None:
            continue

        flag = True

        key = found[0]

        if key in buffer:
            continue

        buffer[key] = [found[1]]
        line = found[2]
        found = extractFunc(line)
        if found is None:
            pending = key
            continue
        pending = None

        flag = True
        buffer[key][0].append(found[0])
        buffer[key].append(found[1])

    if flag:
        for entry in temp:
            deps.add(entry)


def make_descriptor_file(file, buffer: dict, deps: set):
    for dep in deps:
        file.write(dep + '\n')
    file.write('\n')
    entries = []
    for entry in buffer.values():
        entries.append(entry[0])
        file.write(entry[1] + ';\n')
    descriptor = make_descriptor(entries)
    file.write('\n')
    file.write(descriptor)


def main(args):
    # Init
    current = args[1]
    buffer = dict()
    deps = {INCLUDE}

    # Declare walker
    def walker(path):
        # Skip all non-sources dirs
        if not (path.startswith(HEADERS) or path.startswith(SOURCES)):
            return
        # Process found file
        file = open(path, 'r')
        processFile(file, buffer, deps)
        file.close()

    # Walk on files to collect hook entries
    walkDirectory(current, walker)

    # Generate descriptor
    out = open(args[2], 'w')
    make_descriptor_file(out, buffer, deps)
    out.close()


if __name__ == '__main__':
    main(sys.argv)
