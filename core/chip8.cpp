// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <sstream>

#include "chip8.h"
#include "parser.h"
#include "types.h"
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
    size_op opcode = ram[cpu.pc] << 8 | ram[cpu.pc + 1];
    auto instruction = parse(opcode);

    cpu.pc += 2; // increment program counter

    using namespace instruction;
    switch (instruction) {
        case Instruction::CLS: return CLS(&display);
        case Instruction::RET: return RET(&cpu);
        case Instruction::JMP: return JMP(opcode, &cpu);
        case Instruction::CALL: return CALL(opcode, &cpu);
        case Instruction::SE_VX_KK: return SE_VX_KK(opcode, &cpu);
        case Instruction::SNE_VX_KK: return SNE_VX_KK(opcode, &cpu);
        case Instruction::SE_VX_VY: return SE_VX_VY(opcode, &cpu);
        case Instruction::LD_VX_KK: return LD_VX_KK(opcode, &cpu);
        case Instruction::ADD_VX_KK: return ADD_VX_KK(opcode, &cpu);
        case Instruction::LD_VX_VY: return LD_VX_VY(opcode, &cpu);
        case Instruction::OR_VX_VY: return OR_VX_VY(opcode, &cpu);
        case Instruction::AND_VX_VY: return AND_VX_VY(opcode, &cpu);
        case Instruction::XOR_VX_VY: return XOR_VX_VY(opcode, &cpu);
        default:
            std::stringstream message;
            message << "Unknown opcode 0x" << std::hex << opcode;
            throw std::runtime_error(message.str());
    }
}
