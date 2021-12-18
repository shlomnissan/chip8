// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "cpu.h"

void c8::Cpu::Reset() {
    registers = {0};
    stack = {0};
    I = 0;
    pc = kStartAddress;
    sp = 0;
    t_delay = 0;
    t_sound = 0;

    // TODO: reset memory
    // TODO: load sprites
}

void c8::Cpu::ReadProgram(const std::vector<char> &data) {
    // TODO: read program into memory
}
