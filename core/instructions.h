// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef CHIP8_INSTRUCTIONS_H
#define CHIP8_INSTRUCTIONS_H

#include "cpu.h"
#include "display.h"

namespace c8::instruction {

uint16_t GetAddress(int in) { return in & 0x0FFF; }
uint16_t GetByte(int in) { return (in & 0x00FF); }
uint16_t GetX(int in) { return (in & 0x0F00) >> 8; }
uint16_t GetY(int in) { return (in & 0x00F0) >> 4; }

// 00E0 - Clear screen
void OP_CLS(Display* display) {
    display->ClearScreen();
}

// 00EE - Return from a subroutine
void OP_RET(Cpu* cpu) {
   cpu->pc = cpu->stack[--cpu->sp];
}

// 1nnn - Jump to address nnn
void OP_JP(uint16_t in, Cpu* cpu) {
    cpu->pc = GetAddress(in);
}

// 2nnn - Call subroutine at address nnn
void OP_CALL(uint16_t in, Cpu* cpu) {
    cpu->stack[cpu->sp++] = cpu->pc;
    cpu->pc = GetAddress(in);
}

// 3xkk - Skip next instruction if V[x] == kk
void OP_SE_BYTE(uint16_t in, Cpu* cpu) {
    if (cpu->registers[GetX(in)] == GetByte(in)) {
        cpu->pc += 2;
    }
}

// Annn - Load address nnn to register I
void OP_LD_I(uint16_t in, Cpu* cpu) {
    cpu->I = GetAddress(in);
}

}

#endif  // CHIP8_INSTRUCTIONS_H
