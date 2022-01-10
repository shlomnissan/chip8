// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef CHIP8_TYPES_H
#define CHIP8_TYPES_H

#include <cinttypes>
#include <sstream>

namespace c8 {

struct Cpu {
    std::array<uint8_t, 0x10> registers = {0};
    std::array<uint16_t, 0x10> stack = {0};

    uint16_t I = {0};
    uint16_t pc = {0}; // program counter
    uint16_t sp = {0}; // stack pointer
    uint8_t t_delay = 0; // delay timer
    uint8_t t_sound = 0; // sound timer
};

struct Opcode {
    uint16_t in;

    Opcode(uint16_t opcode): in(opcode) {}

    uint16_t x() { return (in & 0x0F00) >> 8; }
    uint16_t y() { return (in & 0x00F0) >> 4; }
    uint16_t byte() { return in & 0x00FF; }
    uint16_t address() { return in & 0x0FFF; }

    uint16_t high() { return in >> 12; }
    uint16_t low() { return in & 0x000F; }
};

struct bad_opcode : public std::exception {
    std::string message;

    explicit bad_opcode(Opcode c) {
        std::stringstream stream;
        stream << "Unknown opcode 0x" << std::hex << c.in;
        message = stream.str();
    }

    [[nodiscard]] const char* what() const noexcept override {
        return message.c_str();
    }
};

}

#endif  // CHIP8_TYPES_H
