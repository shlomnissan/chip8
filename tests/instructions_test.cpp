// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gtest/gtest.h>
#include <algorithm>

#include "core/instructions.h"
#include "core/cpu.h"
#include "core/display.h"

using namespace c8;

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

TEST(Instruction, RET) {
    Cpu cpu;

    // call subroutine 0x001
    instruction::CALL(0x2001, &cpu);

    // return from subroutine (empty call stack)
    instruction::RET(&cpu);
    EXPECT_EQ(cpu.sp, 0x00);
    EXPECT_EQ(cpu.stack[cpu.sp], 0x00);
}

TEST(Instruction, JMP) {
    Cpu cpu;

    // jump to address 0x011A
    instruction::JMP(0x111A, &cpu);
    EXPECT_EQ(cpu.pc, 0x011A);
}

TEST(Instruction, CALL) {
    Cpu cpu;

    instruction::CALL(0x2001, &cpu);
    EXPECT_EQ(cpu.sp, 0x01);
    EXPECT_EQ(cpu.pc, 0x01);
}

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

TEST(Instruction, LD_VX_KK) {
    Cpu cpu;

    instruction::LD_VX_KK(0x60AA, &cpu);
    EXPECT_EQ(cpu.registers[0x00], 0xAA);
}

TEST(Instruction, ADD_VX_KK) {
    Cpu cpu;

    // set registers
    cpu.registers[0x00] = 0x01;

    instruction::ADD_VX_KK(0x7002, &cpu);
    EXPECT_EQ(cpu.registers[0x00], 0x03);
}

TEST(Instruction, LD_VX_VY) {
    Cpu cpu;

    // set registers
    cpu.registers[0x01] = 0x02;

    instruction::LD_VX_VY(0x8010, &cpu);
    EXPECT_EQ(cpu.registers[0x00], 0x02);
}

TEST(Instruction, OR_VX_VY) {
    Cpu cpu;

    // set registers
    cpu.registers[0x00] = 0x01;
    cpu.registers[0x01] = 0x02;

    instruction::OR_VX_VY(0x8011, &cpu);
    EXPECT_EQ(cpu.registers[0x00], 0x03);
}

TEST(Instruction, AND_VX_VY) {
    Cpu cpu;

    // set registers
    cpu.registers[0x00] = 0x01;
    cpu.registers[0x01] = 0x02;

    instruction::AND_VX_VY(0x8012, &cpu);
    EXPECT_EQ(cpu.registers[0x00], 0x00);
}

TEST(Instruction, XOR_VX_VY) {
    Cpu cpu;

    // set registers
    cpu.registers[0x00] = 0x11;
    cpu.registers[0x01] = 0x02;

    instruction::XOR_VX_VY(0x8013, &cpu);
    EXPECT_EQ(cpu.registers[0x00], 0x13);
}

TEST(Instruction, ADD_VX_VY) {
    // TODO: impl.
}

TEST(Instruction, SUB_VX_VY) {
    // TODO: impl.
}

TEST(Instruction, SHR_VX_VY) {
    // TODO: impl.
}

TEST(Instruction, SUBN_VX_VY) {
    // TODO: impl.
}

TEST(Instruction, SHL_VX_VY) {
    // TODO: impl.
}

TEST(Instruction, SNE_VX_VY) {
    // TODO: impl.
}

TEST(Instruction, LD_I) {
    // TODO: impl.
}

TEST(Instruction, JP_V0) {
    // TODO: impl.
}

TEST(Instruction, RND) {
    // TODO: impl.
}

TEST(Instruction, DRW) {
    // TODO: impl.
}

TEST(Instruction, SKP) {
    // TODO: impl.
}

TEST(Instruction, SKNP) {
    // TODO: impl.
}

TEST(Instruction, LD_VX_DT) {
    // TODO: impl.
}

TEST(Instruction, LD_VX_K) {
    // TODO: impl.
}

TEST(Instruction, LD_DT) {
    // TODO: impl.
}

TEST(Instruction, LD_ST) {
    // TODO: impl.
}

TEST(Instruction, ADD_I_VX) {
    // TODO: impl.
}

TEST(Instruction, LD_F_VX) {
    // TODO: impl.
}

TEST(Instruction, LD_B_VX) {
    // TODO: impl.
}

TEST(Instruction, LD_I_VX) {
    // TODO: impl.
}

TEST(Instruction, LD_VX_I) {
    // TODO: impl.
}