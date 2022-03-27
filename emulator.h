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
#include "os/speaker.h"

namespace c8 {

class Emulator : public MainLoop {
public:
    [[nodiscard]] bool Initialize(int cycles_per_sec);
    void LoadRom(const Rom& rom);
    void Start();

private:
    static constexpr int kFramesPerSec = 60;

    int cycles_per_sec;

    Chip8 chip8;
    Display display;
    Window window;
    Speaker speaker;

    void Update() override;
    void Draw() override;
};

}

#endif  // CHIP8_EMULATOR_H
