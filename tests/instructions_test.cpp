// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gtest/gtest.h>
#include <algorithm>

#include "core/instructions.h"
#include "core/cpu.h"
#include "core/display.h"

using namespace c8;

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

TEST(Instructions, OP_RET) {
    Cpu cpu;

    // call subroutine 0x001
    instruction::OP_CALL(0x2001, &cpu);

    // return from subroutine (empty call stack)
    instruction::OP_RET(&cpu);
    EXPECT_EQ(cpu.sp, 0);
    EXPECT_EQ(cpu.stack[cpu.sp], 0);
}

TEST(Instructions, OP_JP) {
    Cpu cpu;

    // jump to address 0x011A
    instruction::OP_JP(0x111A, &cpu);
    EXPECT_EQ(cpu.pc, 0x011A);
}