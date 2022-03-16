// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef CHIP8_EMULATOR_H
#define CHIP8_EMULATOR_H

#include <memory>

#include "main_loop.h"
#include "core/chip8.h"
#include "core/rom.h"
#include "core/display.h"
#include "os/window.h"

namespace c8 {

class Emulator : public MainLoop {
public:
    [[nodiscard]] bool Initialize();
    void LoadRom(const Rom& rom);
    void Start();

private:
    Chip8 chip8;
    Display display;
    Window window;

    void Update() override;
    void Draw() override;
};

}

#endif  // CHIP8_EMULATOR_H
