// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef CHIP8_EMULATOR_H
#define CHIP8_EMULATOR_H

#include <memory>

#include "core/cpu.h"
#include "core/rom.h"
#include "core/display.h"
#include "clients/sdl/sdl.h"

namespace c8 {

class Emulator {
public:
    [[nodiscard]] bool Initialize() const;
    void LoadRom(const Rom& rom);
    void Start();

private:
    Cpu cpu;
    Display display;

    std::unique_ptr<Client> client = std::make_unique<SDL>();
};

}

#endif  // CHIP8_EMULATOR_H
