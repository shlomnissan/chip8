// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef CHIP8_PARSER_H
#define CHIP8_PARSER_H

#include "types.h"

namespace c8 {

enum class Instruction {
    CLS,
    RET,
    JMP,
    CALL,
    SE_VX_KK,
    SNE_VX_KK,
    SE_VX_VY,
    LD_VX_KK,
    ADD_VX_KK,
    LD_VX_VY,
    OR_VX_VY,
    AND_VX_VY,
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
                // UNKNOWN
                default: return Instruction::UNKNOWN;
            }
        default: return Instruction::UNKNOWN;
    }
}

}

#endif  // CHIP8_PARSER_H