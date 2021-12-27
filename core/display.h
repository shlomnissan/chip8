// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef CHIP8_DISPLAY_H
#define CHIP8_DISPLAY_H

#include <array>
#include <vector>
#include <cinttypes>
#include <algorithm>
#include <stdexcept>

#include "../messages.h"

namespace c8 {

class Display {
public:
    static constexpr int kWidth = 64;
    static constexpr int kHeight = 32;
    static constexpr int kScale = 10;

    [[nodiscard]] static constexpr int width() { return kWidth * kScale; }
    [[nodiscard]] static constexpr int height() { return kHeight * kScale; }

    void ClearScreen() {
        std::fill(begin(data), end(data), 0);
    }

    uint8_t& operator[](int index) {
        return data.at(index);
    }

private:
    std::array<uint8_t, kWidth * kHeight> data = {0};
};

}

#endif  // CHIP8_DISPLAY_H
