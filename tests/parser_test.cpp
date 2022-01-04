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
}