// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef CHIP8_ROM_H
#define CHIP8_ROM_H

#include <string_view>
#include <fstream>
#include <vector>
#include <exception>

namespace c8 {

class Rom {
public:
    // 0xDFF = 3,583 = 4,095 (Chip8 RAM) - 512 (Reserved RAM)
    static constexpr int kMaxRomFileSize = 0xDFF;

    ~Rom();

    [[nodiscard]] bool WithFile(std::string_view filename);
    std::string Data() const;

private:
    std::ifstream stream;
    long stream_size = 0;
};

}

#endif  // CHIP8_ROM_H
