// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gtest/gtest.h>
#include <algorithm>

#include "core/instructions.h"
#include "core/cpu.h"
#include "core/display.h"

using namespace c8;

// 00E0 - CLS
// Clear the display.
TEST(Instructions, OP_CLS) {
    Display display;

    // turn pixels on
    display[0x01] = 1;
    display[0xFF] = 1;

    instruction::OP_CLS(&display);

    // make sure all pixels are turned off
    for (auto i = 0; i < Display::kWidth * Display::kHeight; ++i) {
        EXPECT_EQ(display[i], 0);
    }
}

// 00EE - RET
// Return from a subroutine.
TEST(Instructions, OP_RET) {
    Cpu cpu;

    // call subroutine 0x001
    instruction::OP_CALL(0x2001, &cpu);

    // return from subroutine (empty call stack)
    instruction::OP_RET(&cpu);
    EXPECT_EQ(cpu.sp, 0x00);
    EXPECT_EQ(cpu.stack[cpu.sp], 0x00);
}

// 1nnn - JP addr
// Jump to location nnn.
TEST(Instructions, OP_JP) {
    Cpu cpu;

    // jump to address 0x011A
    instruction::OP_JP(0x111A, &cpu);
    EXPECT_EQ(cpu.pc, 0x011A);
}

// 2nnn - CALL addr
// Call subroutine at nnn.
TEST(Instructions, OP_CALL) {
    Cpu cpu;

    instruction::OP_CALL(0x2001, &cpu);
    EXPECT_EQ(cpu.sp, 0x01);
    EXPECT_EQ(cpu.pc, 0x01);
}

// 3xkk - SE Vx, byte
// Skip next instruction if Vx = kk.
TEST(Instructions, OP_SE_BYTE) {
    Cpu cpu;

    // set registers
    cpu.registers[0x00] = 0x01;

    // kk is 1, should skip instruction
    instruction::OP_SE_BYTE(0x3001, &cpu);
    EXPECT_EQ(cpu.pc, 0x02);

    // kk is 2, shouldn't skip instruction
    instruction::OP_SE_BYTE(0x3002, &cpu);
    EXPECT_EQ(cpu.pc, 0x02);
}

// 4xkk - SNE Vx, byte
// Skip next instruction if Vx != kk.
TEST(Instructions, OP_SNE_BYTE) {
    Cpu cpu;

    // set registers
    cpu.registers[0x00] = 0x01;

    // kk is 1, should NOT skip instruction
    instruction::OP_SNE_BYTE(0x4001, &cpu);
    EXPECT_EQ(cpu.pc, 0x00);

    // kk is 2, should skip instruction
    instruction::OP_SNE_BYTE(0x4002, &cpu);
    EXPECT_EQ(cpu.pc, 0x02);
}

// 5xy0 - SE Vx, Vy
// Skip next instruction if Vx = Vy.
TEST(Instruction, OP_SN_XY) {
    Cpu cpu;

    // set registers
    cpu.registers[0x00] = 0x01;
    cpu.registers[0x01] = 0x01;
    cpu.registers[0x02] = 0x02;

    // x == y, should skip instruction
    instruction::OP_SN_XY(0x5010, &cpu);
    EXPECT_EQ(cpu.pc, 0x02);

    // x != y, shouldn't skip instruction
    instruction::OP_SN_XY(0x5120, &cpu);
    EXPECT_EQ(cpu.pc, 0x02);
}

// 6xkk - LD Vx, byte
// Set Vx = kk.
TEST(Instruction, LD_VX_BYTE) {
    Cpu cpu;

    instruction::LD_VX_BYTE(0x60AA, &cpu);
    EXPECT_EQ(cpu.registers[0x00], 0xAA);
}

// 7xkk - ADD Vx, byte
// Set Vx = Vx + kk.
TEST(Instruction, ADD_VX_BYTE) {
    Cpu cpu;

    // set registers
    cpu.registers[0x00] = 0x01;

    instruction::ADD_VX_BYTE(0x7002, &cpu);
    EXPECT_EQ(cpu.registers[0x00], 0x03);
}