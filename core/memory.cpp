// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "memory.h"

#include <stdexcept>
#include <algorithm>

#include "../messages.h"

using namespace c8;

Memory::Memory() {
    std::ranges::copy(begin(kSprites), end(kSprites), begin(memory));
}

uint8_t &Memory::operator[](int index) {
    if (index < 0 || index >= 0x1000) {
        throw std::range_error(message::MemoryRangeError);
    }
    return memory[index];
}

void Memory::SaveProgram(std::string_view source) {
    std::ranges::copy(begin(source), end(source), begin(memory) + kStartAddress);
}

void Memory::Reset() {
    std::fill(begin(memory) + kStartAddress, end(memory), 0);
}
