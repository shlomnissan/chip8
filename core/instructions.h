// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef CHIP8_INSTRUCTIONS_H
#define CHIP8_INSTRUCTIONS_H

#include "cpu.h"

namespace c8::instruction {

// Annn - Load address nnn to register I
void OP_LD_I(int in, Cpu& cpu) {
    cpu.I = in & 0x0FFF;
}

}

#endif  // CHIP8_INSTRUCTIONS_H
