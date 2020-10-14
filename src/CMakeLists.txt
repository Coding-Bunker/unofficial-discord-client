find_package(
  Qt5
  COMPONENTS Quick Network
  REQUIRED)

add_executable(unofficial-discord-client
    core/Types.hpp
    core/User.hpp
    core/User.cpp
    core/Guild.hpp
    core/Guild.cpp

    handlers/Authenticator.hpp
    handlers/Authenticator.cpp
    handlers/Requester.hpp
    handlers/Requester.cpp

    DiscordApi/DiscordAPI.hpp

    gui/GuildsModel.hpp
    gui/GuildsModel.cpp

    app/main.cpp
    app/Application.hpp
    app/Application.cpp

    qml/qml.qrc
)

target_link_libraries(unofficial-discord-client PRIVATE Qt5::Quick Qt5::Network)
