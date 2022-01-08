// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef CHIP8_TYPES_H
#define CHIP8_TYPES_H

#include <cinttypes>
#include <sstream>

namespace c8 {

using size_op = uint16_t; // size of opcode

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

#endif  // CHIP8_TYPES_H
