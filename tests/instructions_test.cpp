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
TEST(Instruction, CLS) {
    Display display;

    // turn pixels on
    display[0x01] = 1;
    display[0xFF] = 1;

    instruction::CLS(&display);

    // make sure all pixels are off
    for (auto i = 0; i < Display::kWidth * Display::kHeight; ++i) {
        EXPECT_EQ(display[i], 0);
    }
}

// 00EE - RET
// Return from a subroutine.
TEST(Instruction, RET) {
    Cpu cpu;

    // call subroutine 0x001
    instruction::CALL(0x2001, &cpu);

    // return from subroutine (empty call stack)
    instruction::RET(&cpu);
    EXPECT_EQ(cpu.sp, 0x00);
    EXPECT_EQ(cpu.stack[cpu.sp], 0x00);
}

// 1nnn - JP addr
// Jump to location nnn.
TEST(Instruction, JMP) {
    Cpu cpu;

    // jump to address 0x011A
    instruction::JMP(0x111A, &cpu);
    EXPECT_EQ(cpu.pc, 0x011A);
}

// 2nnn - CALL addr
// Call subroutine at nnn.
TEST(Instruction, CALL) {
    Cpu cpu;

    instruction::CALL(0x2001, &cpu);
    EXPECT_EQ(cpu.sp, 0x01);
    EXPECT_EQ(cpu.pc, 0x01);
}

// 3xkk - SE Vx, byte
// Skip next instruction if Vx = kk.
TEST(Instruction, SE_VX_KK) {
    Cpu cpu;

    // set registers
    cpu.registers[0x00] = 0x01;

    // kk is 1, should skip instruction
    instruction::SE_VX_KK(0x3001, &cpu);
    EXPECT_EQ(cpu.pc, 0x02);

    // kk is 2, shouldn't skip instruction
    instruction::SE_VX_KK(0x3002, &cpu);
    EXPECT_EQ(cpu.pc, 0x02);
}

// 4xkk - SNE Vx, byte
// Skip next instruction if Vx != kk.
TEST(Instruction, SNE_VX_KK) {
    Cpu cpu;

    // set registers
    cpu.registers[0x00] = 0x01;

    // kk is 1, should NOT skip instruction
    instruction::SNE_VX_KK(0x4001, &cpu);
    EXPECT_EQ(cpu.pc, 0x00);

    // kk is 2, should skip instruction
    instruction::SNE_VX_KK(0x4002, &cpu);
    EXPECT_EQ(cpu.pc, 0x02);
}

// 5xy0 - SE Vx, Vy
// Skip next instruction if Vx = Vy.
TEST(Instruction, SE_VX_VY) {
    Cpu cpu;

    // set registers
    cpu.registers[0x00] = 0x01;
    cpu.registers[0x01] = 0x01;
    cpu.registers[0x02] = 0x02;

    // x == y, should skip instruction
    instruction::SE_VX_VY(0x5010, &cpu);
    EXPECT_EQ(cpu.pc, 0x02);

    // x != y, shouldn't skip instruction
    instruction::SE_VX_VY(0x5120, &cpu);
    EXPECT_EQ(cpu.pc, 0x02);
}

// 6xkk - LD Vx, byte
// Set Vx = kk.
TEST(Instruction, LD_VX_KK) {
    Cpu cpu;

    instruction::LD_VX_KK(0x60AA, &cpu);
    EXPECT_EQ(cpu.registers[0x00], 0xAA);
}

// 7xkk - ADD Vx, byte
// Set Vx = Vx + kk.
TEST(Instruction, ADD_VX_KK) {
    Cpu cpu;

    // set registers
    cpu.registers[0x00] = 0x01;

    instruction::ADD_VX_KK(0x7002, &cpu);
    EXPECT_EQ(cpu.registers[0x00], 0x03);
}

// 8xy0 - LD Vx, Vy
// Set Vx = Vy.
TEST(Instruction, LD_VX_VY) {
    Cpu cpu;

    // set registers
    cpu.registers[0x01] = 0x02;

    instruction::LD_VX_VY(0x8010, &cpu);
    EXPECT_EQ(cpu.registers[0x00], 0x02);
}

// 8xy1 - OR Vx, Vy
// Set Vx = Vx OR Vy.
TEST(Instruction, OR_VX_VY) {
    Cpu cpu;

    // set registers
    cpu.registers[0x00] = 0x01;
    cpu.registers[0x01] = 0x02;

    instruction::OR_VX_VY(0x8011, &cpu);
    EXPECT_EQ(cpu.registers[0x00], 0x03);
}

// 8xy2 - AND Vx, Vy
// Set Vx = Vx AND Vy.
TEST(Instruction, AND_VX_VY) {
    Cpu cpu;

    // set registers
    cpu.registers[0x00] = 0x01;
    cpu.registers[0x01] = 0x02;

    instruction::AND_VX_VY(0x8012, &cpu);
    EXPECT_EQ(cpu.registers[0x00], 0x00);
}

// 8xy3 - XOR Vx, Vy
// Set Vx = Vx XOR Vy.
TEST(Instruction, XOR_VX_VY) {
    Cpu cpu;

    // set registers
    cpu.registers[0x00] = 0x11;
    cpu.registers[0x01] = 0x02;

    instruction::XOR_VX_VY(0x8013, &cpu);
    EXPECT_EQ(cpu.registers[0x00], 0x13);
}