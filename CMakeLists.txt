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

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
  set(CMAKE_CXX_FLAGS "/W4 /wd4711 /wd4577 /experimental:external \
        /external:anglebrackets /external:W0")
else()
  set(CMAKE_CXX_FLAGS
      "-Wall -Wextra -Wpedantic -Wdouble-promotion -Wimplicit-fallthrough \
        -Winit-self -Wfloat-equal -Wformat=2 -Wmissing-include-dirs \
        -Wnull-dereference -Wshadow -Wstrict-overflow=5 -Wtautological-compare")
endif()

add_subdirectory(src)
