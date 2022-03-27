// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "chip8.h"
#include "types.h"
#include "parser.h"
#include "instructions.h"

using namespace c8;

void Chip8::Reset() {
    ram.Reset();
    input.Reset();
    display.ClearScreen();

    program_loaded = false;
    cpu.regs = {0};
    cpu.stack = {0};
    cpu.I = 0;
    cpu.pc = Memory::kStartAddress;
    cpu.sp = 0;
    cpu.t_delay = 0;
    cpu.t_sound = 0;

    rand.seed(time(nullptr));
}

void Chip8::ReadProgram(std::string_view buffer) {
    ram.SaveProgram(buffer);
    program_loaded = true;
}

void Chip8::SetKey(int key, int value) {
    input[key] = value;
}

bool Chip8::ProgramLoaded() const {
    return program_loaded;
}

uint8_t Chip8::DisplayAt(int loc) {
    return display[loc];
}

void Chip8::UpdateDelayTimer() {
    if (cpu.t_delay > 0) {
        --cpu.t_delay;
    }
}

bool Chip8::UpdateSoundTimer() {
    if (cpu.t_sound > 0) {
        --cpu.t_sound;
    }
    return cpu.t_sound > 0;
}

void Chip8::Tick() {
    Opcode opcode = ram[cpu.pc] << 8 | ram[cpu.pc + 1];
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
        case Instruction::ADD_VX_VY: return ADD_VX_VY(opcode, &cpu);
        case Instruction::SUB_VX_VY: return SUB_VX_VY(opcode, &cpu);
        case Instruction::SHR_VX: return SHR_VX(opcode, &cpu);
        case Instruction::SUBN_VX_VY: return SUBN_VX_VY(opcode, &cpu);
        case Instruction::SHL_VX: return SHL_VX(opcode, &cpu);
        case Instruction::SNE_VX_VY: return SNE_VX_VY(opcode, &cpu);
        case Instruction::LD_I: return LD_I(opcode, &cpu);
        case Instruction::JMP_V0: return JP_V0(opcode, &cpu);
        case Instruction::RND: return RND(opcode, &cpu, &rand);
        case Instruction::DRW: return DRW(opcode, &cpu, &display, &ram);
        case Instruction::SKP: return SKP(opcode, &cpu, &input);
        case Instruction::SKNP: return SKNP(opcode, &cpu, &input);
        case Instruction::LD_VX_DT: return LD_VX_DT(opcode, &cpu);
        case Instruction::LD_VX_K: return LD_VX_K(opcode, &cpu, &input);
        case Instruction::LD_DT: return LD_DT(opcode, &cpu);
        case Instruction::LD_ST: return LD_ST(opcode, &cpu);
        case Instruction::ADD_I_VX: return ADD_I_VX(opcode, &cpu);
        case Instruction::LD_F_VX: return LD_F_VX(opcode, &cpu);
        case Instruction::LD_B_VX: return LD_B_VX(opcode, &cpu, &ram);
        case Instruction::LD_I_VX: return LD_I_VX(opcode, &cpu, &ram);
        case Instruction::LD_VX_I: return LD_VX_I(opcode, &cpu, &ram);

        default:
            throw bad_opcode(opcode);
    }
}
