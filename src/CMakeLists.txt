find_package(
  Qt6
  COMPONENTS Quick QuickControls2 Network
  REQUIRED)

add_executable(
  unofficial-discord-client
  core/Types.hpp
  core/User.hpp
  core/User.cpp
  core/Guild.hpp
  core/Guild.cpp
  core/Channel.hpp
  core/Channel.cpp
  core/Message.hpp
  core/Message.cpp
  handlers/Authenticator.hpp
  handlers/Authenticator.cpp
  handlers/Requester.hpp
  handlers/Requester.cpp
  DiscordApi/DiscordAPI.hpp
  gui/GuildsModel.hpp
  gui/GuildsModel.cpp
  gui/ChannelsModel.hpp
  gui/ChannelsModel.cpp
  gui/MessagesModel.hpp
  gui/MessagesModel.cpp
  app/main.cpp
  app/Application.hpp
  app/Application.cpp
  qml/qml.qrc)

target_link_libraries(unofficial-discord-client
                      PRIVATE Qt6::Quick Qt6::QuickControls2 Qt6::Network)
