// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef CHIP8_PARSER_H
#define CHIP8_PARSER_H

#include "types.h"

namespace c8 {

enum class Instruction {
    ADD_I_VX,
    ADD_VX_KK,
    ADD_VX_VY,
    AND_VX_VY,
    CALL,
    CLS,
    DRW,
    JMP,
    JMP_V0,
    LD_B_VX,
    LD_DT,
    LD_F_VX,
    LD_I,
    LD_I_VX,
    LD_ST,
    LD_VX_DT,
    LD_VX_I,
    LD_VX_K,
    LD_VX_KK,
    LD_VX_VY,
    OR_VX_VY,
    RET,
    RND,
    SE_VX_KK,
    SE_VX_VY,
    SHL_VX_VY,
    SHR_VX_VY,
    SKNP,
    SKP,
    SNE_VX_KK,
    SNE_VX_VY,
    SUBN_VX_VY,
    SUB_VX_VY,
    XOR_VX_VY,
    UNKNOWN
};

// Standard Chip-8 instructions reference:
// http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#3.1
Instruction parse(size_op opcode) {
    switch (opcode >> 12) {
        case 0x00:
            switch (opcode & 0x00FF) {
                // 00E0 - Clear the display.
                case 0xE0: return Instruction::CLS;
                // 00EE - Return from a subroutine.
                case 0xEE: return Instruction::RET;
                // UNKNOWN
                default: return Instruction::UNKNOWN;
            }
        // 1nnn - Jump to location nnn.
        case 0x01: return Instruction::JMP;
        // 2nnn - Call subroutine at nnn.
        case 0x02: return Instruction::CALL;
        // 3xkk - Skip next instruction if Vx = kk.
        case 0x03: return Instruction::SE_VX_KK;
        // 4xkk - Skip next instruction if Vx != kk.
        case 0x04: return Instruction::SNE_VX_KK;
        // 5xy0 - Skip next instruction if Vx = Vy.
        case 0x05: return Instruction::SE_VX_VY;
        // 6xkk - The interpreter puts the value kk into register Vx.
        case 0x06: return Instruction::LD_VX_KK;
        // 7xkk - Adds the value kk to the value of register Vx.
        case 0x07: return Instruction::ADD_VX_KK;
        case 0x08:
            switch (opcode & 0x000F) {
                // 8xy0 - Stores the value of register Vy in register Vx.
                case 0x00: return Instruction::LD_VX_VY;
                // 8xy1 - Performs a bitwise OR on the values of Vx and Vy.
                case 0x01: return Instruction::OR_VX_VY;
                // 8xy2 - Performs a bitwise AND on the values of Vx and Vy.
                case 0x02: return Instruction::AND_VX_VY;
                // 8xy3 - Performs a bitwise exclusive OR on the values of Vx and Vy.
                case 0x03: return Instruction::XOR_VX_VY;
                // 8xy4 - Set Vx = Vx + Vy, set VF = carry.
                case 0x04: return Instruction::ADD_VX_VY;
                // 8xy5 - Set Vx = Vx - Vy, set VF = NOT borrow.
                case 0x05: return Instruction::SUB_VX_VY;
                // 8xy6 - Set Vx = Vx SHR 1.
                case 0x06: return Instruction::SHR_VX_VY;
                // 8xy7 - Set Vx = Vy - Vx, set VF = NOT borrow.
                case 0x07: return Instruction::SUBN_VX_VY;
                // 8xyE - SHL Vx {, Vy}.
                case 0x0E: return Instruction::SHL_VX_VY;
                // UNKNOWN
                default: return Instruction::UNKNOWN;
            }
        // 9xy0 - Skip next instruction if Vx != Vy.
        case 0x09: return Instruction::SNE_VX_VY;
        // Annn - Register I is set to nnn.
        case 0x0A: return Instruction::LD_I;
        // Bnnn - Program counter is set to nnn plus the value of V0.
        case 0x0B: return Instruction::JMP_V0;
        // Cxkk - Set Vx = random byte AND kk.
        case 0x0C: return Instruction::RND;
        // Dxyn - Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision.
        case 0x0D: return Instruction::DRW;
        case 0x0E:
            switch (opcode & 0x00FF) {
                // Ex9E - Skip instruction if key with the value of Vx is pressed.
                case 0x9E: return Instruction::SKP;
                // ExA1 - Skip instruction if key with the value of Vx is not pressed.
                case 0xA1: return Instruction::SKNP;
                // UNKNOWN
                default: return Instruction::UNKNOWN;
            }
        case 0x0F:
            switch (opcode & 0x00FF) {
                // Fx07 - Set Vx = delay timer value.
                case 0x07: return Instruction::LD_VX_DT;
                // Fx0A - Wait for a key press, store the value of the key in Vx.
                case 0x0A: return Instruction::LD_VX_K;
                // Fx15 - Set delay timer = Vx.
                case 0x15: return Instruction::LD_DT;
                // Fx18 - Set sound timer = Vx.
                case 0x18: return Instruction::LD_ST;
                // Fx1E - Set I = I + Vx.
                case 0x1E: return Instruction::ADD_I_VX;
                // Fx29 - Set I = location of sprite for digit Vx.
                case 0x29: return Instruction::LD_F_VX;
                // Fx33 - Store BCD representation of Vx in memory locations I, I+1, and I+2.
                case 0x33: return Instruction::LD_B_VX;
                // Fx55 - Store registers V0 through Vx in memory starting at location I.
                case 0x55: return Instruction::LD_I_VX;
                // Fx65 - Read registers V0 through Vx from memory starting at location I.
                case 0x65: return Instruction::LD_VX_I;
                // UNKNOWN
                default: return Instruction::UNKNOWN;
            }
        default: return Instruction::UNKNOWN;
    }
}

}

#endif  // CHIP8_PARSER_H