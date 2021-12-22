// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "cpu.h"
#include <iostream>

using namespace c8;

void Cpu::Reset() {
    ram.Reset();
    program_loaded = false;

    registers = {0};
    stack = {0};
    I = 0;
    pc = Memory::kStartAddress;
    sp = 0;
    t_delay = 0;
    t_sound = 0;
}

void Cpu::ReadProgram(const std::vector<char> &buffer) {
    ram.SaveProgram(buffer.data(), buffer.size());
    program_loaded = true;
}

bool Cpu::ProgramLoaded() const {
    return program_loaded;
}