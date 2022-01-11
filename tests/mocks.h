// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef CHIP8_MOCKS_HPP
#define CHIP8_MOCKS_HPP

#include "core/random.h"

class MockRand : public c8::Random {
public:
    [[nodiscard]] uint8_t operator()() { return 0xB4; }
};

#endif  // CHIP8_MOCKS_HPP
