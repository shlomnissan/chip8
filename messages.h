// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef CHIP8_MESSAGES_H
#define CHIP8_MESSAGES_H

namespace c8::message {

constexpr auto FlagRomHelp = "Specify a relative path to a Chip-8 program";
constexpr auto FlagCyclesHelp = "Set Chip-8 CPU cycles per second";
constexpr auto InvalidPath = "Specify a valid relative path to a Chip-8 program";
constexpr auto InvalidRom = "Unable to read Chip-8 program";
constexpr auto FailedToInit = "Unable to initialize window";

}

#endif  // CHIP8_MESSAGES_H
