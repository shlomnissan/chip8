// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "chip8.h"
#include "instructions.h"

using namespace c8;

void Chip8::Reset() {
    ram.Reset();
    program_loaded = false;

    cpu.registers = {0};
    cpu.stack = {0};
    cpu.I = 0;
    cpu.pc = Memory::kStartAddress;
    cpu.sp = 0;
    cpu.t_delay = 0;
    cpu.t_sound = 0;
}

void Chip8::ReadProgram(std::string_view buffer) {
    ram.SaveProgram(buffer.data());
    program_loaded = true;
}

bool Chip8::ProgramLoaded() const {
    return program_loaded;
}

void Chip8::Tick() {
    auto in = ram[cpu.pc] << 8 | ram[cpu.pc + 1];
    auto opcode = in >> 12;
}
