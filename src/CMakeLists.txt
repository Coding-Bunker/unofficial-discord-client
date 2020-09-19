find_package(Qt5 COMPONENTS Quick Network REQUIRED)

add_executable(unofficial-discord-client
    main.cpp
    qml/qml.qrc

    Application.hpp
    Application.cpp

    Authenticator.hpp
    Authenticator.cpp

    Requester.hpp
    Requester.cpp
    DiscordApi/DiscordAPI.hpp

    User.hpp
    User.cpp
    Guild.hpp
    Guild.cpp

    GuildsModel.hpp
    GuildsModel.cpp
)

target_link_libraries(unofficial-discord-client PRIVATE Qt5::Quick Qt5::Network)
