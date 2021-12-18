// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef CHIP8_CPU_H
#define CHIP8_CPU_H

#include <array>
#include <vector>
#include <cinttypes>

#include "memory.h"

namespace c8 {

class Cpu {
public:
    void Reset();
    void ReadProgram(const std::vector<char>& buffer);

private:
    std::array<uint8_t, 0x10> registers = {0};
    std::array<uint16_t, 0x10> stack = {0};

    uint16_t I = {0};
    uint16_t pc = {kStartAddress}; // program counter
    uint16_t sp = {0}; // stack pointer

    uint8_t t_delay = 0; // delay timer
    uint8_t t_sound = 0; // sound timer

    Memory ram;
};

}

#endif  // CHIP8_CPU_H
