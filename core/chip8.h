// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef CHIP8_CHIP8_H
#define CHIP8_CHIP8_H

#include <vector>
#include <string_view>

#include "memory.h"
#include "display.h"
#include "input.h"
#include "random.h"
#include "types.h"

namespace c8 {

class Chip8 {
public:
    void Reset();
    void ReadProgram(std::string_view buffer);
    void SetKey(int key, int value);
    void UpdateDelayTimer();
    bool UpdateSoundTimer();
    void Tick();

    uint8_t DisplayAt(int loc);

    [[nodiscard]] bool ProgramLoaded() const;

private:
    Cpu cpu;
    Memory ram;
    Display display;
    Input input;
    Random rand;

    bool program_loaded = false;
};

}

#endif  // CHIP8_CHIP8_H
