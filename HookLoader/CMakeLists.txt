cmake_minimum_required(VERSION 3.23)
project(HookLoader)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_STATIC_LIBRARY_PREFIX "")

set(CXX_FLAGS "-Waddress \
-Warray-bounds=1 \
-Wbool-compare \
-Wbool-operation \
-Wc++11-compat \
-Wc++14-compat \
-Wcatch-value \
-Wchar-subscripts \
-Wcomment \
-Wformat \
-Wformat-overflow \
-Wformat-truncation \
-Wint-in-bool-context \
-Winit-self \
-Wlogical-not-parentheses \
-Wmaybe-uninitialized \
-Wmemset-elt-size \
-Wmemset-transposed-args \
-Wmisleading-indentation \
-Wmissing-attributes \
-Wmultistatement-macros \
-Wnarrowing \
-Wnonnull \
-Wnonnull-compare \
-Wopenmp-simd \
-Wparentheses \
-Wreorder \
-Wrestrict \
-Wreturn-type \
-Wsequence-point \
-Wsign-compare \
-Wsizeof-pointer-div \
-Wsizeof-pointer-memaccess \
-Wstrict-aliasing \
-Wstrict-overflow=1 \
-Wswitch \
-Wtautological-compare \
-Wtrigraphs \
-Wuninitialized \
-Wunknown-pragmas \
-Wvolatile-register-var \
-Wclobbered \
-Wignored-qualifiers \
-Wimplicit-fallthrough=3 \
-Wmissing-field-initializers \
-Wtype-limits \
-Wuninitialized \
-Wshift-negative-value")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_FLAGS} -O0 -g3")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${CXX_FLAGS} -static-libgcc -static-libstdc++ -O2 -static -DNDEBUG")

# Libs
include_directories(${CMAKE_SOURCE_DIR}/libs/include)
find_library(EasyHook EasyHook64 "${CMAKE_SOURCE_DIR}/libs/bin")

# Sources
include_directories(include)
include_directories(include/export)
file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")
file(GLOB_RECURSE HEADERS RELATIVE ${CMAKE_SOURCE_DIR} "include/*.h")
file(GLOB_RECURSE CXX_HEADERS RELATIVE ${CMAKE_SOURCE_DIR} "include/*.hpp")

# Combine
add_library(HookLoader SHARED ${HEADERS} ${CXX_HEADERS} ${SOURCES})


# Link
target_link_libraries(HookLoader ${EasyHook})