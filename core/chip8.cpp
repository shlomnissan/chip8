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
    uint16_t in = ram[cpu.pc] << 8 | ram[cpu.pc + 1];
    cpu.pc += 2;

    switch (in >> 12) {
        case 0x0000:
            switch(in & 0x00FF) {
                case 0xE0: // 00E0
                    instruction::OP_CLS(&display);
                    break;
                case 0xEE: // 00EE
                    instruction::OP_RET(&cpu);
                    break;
            }
            break;
        case 0x1000:
            instruction::OP_JP(in, &cpu);
            break;
        case 0x2000:
            instruction::OP_CALL(in, &cpu);
            break;
        case 0x3000:
            instruction::OP_SE_BYTE(in, &cpu);
            break;
        case 0x4000:
            instruction::OP_SNE_BYTE(in, &cpu);
            break;
        case 0x5000:
            instruction::OP_SN_XY(in, &cpu);
            break;
        case 0x6000:
            instruction::LD_VX_BYTE(in, &cpu);
            break;
        case 0x7000:
            instruction::ADD_VX_BYTE(in, &cpu);
            break;
    }
}
