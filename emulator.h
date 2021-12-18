// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef CHIP8_EMULATOR_H
#define CHIP8_EMULATOR_H

#include "core/cpu.h"
#include "core/rom.h"

namespace c8 {

class Emulator {
public:
    void LoadRom(const Rom& rom);
    void Start();

private:
    Cpu cpu;
};

}

#endif  // CHIP8_EMULATOR_H
