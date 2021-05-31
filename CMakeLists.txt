cmake_minimum_required(VERSION 3.16.3)

project(
  unofficial-discord-client
  VERSION 0.1
  DESCRIPTION "Discord unofficial desktop application"
  LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")
if (MSVC)
    add_compile_options(/W4 /wd4711 -experimental:external
        -external:anglebrackets -external:W0)
else()
set(CMAKE_CXX_FLAGS_INIT
    "-Werror"
    "-Wall"
    "-Wextra"
    "-Wpedantic"
    "-Warray-bounds"
    "-Wdouble-promotion"
    "-Weffc++"
    "-Wno-c++98-compat"
    "-Wextra"
    "-Wimplicit-fallthrough"
    "-Winit-self"
    "-Wfloat-equal"
    "-Wformat=2"
    "-Wmissing-include-dirs"
    "-Wno-unused-const-variable"
    "-Wno-unused-function"
    "-Wnull-dereference"
    "-Wparentheses"
    "-Wpedantic"
    "-Wshift-overflow"
    "-Wshadow"
    "-Wstrict-aliasing=1"
    "-Wstrict-overflow=5"
    "-Wtautological-compare"
    "-Wuninitialized")
endif()

add_subdirectory(src)
