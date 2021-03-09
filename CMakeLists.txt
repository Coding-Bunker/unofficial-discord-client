cmake_minimum_required(VERSION 3.16.3)

project(unofficial-discord-client
    VERSION 0.1
    DESCRIPTION "Discord unofficial desktop application"
    LANGUAGES CXX)


set(CMAKE_INCLUDE_CURRENT_DIR ON)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")


add_subdirectory(src)
