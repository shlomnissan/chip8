// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gtest/gtest.h>
#include <vector>

#include "core/instructions.h"
#include "core/display.h"
#include "core/input.h"
#include "core/types.h"
#include "mocks.h"

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
    cpu.regs[0x00] = 0x01;

    // kk is 1, should skip instruction
    instruction::SE_VX_KK(0x3001, &cpu);
    EXPECT_EQ(cpu.pc, 0x02);

    // kk is 2, shouldn't skip instruction
    instruction::SE_VX_KK(0x3002, &cpu);
    EXPECT_EQ(cpu.pc, 0x02);
}

TEST(Instruction, SNE_VX_KK) {
    Cpu cpu;
    cpu.regs[0x00] = 0x01;

    // kk is 1, should NOT skip instruction
    instruction::SNE_VX_KK(0x4001, &cpu);
    EXPECT_EQ(cpu.pc, 0x00);

    // kk is 2, should skip instruction
    instruction::SNE_VX_KK(0x4002, &cpu);
    EXPECT_EQ(cpu.pc, 0x02);
}

TEST(Instruction, SE_VX_VY) {
    Cpu cpu;
    cpu.regs[0x00] = 0x01;
    cpu.regs[0x01] = 0x01;
    cpu.regs[0x02] = 0x02;

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
    EXPECT_EQ(cpu.regs[0x00], 0xAA);
}

TEST(Instruction, ADD_VX_KK) {
    Cpu cpu;
    cpu.regs[0x00] = 0x01;

    instruction::ADD_VX_KK(0x7002, &cpu);
    EXPECT_EQ(cpu.regs[0x00], 0x03);
}

TEST(Instruction, LD_VX_VY) {
    Cpu cpu;
    cpu.regs[0x01] = 0x02;

    instruction::LD_VX_VY(0x8010, &cpu);
    EXPECT_EQ(cpu.regs[0x00], 0x02);
}

TEST(Instruction, OR_VX_VY) {
    Cpu cpu;
    cpu.regs[0x00] = 0x01;
    cpu.regs[0x01] = 0x02;

    instruction::OR_VX_VY(0x8011, &cpu);
    EXPECT_EQ(cpu.regs[0x00], 0x03);
}

TEST(Instruction, AND_VX_VY) {
    Cpu cpu;
    cpu.regs[0x00] = 0x01;
    cpu.regs[0x01] = 0x02;

    instruction::AND_VX_VY(0x8012, &cpu);
    EXPECT_EQ(cpu.regs[0x00], 0x00);
}

TEST(Instruction, XOR_VX_VY) {
    Cpu cpu;
    cpu.regs[0x00] = 0x11;
    cpu.regs[0x01] = 0x02;

    instruction::XOR_VX_VY(0x8013, &cpu);
    EXPECT_EQ(cpu.regs[0x00], 0x13);
}

TEST(Instruction, ADD_VX_VY) {
    Cpu cpu;
    cpu.regs[0x00] = 0x01;
    cpu.regs[0x01] = 0x02;

    // add without overflow
    instruction::ADD_VX_VY(0x8014, &cpu);
    EXPECT_EQ(cpu.regs[0x00], 0x03);
    EXPECT_EQ(cpu.regs[0x0F], 0x00);

    // add with overflow - test the carry (0x0F)
    cpu.regs[0x00] = 0xFF;
    instruction::ADD_VX_VY(0x8014, &cpu);
    EXPECT_EQ(cpu.regs[0x00], 0x01);
    EXPECT_EQ(cpu.regs[0x0F], 0x01);
}

TEST(Instruction, SUB_VX_VY) {
    Cpu cpu;
    cpu.regs[0x00] = 0x01;
    cpu.regs[0x01] = 0x02;

    // subtract with negative result
    instruction::SUB_VX_VY(0x8015, &cpu);
    EXPECT_EQ(cpu.regs[0x00], 0xFF);
    EXPECT_EQ(cpu.regs[0x0F], 0x00);

    // subtract with positive result
    cpu.regs[0x00] = 0x04;
    instruction::SUB_VX_VY(0x8015, &cpu);
    EXPECT_EQ(cpu.regs[0x00], 0x02);
    EXPECT_EQ(cpu.regs[0x0F], 0x01);
}

