# unofficial-discord-client

[![Build Linux](https://github.com/Coding-Bunker/unofficial-discord-client/actions/workflows/build-linux.yml/badge.svg)](https://github.com/Coding-Bunker/unofficial-discord-client/actions/workflows/build-linux.yml)
[![Build W10](https://github.com/Coding-Bunker/unofficial-discord-client/actions/workflows/build-w10.yml/badge.svg)](https://github.com/Coding-Bunker/unofficial-discord-client/actions/workflows/build-w10.yml)
[![Build MacOS](https://github.com/Coding-Bunker/unofficial-discord-client/actions/workflows/build-macos.yml/badge.svg)](https://github.com/Coding-Bunker/unofficial-discord-client/actions/workflows/build-macos.yml)

# Description

The main purpose of this client is to be a desktop application fast and simple to use in order to replace the official application. Is a community project and anyone can help with issues, feedback or coding. The purpose is to learn how manage desktop application in C++ with Qt framework using public API provided by discord.

## Build

- Qt min version 6.0.0
- CMake min version 3.16.3

```bash
cmake -S . -B build
cmake --build build 
```

## Run

```bash
build/src/bin/unofficial-discord-client 
```

## Features

- [x] Settings (Ctrl + S)
- [ ] News and other types of channels
  - Voice channels require Qt Multimedia for audio handling, which has not been ported to Qt 6 yet: https://github.com/Coding-Bunker/unofficial-discord-client/issues/45
- [ ] Mentions
- [ ] Attachments
- [ ] Reactions
- [ ] Custom emojis
