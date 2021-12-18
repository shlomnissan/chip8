// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef CHIP8_ROM_H
#define CHIP8_ROM_H

#include <string_view>
#include <fstream>
#include <vector>
#include <exception>

namespace c8 {

// 0xDFF = 3,583 = 4,095 (Chip8 RAM) - 512 (Reserved RAM)
const int kMaxRomFileSize = 0xDFF;

class Rom {
public:
    ~Rom();

    [[nodiscard]] bool WithFile(std::string_view filename);
    std::vector<char> Data();

private:
    std::ifstream stream;
    long stream_size = 0;

    long GetSize(std::ifstream* s_ptr);
};

}

#endif  // CHIP8_ROM_H
