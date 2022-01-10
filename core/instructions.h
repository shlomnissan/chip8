// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef CHIP8_INSTRUCTIONS_H
#define CHIP8_INSTRUCTIONS_H

#include "display.h"
#include "types.h"

namespace c8::instruction {

// 00E0 - Clear the display.
void CLS(Display *display) {
    display->ClearScreen();
}

// 00EE - Return from a subroutine.
void RET(Cpu *cpu) {
    cpu->pc = cpu->stack[--cpu->sp];
}

// 1nnn - Jump to location nnn.
void JMP(Opcode in, Cpu *cpu) {
    cpu->pc = in.address();
}

// 2nnn - Call subroutine at nnn.
void CALL(Opcode in, Cpu *cpu) {
    cpu->stack[cpu->sp++] = cpu->pc;
    cpu->pc = in.address();
}

// 3xkk - Skip next instruction if Vx = kk.
void SE_VX_KK(Opcode in, Cpu *cpu) {
    if (cpu->registers[in.x()] == in.byte()) {
        cpu->pc += 2;
    }
}

    // 4xkk - Skip next instruction if Vx != kk.
void SNE_VX_KK(Opcode in, Cpu *cpu) {
    if (cpu->registers[in.x()] != in.byte()) {
        cpu->pc += 2;
    }
}

// 5xy0 - Skip next instruction if Vx = Vy.
void SE_VX_VY(Opcode in, Cpu *cpu) {
    if (cpu->registers[in.x()] == cpu->registers[in.y()]) {
        cpu->pc += 2;
    }
}

// 6xkk - The interpreter puts the value kk into register Vx.
void LD_VX_KK(Opcode in, Cpu *cpu) {
    cpu->registers[in.x()] = in.byte();
}

// 7xkk - Adds the value kk to the value of register Vx.
void ADD_VX_KK(Opcode in, Cpu *cpu) {
    cpu->registers[in.x()] += in.byte();
}

// 8xy0 - Stores the value of register Vy in register Vx.
void LD_VX_VY(Opcode in, Cpu *cpu) {
    cpu->registers[in.x()] = cpu->registers[in.y()];
}

// 8xy1 - Performs a bitwise OR on the values of Vx and Vy.
void OR_VX_VY(Opcode in, Cpu *cpu) {
    cpu->registers[in.x()] |= cpu->registers[in.y()];
}

// 8xy2 - Performs a bitwise AND on the values of Vx and Vy.
void AND_VX_VY(Opcode in, Cpu *cpu) {
    cpu->registers[in.x()] &= cpu->registers[in.y()];
}

// 8xy3 - Performs a bitwise exclusive OR on the values of Vx and Vy.
void XOR_VX_VY(Opcode in, Cpu *cpu) {
    cpu->registers[in.x()] ^= cpu->registers[in.y()];
}

// 8xy4 - Set Vx = Vx + Vy, set VF = carry.
void ADD_VX_VY(Opcode in, Cpu *cpu) {
    uint16_t sum = cpu->registers[in.x()] + cpu->registers[in.y()];
    cpu->registers[0x0F] = sum > 0xFF ? 1 : 0;
    cpu->registers[in.x()] = sum & 0xFF;
}

// 8xy5 - Set Vx = Vx - Vy, set VF = NOT borrow.
void SUB_VX_VY(Opcode in, Cpu *cpu) {
    cpu->registers[0x0F] = cpu->registers[in.x()] > cpu->registers[in.y()] ? 1 : 0;
    cpu->registers[in.x()] -= cpu->registers[in.y()];
}

// 8xy6 - Set Vx = Vx SHR 1.
void SHR_VX(Opcode in, Cpu *cpu) {
    cpu->registers[0x0F] = cpu->registers[in.x()] & 0x01;
    cpu->registers[in.x()] >>= 1;
}

// 8xy7 - Set Vx = Vy - Vx, set VF = NOT borrow.
void SUBN_VX_VY(Opcode in, Cpu *cpu) {
    cpu->registers[0x0F] = cpu->registers[in.y()] > cpu->registers[in.x()] ? 1 : 0;
    cpu->registers[in.x()] = cpu->registers[in.y()] - cpu->registers[in.x()];
}

// 8xyE - Set Vx = Vx SHL 1.
void SHL_VX(Opcode in, Cpu *cpu) {
    cpu->registers[0x0F] = cpu->registers[in.x()] >> 7;
    cpu->registers[in.x()] <<= 1;
}

// 9xy0 - Skip next instruction if Vx != Vy.
void SNE_VX_VY(Opcode in, Cpu *cpu) {
    // TODO: impl.
}

// Annn - Register I is set to nnn.
void LD_I(Opcode in, Cpu *cpu) {
    // TODO: impl.
}

// Bnnn - Program counter is set to nnn plus the value of V0.
void JP_V0(Opcode in, Cpu *cpu) {
    // TODO: impl.
}

// Cxkk - Set Vx = random byte AND kk.
void RND(Opcode in, Cpu *cpu) {
    // TODO: impl.
}

// Dxyn - Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision.
void DRW(Opcode in, Cpu *cpu, Display *display) {
    // TODO: impl.
}

// Ex9E - Skip instruction if key with the value of Vx is pressed.
void SKP(Opcode in, Cpu *cpu) {
    // TODO: impl.
}

// ExA1 - Skip instruction if key with the value of Vx is not pressed.
void SKNP(Opcode in, Cpu *cpu) {
    // TODO: impl.
}

// Fx07 - Set Vx = delay timer value.
void LD_VX_DT(Opcode in, Cpu *cpu) {
    // TODO: impl.
}

// Fx0A - Wait for a key press, store the value of the key in Vx.
void LD_VX_K(Opcode in, Cpu *cpu) {
    // TODO: impl.
}

// Fx15 - Set delay timer = Vx.
void LD_DT(Opcode in, Cpu *cpu) {
    // TODO: impl.
}

// Fx18 - Set sound timer = Vx.
void LD_ST(Opcode in, Cpu *cpu) {
    // TODO: impl.
}

// Fx1E - Set I = I + Vx.
void ADD_I_VX(Opcode in, Cpu *cpu) {
    // TODO: impl.
}

// Fx29 - Set I = location of sprite for digit Vx.
void LD_F_VX(Opcode in, Cpu *cpu) {
   // TODO: impl.
}

// Fx33 - Store BCD representation of Vx in memory locations I, I+1, and I+2.
void LD_B_VX(Opcode in, Cpu *cpu) {
    // TODO: impl.
}

// Fx55 - Store registers V0 through Vx in memory starting at location I.
void LD_I_VX(Opcode in, Cpu *cpu) {
    // TODO: impl.
}

// Fx65 - Read registers V0 through Vx from memory starting at location I.
void LD_VX_I(Opcode in, Cpu *cpu) {
    // TODO: impl.
}


}

#endif  // CHIP8_INSTRUCTIONS_H