# ===== ===== ===== Find packages ===== ===== =====
find_package(
  Qt6
  COMPONENTS Quick QuickControls2 Network
  REQUIRED)

# ===== ===== ===== Create executable ===== ===== =====
set(HEADER_LIST
    "${unofficial-discord-client_SOURCE_DIR}/src/core/Types.hpp"
    "${unofficial-discord-client_SOURCE_DIR}/src/core/User.hpp"
    "${unofficial-discord-client_SOURCE_DIR}/src/core/Guild.hpp"
    "${unofficial-discord-client_SOURCE_DIR}/src/core/Channel.hpp"
    "${unofficial-discord-client_SOURCE_DIR}/src/core/Message.hpp"
    "${unofficial-discord-client_SOURCE_DIR}/src/handlers/Authenticator.hpp"
    "${unofficial-discord-client_SOURCE_DIR}/src/handlers/Requester.hpp"
    "${unofficial-discord-client_SOURCE_DIR}/src/DiscordApi/DiscordAPI.hpp"
    "${unofficial-discord-client_SOURCE_DIR}/src/gui/GuildsModel.hpp"
    "${unofficial-discord-client_SOURCE_DIR}/src/gui/ChannelsModel.hpp"
    "${unofficial-discord-client_SOURCE_DIR}/src/gui/MessagesModel.hpp"
    "${unofficial-discord-client_SOURCE_DIR}/src/app/Application.hpp")

set(SRC_LIST
    "${unofficial-discord-client_SOURCE_DIR}/src/core/Guild.cpp"
    "${unofficial-discord-client_SOURCE_DIR}/src/core/User.cpp"
    "${unofficial-discord-client_SOURCE_DIR}/src/core/Channel.cpp"
    "${unofficial-discord-client_SOURCE_DIR}/src/core/Message.cpp"
    "${unofficial-discord-client_SOURCE_DIR}/src/handlers/Authenticator.cpp"
    "${unofficial-discord-client_SOURCE_DIR}/src/handlers/Requester.cpp"
    "${unofficial-discord-client_SOURCE_DIR}/src/gui/GuildsModel.cpp"
    "${unofficial-discord-client_SOURCE_DIR}/src/gui/ChannelsModel.cpp"
    "${unofficial-discord-client_SOURCE_DIR}/src/gui/MessagesModel.cpp"
    "${unofficial-discord-client_SOURCE_DIR}/src/app/Application.cpp")

add_executable(
  unofficial-discord-client
  ${SRC_LIST} ${HEADER_LIST}
  "${unofficial-discord-client_SOURCE_DIR}/src/app/main.cpp"
  "${unofficial-discord-client_SOURCE_DIR}/src/qml/qml.qrc")

target_link_libraries(unofficial-discord-client
                      PRIVATE Qt6::Quick Qt6::QuickControls2 Qt6::Network)
