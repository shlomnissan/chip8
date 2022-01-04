// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef CHIP8_CHIP8_H
#define CHIP8_CHIP8_H

#include <vector>
#include <string_view>
#include <sstream>

#include "cpu.h"
#include "memory.h"
#include "display.h"
#include "types.h"

namespace c8 {

class Chip8 {
public:
    void Reset();
    void ReadProgram(std::string_view buffer);
    void Tick();

    [[nodiscard]] bool ProgramLoaded() const;

private:
    Cpu cpu;
    Memory ram;
    Display display;

    bool program_loaded = false;
};

struct bad_opcode : public std::exception {
    std::string message;

    explicit bad_opcode(size_op c) {
        std::stringstream stream;
        stream << "Unknown opcode 0x" << std::hex << c;
        message = stream.str();
    }

    [[nodiscard]] const char* what() const noexcept override {
        return message.c_str();
    }
};

}

#endif  // CHIP8_CHIP8_H
