// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "memory.h"

#include <cstring>
#include <stdexcept>

using namespace c8;

Memory::Memory() {
    memcpy(memory.data(), kSprites.data(), kSprites.size());
}

uint8_t &Memory::operator[](int index) {
    if (index < 0 || index >= 0x1000) {
        throw std::range_error("Error trying to access memory address that's out of range");
    }
    return memory[index];
}

void Memory::SaveProgram(const char* source, std::size_t size) {
    memcpy(memory.data() + kStartAddress, source, size);
}

void Memory::Reset() {
    memset(memory.data() + kStartAddress, 0, memory.size() - kStartAddress);
}