TEST(Instruction, SHR_VX) {
    Cpu cpu;
    cpu.regs[0x00] = 0x06;

    instruction::SHR_VX(0x8006, &cpu);
    EXPECT_EQ(cpu.regs[0x00], 0x03);
    EXPECT_EQ(cpu.regs[0x0F], 0x00);

    instruction::SHR_VX(0x8006, &cpu);
    EXPECT_EQ(cpu.regs[0x00], 0x01);
    EXPECT_EQ(cpu.regs[0x0F], 0x01);
}

TEST(Instruction, SUBN_VX_VY) {
    Cpu cpu;
    cpu.regs[0x00] = 0x02;
    cpu.regs[0x01] = 0x03;

    // subtract with a positive result
    instruction::SUBN_VX_VY(0x8017, &cpu);
    EXPECT_EQ(cpu.regs[0x00], 0x01);
    EXPECT_EQ(cpu.regs[0x0F], 0x01);

    cpu.regs[0x00] = 0x03;
    cpu.regs[0x01] = 0x02;

    // subtract with a negative result
    instruction::SUBN_VX_VY(0x8017, &cpu);
    EXPECT_EQ(cpu.regs[0x00], 0xFF);
    EXPECT_EQ(cpu.regs[0x0F], 0x00);
}

TEST(Instruction, SHL_VX) {
    Cpu cpu;
    cpu.regs[0x00] = 0x80;

    instruction::SHL_VX(0x800E, &cpu);
    EXPECT_EQ(cpu.regs[0x00], 0x00);
    EXPECT_EQ(cpu.regs[0x0F], 0x01);

    cpu.regs[0x00] = 0x40;
    instruction::SHL_VX(0x800E, &cpu);
    EXPECT_EQ(cpu.regs[0x00], 0x80);
    EXPECT_EQ(cpu.regs[0x0F], 0x00);
}

TEST(Instruction, SNE_VX_VY) {
    Cpu cpu;
    cpu.regs[0x00] = 0x01;
    cpu.regs[0x01] = 0x01;
    cpu.regs[0x02] = 0x02;

    // don't skip to next instruction
    instruction::SNE_VX_VY(0x9010, &cpu);
    EXPECT_EQ(cpu.pc, 0x00);

    // skip to next instruction
    instruction::SNE_VX_VY(0x9020, &cpu);
    EXPECT_EQ(cpu.pc, 0x02);
}

TEST(Instruction, LD_I) {
    Cpu cpu;

    instruction::LD_I(0xA2B4, &cpu);
    EXPECT_EQ(cpu.I, 0x02B4);
}

TEST(Instruction, JP_V0) {
    Cpu cpu;
    cpu.regs[0x00] = 0x01;

    instruction::JP_V0(0xB2B4, &cpu);
    EXPECT_EQ(cpu.pc, 0x02B5);
}

TEST(Instruction, RND) {
    Cpu cpu;

    MockRand rand;
    EXPECT_EQ(rand(), 0xB4);

    instruction::RND(0xC00F, &cpu, &rand);
    EXPECT_EQ(cpu.regs[0x00], 0x04);
}

TEST(Instruction, DRW) {
    Cpu cpu;
    Memory memory;
    Display display;

    // sprite data
    memory[0x00] = 0x20;
    memory[0x01] = 0x60;
    memory[0x02] = 0x20;
    memory[0x03] = 0x20;
    memory[0x04] = 0x70;

    // draw sprite into the display
    instruction::DRW(0xD015, &cpu, &display, &memory);

    // expected output
    std::vector<std::vector<int>> sprite = {
        {0, 0, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 1, 1, 1},
    };

    // check that the expected output matches the display
    for (auto y = 0; y < sprite.size(); ++y) {
        for (auto x = 0; x < sprite.front().size(); ++x) {
            auto pixel = display[x + y * 64];
            EXPECT_EQ(sprite[y][x], pixel);
        }
    }

    // ensure there was no collision
    EXPECT_EQ(cpu.regs[0x0F], 0);

    // check for collision
    instruction::DRW(0xD015, &cpu, &display, &memory);
    EXPECT_EQ(cpu.regs[0x0F], 1);
}

TEST(Instruction, SKP) {
    Cpu cpu;
    cpu.regs[0x00] = 0x01;

    Input input;
    instruction::SKP(0xE09E, &cpu, &input);

    // key isn't pressed - don't skip instruction
    EXPECT_EQ(cpu.pc, 0x00);

    // press the 1-key in computer actual keyboard
    input[0x31] = 1;
    instruction::SKP(0xE09E, &cpu, &input);

    // key is pressed - skip instruction
    EXPECT_EQ(cpu.pc, 0x02);
}

