cmake_minimum_required(VERSION 3.5)

project(unofficial-discord-client LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets Network REQUIRED)

add_executable(unofficial-discord-client
    main.cpp
    Overwrite.hpp
    Channel.hpp
    MainWindow.cpp  MainWindow.hpp   MainWindow.ui
    DiscordApi/DiscordAPI.hpp DiscordApi/Requests.hpp
    DiscordApi/Constructs.hpp
)

target_link_libraries(unofficial-discord-client PRIVATE Qt5::Widgets Qt5::Network)
