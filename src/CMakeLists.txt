# ===== ===== ===== Find packages ===== ===== =====
find_package(
  Qt6
  COMPONENTS Quick QuickControls2 Network
  REQUIRED)

# ===== ===== ===== Create executable ===== ===== =====
set(HEADER_LIST
    "${PROJECT_SOURCE_DIR}/src/core/Types.hpp"
    "${PROJECT_SOURCE_DIR}/src/core/User.hpp"
    "${PROJECT_SOURCE_DIR}/src/core/Guild.hpp"
    "${PROJECT_SOURCE_DIR}/src/core/Channel.hpp"
    "${PROJECT_SOURCE_DIR}/src/core/Message.hpp"
    "${PROJECT_SOURCE_DIR}/src/core/Settings.hpp"
    "${PROJECT_SOURCE_DIR}/src/core/Role.hpp"
    "${PROJECT_SOURCE_DIR}/src/core/Embed.hpp"
    "${PROJECT_SOURCE_DIR}/src/core/Attachment.hpp"
    "${PROJECT_SOURCE_DIR}/src/handlers/Authenticator.hpp"
    "${PROJECT_SOURCE_DIR}/src/handlers/Requester.hpp"
    "${PROJECT_SOURCE_DIR}/src/DiscordApi/DiscordAPI.hpp"
    "${PROJECT_SOURCE_DIR}/src/gui/GuildsModel.hpp"
    "${PROJECT_SOURCE_DIR}/src/gui/ChannelsModel.hpp"
    "${PROJECT_SOURCE_DIR}/src/gui/MessagesModel.hpp"
    "${PROJECT_SOURCE_DIR}/src/gui/SettingsModel.hpp"
    "${PROJECT_SOURCE_DIR}/src/gui/ImageRender.hpp"
    "${PROJECT_SOURCE_DIR}/src/app/Application.hpp")

set(SRC_LIST
    "${PROJECT_SOURCE_DIR}/src/core/Guild.cpp"
    "${PROJECT_SOURCE_DIR}/src/core/User.cpp"
    "${PROJECT_SOURCE_DIR}/src/core/Channel.cpp"
    "${PROJECT_SOURCE_DIR}/src/core/Message.cpp"
    "${PROJECT_SOURCE_DIR}/src/core/Settings.cpp"
    "${PROJECT_SOURCE_DIR}/src/core/Role.cpp"
    "${PROJECT_SOURCE_DIR}/src/core/Attachment.cpp"
    "${PROJECT_SOURCE_DIR}/src/core/Embed.cpp"
    "${PROJECT_SOURCE_DIR}/src/handlers/Authenticator.cpp"
    "${PROJECT_SOURCE_DIR}/src/handlers/Requester.cpp"
    "${PROJECT_SOURCE_DIR}/src/gui/GuildsModel.cpp"
    "${PROJECT_SOURCE_DIR}/src/gui/ChannelsModel.cpp"
    "${PROJECT_SOURCE_DIR}/src/gui/MessagesModel.cpp"
    "${PROJECT_SOURCE_DIR}/src/gui/SettingsModel.cpp"
    "${PROJECT_SOURCE_DIR}/src/gui/ImageRender.cpp"
    "${PROJECT_SOURCE_DIR}/src/app/Application.cpp")

add_executable(
  unofficial-discord-client
  ${SRC_LIST} ${HEADER_LIST} "${PROJECT_SOURCE_DIR}/src/app/main.cpp"
  "${PROJECT_SOURCE_DIR}/src/qml/qml.qrc")

target_link_libraries(unofficial-discord-client
                      PRIVATE Qt6::Quick Qt6::QuickControls2 Qt6::Network)
