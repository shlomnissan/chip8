// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gtest/gtest.h>

#include "core/parser.h"

using namespace c8;

TEST(Parser, Opcodes) {
    EXPECT_EQ(parse(0x00E0), Instruction::CLS);
    EXPECT_EQ(parse(0x00EE), Instruction::RET);
    EXPECT_EQ(parse(0x1AAF), Instruction::JMP);
    EXPECT_EQ(parse(0x2AAF), Instruction::CALL);
    EXPECT_EQ(parse(0x30AA), Instruction::SE_VX_KK);
    EXPECT_EQ(parse(0x40AA), Instruction::SNE_VX_KK);
    EXPECT_EQ(parse(0x5010), Instruction::SE_VX_VY);
    EXPECT_EQ(parse(0x60AA), Instruction::LD_VX_KK);
    EXPECT_EQ(parse(0x70AA), Instruction::ADD_VX_KK);
    EXPECT_EQ(parse(0x8010), Instruction::LD_VX_VY);
    EXPECT_EQ(parse(0x8011), Instruction::OR_VX_VY);
    EXPECT_EQ(parse(0x8012), Instruction::AND_VX_VY);
    EXPECT_EQ(parse(0x8013), Instruction::XOR_VX_VY);
    EXPECT_EQ(parse(0x8014), Instruction::ADD_VX_VY);
    EXPECT_EQ(parse(0x8015), Instruction::SUB_VX_VY);
    EXPECT_EQ(parse(0x8016), Instruction::SHR_VX);
    EXPECT_EQ(parse(0x8017), Instruction::SUBN_VX_VY);
    EXPECT_EQ(parse(0x801E), Instruction::SHL_VX);
    EXPECT_EQ(parse(0x9010), Instruction::SNE_VX_VY);
    EXPECT_EQ(parse(0xA2B4), Instruction::LD_I);
    EXPECT_EQ(parse(0xB111), Instruction::JMP_V0);
    EXPECT_EQ(parse(0xC100), Instruction::RND);
    EXPECT_EQ(parse(0xD321), Instruction::DRW);
    EXPECT_EQ(parse(0xE09E), Instruction::SKP);
    EXPECT_EQ(parse(0xE0A1), Instruction::SKNP);
    EXPECT_EQ(parse(0xF107), Instruction::LD_VX_DT);
    EXPECT_EQ(parse(0xF10A), Instruction::LD_VX_K);
    EXPECT_EQ(parse(0xF115), Instruction::LD_DT);
    EXPECT_EQ(parse(0xF118), Instruction::LD_ST);
    EXPECT_EQ(parse(0xF11E), Instruction::ADD_I_VX);
    EXPECT_EQ(parse(0xF129), Instruction::LD_F_VX);
    EXPECT_EQ(parse(0xF133), Instruction::LD_B_VX);
    EXPECT_EQ(parse(0xF155), Instruction::LD_I_VX);
    EXPECT_EQ(parse(0xF165), Instruction::LD_VX_I);
}