TEST(Instruction, SKNP) {
    Cpu cpu;
    cpu.regs[0x00] = 0x01;

    Input input;
    instruction::SKNP(0xE09E, &cpu, &input);

    // key isn't pressed - skip instruction
    EXPECT_EQ(cpu.pc, 0x02);

    // press the 1-key in computer actual keyboard
    input[0x31] = 1;
    instruction::SKNP(0xE09E, &cpu, &input);

    // key is pressed - don't skip instruction
    EXPECT_EQ(cpu.pc, 0x02);
}

TEST(Instruction, LD_VX_DT) {
    Cpu cpu;
    cpu.t_delay = 0x05;

    instruction::LD_VX_DT(0xF207, &cpu);

    EXPECT_EQ(cpu.regs[0x02], 0x05);
}

TEST(Instruction, LD_VX_K) {
    Cpu cpu;
    Input input;

    // no key was pressed, register 5 should be 0
    instruction::LD_VX_K(0xF50A, &cpu, &input);
    EXPECT_EQ(cpu.regs[0x05], 0x00);

    // press the 2-key in computer actual keyboard
    input[0x32] = 1;

    // 2-key was pressed, register 5 should be 2
    instruction::LD_VX_K(0xF50A, &cpu, &input);
    EXPECT_EQ(cpu.regs[0x05], 0x02);
}

TEST(Instruction, LD_DT) {
    Cpu cpu;
    cpu.regs[0x01] = 0x03;
    instruction::LD_DT(0xF118, &cpu);
    EXPECT_EQ(cpu.t_delay, 0x03);
}

TEST(Instruction, LD_ST) {
    Cpu cpu;
    cpu.regs[0x01] = 0x03;
    instruction::LD_ST(0xF118, &cpu);
    EXPECT_EQ(cpu.t_sound, 0x03);
}

TEST(Instruction, ADD_I_VX) {
    Cpu cpu;
    cpu.I = 0x02;
    cpu.regs[0x00] = 0x02;
    instruction::ADD_I_VX(0xF01E, &cpu);
    EXPECT_EQ(cpu.I, 0x04);
}

TEST(Instruction, LD_F_VX) {
    Cpu cpu;
    cpu.regs[0x00] = 0x0A;
    instruction::LD_F_VX(0xF029, &cpu);
    EXPECT_EQ(cpu.I, 0x32);
}

TEST(Instruction, LD_B_VX) {
    Cpu cpu;
    cpu.regs[0x00] = 0xFE; // 254 decimal
    cpu.I = 0x50;

    Memory ram;
    instruction::LD_B_VX(0xF033, &cpu, &ram);
    EXPECT_EQ(ram[cpu.I], 0x02); // the hundreds digit (2)
    EXPECT_EQ(ram[cpu.I + 1], 0x05); // the tens digit (5)
    EXPECT_EQ(ram[cpu.I + 2], 0x04); // the ones digit (4)
}

TEST(Instruction, LD_I_VX) {
    Cpu cpu;

    std::vector<uint8_t> data = {0x0A, 0x10, 0x05};
    // copy data to registers
    for (auto i = 0; i < data.size(); ++i) {
        cpu.regs[i] = data[i];
    }

    cpu.I = 0x50;

    Memory ram;
    instruction::LD_I_VX(0xF255, &cpu, &ram);

    // verify the data was copied to memory
    for (auto i = 0; i < data.size(); ++i) {
        EXPECT_EQ(ram[cpu.I + i], cpu.regs[i]);
    }
}

TEST(Instruction, LD_VX_I) {
    Cpu cpu;
    cpu.I = 0x50;

    std::vector<uint8_t> data = {0x0A, 0x10, 0x05};
    Memory ram;
    // copy data to memory
    for (auto i = 0; i < data.size(); ++i) {
        ram[cpu.I + i] = data[i];
    }

    instruction::LD_VX_I(0xF265, &cpu, &ram);

    // verify the data was copied to registers
    for (auto i = 0; i < data.size(); ++i) {
        EXPECT_EQ(cpu.regs[i], ram[cpu.I + i]);
    }
}