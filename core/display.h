// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef CHIP8_DISPLAY_H
#define CHIP8_DISPLAY_H

#include <array>
#include <cinttypes>
#include <algorithm>
#include <stdexcept>

#include "../messages.h"

namespace c8 {

class Display {
public:
    [[nodiscard]] static constexpr int width() { return kWidth * kScale; }
    [[nodiscard]] static constexpr int height() { return kHeight * kScale; }

    void ClearScreen() {
        std::fill(begin(display), end(display), 0);
    }

    uint8_t& operator[](int index) {
        if (index < 0 || index >= kWidth * kHeight) {
            throw std::range_error(message::DisplayRangeError);
        }
        return display[index];
    }

private:
    static constexpr int kWidth = 64;
    static constexpr int kHeight = 32;
    static constexpr int kScale = 10;

    std::array<uint8_t, kWidth * kHeight> display = {0};
};

}

#endif  // CHIP8_DISPLAY_H
