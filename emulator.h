// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef CHIP8_EMULATOR_H
#define CHIP8_EMULATOR_H

#include "core/rom.h"

namespace c8 {

class Emulator {
public:
    void Reset();
    void LoadRom(const c8::Rom& rom);
    void Start();
};

}

#endif  // CHIP8_EMULATOR_H
