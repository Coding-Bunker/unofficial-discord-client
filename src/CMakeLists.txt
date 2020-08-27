find_package(Qt5 COMPONENTS Widgets Network REQUIRED)

add_executable(unofficial-discord-client
    main.cpp
    MainWindow.cpp MainWindow.hpp MainWindow.ui
    DiscordApi/DiscordAPI.hpp
    DiscordApi/Constructs.hpp
    Authenticator.cpp Authenticator.hpp
)

target_link_libraries(unofficial-discord-client PRIVATE Qt5::Widgets Qt5::Network)
