// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gtest/gtest.h>

#include "core/parser.h"

using namespace c8;
using enum Instruction;

TEST(Parser, Opcodes) {
    EXPECT_EQ(parse(0x00E0), CLS);
    EXPECT_EQ(parse(0x00EE), RET);
    EXPECT_EQ(parse(0x1AAF), JMP);
    EXPECT_EQ(parse(0x2AAF), CALL);
    EXPECT_EQ(parse(0x30AA), SE_VX_KK);
    EXPECT_EQ(parse(0x40AA), SNE_VX_KK);
    EXPECT_EQ(parse(0x5010), SE_VX_VY);
    EXPECT_EQ(parse(0x60AA), LD_VX_KK);
    EXPECT_EQ(parse(0x70AA), ADD_VX_KK);
    EXPECT_EQ(parse(0x8010), LD_VX_VY);
    EXPECT_EQ(parse(0x8011), OR_VX_VY);
    EXPECT_EQ(parse(0x8012), AND_VX_VY);
    EXPECT_EQ(parse(0x8013), XOR_VX_VY);
    EXPECT_EQ(parse(0x8014), ADD_VX_VY);
    EXPECT_EQ(parse(0x8015), SUB_VX_VY);
    EXPECT_EQ(parse(0x8016), SHR_VX_VY);
    EXPECT_EQ(parse(0x8017), SUBN_VX_VY);
    EXPECT_EQ(parse(0x801E), SHL_VX_VY);
    EXPECT_EQ(parse(0x9010), SNE_VX_VY);
    EXPECT_EQ(parse(0xA111), LD_I);
    EXPECT_EQ(parse(0xB111), JMP_V0);
    EXPECT_EQ(parse(0xC100), RND);
    EXPECT_EQ(parse(0xD321), DRW);
    EXPECT_EQ(parse(0xE09E), SKP);
    EXPECT_EQ(parse(0xE0A1), SKNP);
    EXPECT_EQ(parse(0xF107), LD_VX_DT);
    EXPECT_EQ(parse(0xF10A), LD_VX_K);
    EXPECT_EQ(parse(0xF115), LD_DT);
    EXPECT_EQ(parse(0xF118), LD_ST);
    EXPECT_EQ(parse(0xF11E), ADD_I_VX);
    EXPECT_EQ(parse(0xF129), LD_F_VX);
    EXPECT_EQ(parse(0xF133), LD_B_VX);
    EXPECT_EQ(parse(0xF155), LD_I_VX);
    EXPECT_EQ(parse(0xF165), LD_VX_I);
}