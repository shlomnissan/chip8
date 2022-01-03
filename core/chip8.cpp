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
    size_i in = ram[cpu.pc] << 8 | ram[cpu.pc + 1];
    cpu.pc += 2;

    switch (in >> 12) {
        case 0x0000:
            switch(in & 0x00FF) {
                case 0xE0: // 00E0
                    instruction::CLS(&display);
                    break;
                case 0xEE: // 00EE
                    instruction::RET(&cpu);
                    break;
            }
            break;
        case 0x1000:
            instruction::JMP(in, &cpu);
            break;
        case 0x2000:
            instruction::CALL(in, &cpu);
            break;
        case 0x3000:
            instruction::SE_VX_KK(in, &cpu);
            break;
        case 0x4000:
            instruction::SNE_VX_KK(in, &cpu);
            break;
        case 0x5000:
            instruction::SE_VX_VY(in, &cpu);
            break;
        case 0x6000:
            instruction::LD_VX_KK(in, &cpu);
            break;
        case 0x7000:
            instruction::ADD_VX_KK(in, &cpu);
            break;
        case 0x8000:
            switch(in & 0x000F) {
                case 0x00:
                    instruction::LD_VX_VY(in, &cpu);
                    break;
                case 0x01:
                    instruction::OR_VX_VY(in, &cpu);
                    break;
                case 0x02:
                    instruction::AND_VX_VY(in, &cpu);
                    break;
                case 0x03:
                    instruction::XOR_VX_VY(in, &cpu);
                    break;
                case 0x04:
                    // TODO: impl.
                    break;
                case 0x05:
                    // TODO: impl.
                    break;
                case 0x06:
                    // TODO: impl.
                    break;
                case 0x07:
                    // TODO: impl.
                    break;
                case 0x0E:
                    // TODO: impl.
                    break;
            }
            break;
    }
}
