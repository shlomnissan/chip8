// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef CHIP8_INSTRUCTIONS_H
#define CHIP8_INSTRUCTIONS_H

#include "cpu.h"
#include "display.h"

using size_i = uint16_t; // size of instruction

namespace c8::instruction {

size_i GetAddress(int in) { return in & 0x0FFF; }

size_i GetByte(int in) { return (in & 0x00FF); }

size_i GetX(int in) { return (in & 0x0F00) >> 8; }

size_i GetY(int in) { return (in & 0x00F0) >> 4; }

// 00E0 - Clear screen
void CLS(Display *display) {
    display->ClearScreen();
}

// 00EE - Return from a subroutine
void RET(Cpu *cpu) {
    cpu->pc = cpu->stack[--cpu->sp];
}

// 1nnn - Jump to address nnn
void JMP(size_i in, Cpu *cpu) {
    cpu->pc = GetAddress(in);
}

// 2nnn - Call subroutine at address nnn
void CALL(size_i in, Cpu *cpu) {
    cpu->stack[cpu->sp++] = cpu->pc;
    cpu->pc = GetAddress(in);
}

// 3xkk - Skip next instruction if V[x] == kk
void SE_VX_KK(size_i in, Cpu *cpu) {
    if (cpu->registers[GetX(in)] == GetByte(in)) {
        cpu->pc += 2;
    }
}

// 4xkk - Skip next instruction if V[x] != kk
void SNE_VX_KK(size_i in, Cpu *cpu) {
    if (cpu->registers[GetX(in)] != GetByte(in)) {
        cpu->pc += 2;
    }
}

// 5xy0 - Skip next instruction if Vx = Vy
void SE_VX_VY(size_i in, Cpu *cpu) {
    if (cpu->registers[GetX(in)] == cpu->registers[GetY(in)]) {
        cpu->pc += 2;
    }
}

// 6xkk - Puts the value kk into register Vx.
void LD_VX_KK(size_i in, Cpu *cpu) {
    cpu->registers[GetX(in)] = GetByte(in);
}

// 7xkk - Adds the value kk to the value of register Vx
void ADD_VX_KK(size_i in, Cpu *cpu) {
    cpu->registers[GetX(in)] += GetByte(in);
}

// 8xy0 - Puts the value of register Vy in register Vx.
void LD_VX_VY(size_i in, Cpu *cpu) {
    cpu->registers[GetX(in)] = cpu->registers[GetY(in)];
}

// 8xy1 - Set Vx = Vx OR Vy
void OR_VX_VY(size_i in, Cpu *cpu) {
    cpu->registers[GetX(in)] |= cpu->registers[GetY(in)];
}

// 8xy2 - Set Vx = Vx AND Vy
void AND_VX_VY(size_i in, Cpu *cpu) {
    cpu->registers[GetX(in)] &= cpu->registers[GetY(in)];
}

// 8xy3 - Set Vx = Vx XOR Vy
void XOR_VX_VY(size_i in, Cpu *cpu) {
    cpu->registers[GetX(in)] ^= cpu->registers[GetY(in)];
}

}

#endif  // CHIP8_INSTRUCTIONS_H