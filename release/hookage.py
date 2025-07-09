import subprocess
import sys
import os
from abc import ABC, abstractmethod
from tkinter import filedialog
import shutil

HEADER = """  _   _  ___   ___  _  __    _    ____ _____ 
 | | | |/ _ \ / _ \| |/ /   / \  / ___| ____|
 | |_| | | | | | | | ' /   / _ \| |  _|  _|  
 |  _  | |_| | |_| | . \  / ___ \ |_| | |___ 
 |_| |_|\___/ \___/|_|\_\/_/   \_\____|_____|
                                             """

ABOUT = """A cool thing that will help you enjoy all the splendor of hooks, even if you are a fucking vegetable.
P.S. I want to thank my parents (and in particular you, mom, for this apple pie that inspires feats), 
the creators of easy hook, the authors of win api and the Hoegaarden brewing company).
P.P.S. Blizzard go fuck yourself"""


class OperationError(Exception):
    def __init__(self):
        super().__init__("Invalid operation")


class AbstractMenu(ABC):
    def __init__(self, title: str):
        self.title = title
        self.menu_items = []
        self.initialise()

    @abstractmethod
    def initialise(self):
        pass

    def update_menu_items(self):
        pass

    def item_text(self, item: 'MenuItem'):
        return "%s" % item.description

    def item_line(self, index: int, item: 'MenuItem'):
        return "%s. %s" % (index, self.item_text(item))

    def display(self):
        repeat: bool = True
        while repeat:
            self.update_menu_items()
            print()
            print(self.title)
            for i in range(0, len(self.menu_items)):
                if self.menu_items[i].isVisible:
                    print(self.item_line(i, self.menu_items[i]))

            inp = input("Select Option: ")
            try:
                menu_item = self.menu_items[int(inp)]
                if menu_item.isVisible:
                    repeat = menu_item.run()
                else:
                    raise OperationError()
            except ValueError:
                print("Invalid option, you need to enter a number.", inp)
                repeat = True
            except IndexError:
                print("Invalid option. Option {0} doesn't exist.".format(inp))
                repeat = True
            except OperationError:
                print("Invalid option. Option at {0} is hidden.".format(inp))
                repeat = True

    def add_menu_item(self, menu_item: 'MenuItem'):
        if not self.menu_items.__contains__(menu_item):
            self.menu_items.append(menu_item)
        else:
            raise ValueError("Menu item with id {0} already exists!.".format(menu_item.id))

    def add_hidden_menu_item(self, menu_item: 'MenuItem'):
        self.add_menu_item(menu_item.hide())

    def show_menu_item(self, item_id: int):
        try:
            menu_item = MenuItem(item_id)
            index = self.menu_items.index(menu_item)
            self.menu_items[index].show()
        except ValueError:
            print("Error showing menu item. Menu item with ID {0} hasn't been added to this menu.".format(item_id))

    def hide_menu_item(self, item_id: int):
        try:
            menu_item = MenuItem(item_id)
            index = self.menu_items.index(menu_item)
            self.menu_items[index].hide()
        except ValueError:
            print("Error hiding menu item. Menu item with ID {0} hasn't been added to this menu.".format(item_id))


class MenuItem:
    def __init__(self, id: int, description: str = "", action: callable(None) = None, menu: AbstractMenu = None):
        self.id: int = id
        self.description: str = description
        self.action = action
        self.menu: AbstractMenu = menu
        self.isExitOption: bool = False
        self.isVisible: bool = True

    def hide(self) -> 'MenuItem':
        self.isVisible = False
        return self

    def show(self) -> 'MenuItem':
        self.isVisible = True
        return self

    def set_as_exit_option(self) -> 'MenuItem':
        self.isExitOption = True
        return self

    def run(self) -> bool:
        if self.action is not None:
            self.action()
        elif self.menu is not None:
            self.menu.display()

        return not self.isExitOption

    def __eq__(self, other):
        if isinstance(other, self.__class__):
            return self.id == other.id
        else:
            return False

    def __ne__(self, other):
        return not self.__eq__(other)


def ask_directory():
    return filedialog.askdirectory(initialdir=os.getcwd())


def read_log_level():
    value = input("Input log level, it must be one of [" + ", ".join(LOG_LEVELS.keys()) + "]:")
    if value not in LOG_LEVELS:
        print("Invalid log level")
        return None
    return LOG_LEVELS[value]


LOG_LEVELS = {
    "debug": 0,
    "info": 1,
    "fail": 2
}

VARIABLES = {
    "Hooks": None,
    "Logs": None,
    "LogLevel": 0
}

READERS = {
    "Hooks": ask_directory,
    "Logs": ask_directory,
    "LogLevel": read_log_level
}


def set_variables():
    key = input("Input variable to change, available variables " + ", ".join(VARIABLES.keys()) + ":")
    if key not in VARIABLES:
        print("Unknown variable")
        return
    value = READERS[key]()
    VARIABLES[key] = value


HOOK_TEMPLATE = "hook_template"
CMAKE = "CMakeLists.txt"
CMAKE_SOURCE = HOOK_TEMPLATE + "/" + CMAKE
PROJECT_NAME = "%name"
BINARIES = "bin"


def create_hook_project():
    try:
        if not os.path.isdir(HOOK_TEMPLATE):
            print("Template project not found")
            return
        name = input("Input project name:")
        directory = filedialog.askdirectory()
        if directory == "":
            return
        if not os.path.isdir(directory):
            print("Bad directory")
            return
        target = os.path.join(directory, name)
        shutil.copytree(os.path.join(HOOK_TEMPLATE, "body"), target, copy_function=shutil.copy, dirs_exist_ok=False)
        cmake = open(CMAKE_SOURCE, "r")
        cmake_target = open(os.path.join(target, CMAKE), "w")
        for line in cmake.readlines():
            cmake_target.write(line.replace(PROJECT_NAME, name))
        cmake_target.close()
        cmake.close()
        print("Project successfully created")
    except OSError as e:
        print(e)


LOADER_CONFIG = "bin/loader.cfg"
TRANSLATIONS = {
    "Hooks": "hookDir",
    "Logs": "logDir",
    "LogLevel": "logLvl"
}


def ask_file():
    return filedialog.askopenfilename()


INJECTOR = "Injector.exe"


def inject_hooks():
    if not os.path.isfile(LOADER_CONFIG):
        data = []
        for key in TRANSLATIONS.keys():
            value = VARIABLES[key]
            if value is None:
                print("Value '" + key + "' is unset")
                return
            data.append(TRANSLATIONS[key] + "=" + str(value))
        config = open(LOADER_CONFIG, "w")
        for line in data:
            config.write(line + "\n")
        config.close()
    file_path = ask_file()
    if file_path == "":
        return
    cur_path = os.getcwd()
    subprocess.run([os.path.join(cur_path, BINARIES, INJECTOR), file_path], cwd=os.path.join(cur_path, BINARIES))


class MenuImpl(AbstractMenu):
    def __init__(self):
        super().__init__("What do u want?")

    def initialise(self):
        self.add_menu_item(MenuItem(0, "Exit").set_as_exit_option())
        self.add_menu_item(MenuItem(1, "About", lambda: print(ABOUT)))
        self.add_menu_item(MenuItem(2, "Set variables", set_variables))
        self.add_menu_item(MenuItem(3, "Create hook project", create_hook_project))
        self.add_menu_item(MenuItem(4, "Inject hooks", inject_hooks))


def main(args):
    print(HEADER)
    MenuImpl().display()


if __name__ == '__main__':
    main(sys.argv)
