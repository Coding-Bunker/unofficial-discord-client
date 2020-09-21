find_package(Qt5 COMPONENTS Quick Network REQUIRED)

add_executable(unofficial-discord-client
    main.cpp
    qml/qml.qrc

    Application.hpp
    Application.cpp

    Authenticator.hpp
    Authenticator.cpp

    DiscordApi/DiscordAPI.hpp
)

target_link_libraries(unofficial-discord-client PRIVATE Qt5::Quick Qt5::Network)
