// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef CHIP8_DISPLAY_H
#define CHIP8_DISPLAY_H

namespace c8 {

class Display {
public:
    [[nodiscard]] static constexpr int width() { return kWidth * kScale; }
    [[nodiscard]] static constexpr int height() { return kHeight * kScale; }

private:
    static constexpr int kWidth = 64;
    static constexpr int kHeight = 32;
    static constexpr int kScale = 10;
};

}

#endif  // CHIP8_DISPLAY_H
