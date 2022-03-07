// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef CHIP8_INPUT_H
#define CHIP8_INPUT_H

#include <array>
#include <cinttypes>

/*
------------------------------------------------
|   Chip 8 Keyboard    |     Keyboard Map      |
------------------------------------------------
|   1    2    3    C   |    1    2    3    4   |
|   4    5    6    D   |    Q    W    E    R   |
|   7    8    9    E   |    A    S    D    F   |
|   A    0    B    F   |    Z    X    C    V   |
------------------------------------------------
 */

namespace c8 {

class Input {
public:
    uint8_t& operator[](uint8_t index) {
        return keyboard.at(index);
    }

    bool IsPressed(uint8_t key) {
        return keyboard.at(keymap.at(key)) == 1;
    }

    void Reset() {
        keyboard.fill(0);
    }

private:
    std::array<uint8_t, 0xFF> keyboard = {0};
    std::array<uint8_t, 0x10> keymap = {
        0x78, // X (C8: 0)
        0x31, // 1 (C8: 1)
        0x32, // 2 (C8: 2)
        0x33, // 3 (C8: 3)
        0x71, // Q (C8: 4)
        0x77, // W (C8: 5)
        0x65, // E (C8: 6)
        0x61, // A (C8: 7)
        0x73, // S (C8: 8)
        0x64, // D (C8: 9)
        0x7a, // Z (C8: A)
        0x63, // C (C8: B)
        0x34, // 4 (C8: C)
        0x72, // R (C8: D)
        0x66, // F (C8: E)
        0x76, // V (C8: F)
    };
};

}

#endif  // CHIP8_INPUT_HPP
