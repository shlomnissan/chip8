// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "emulator.h"

using namespace c8;

bool Emulator::Initialize() {
    return window.Initialize(
        Display::width(),
        Display::height(),
        "Chip 8"
    );
}

void Emulator::LoadRom(const Rom& rom) {
    chip8.Reset();
    chip8.ReadProgram(rom.Data());
}

void Emulator::Start() {
    while (chip8.ProgramLoaded() && window.running) {
        Update();
        Draw();
    }
}

void Emulator::Update() {
    window.PollEvents([](int key, int value) {
        // TODO: implement
    });
    chip8.Tick();
}

void Emulator::Draw() {
    window.ClearScreen();

    for (int y = 0; y < Display::kHeight; ++y) {
        for (int x = 0; x < Display::kWidth; ++x) {
            // TODO: should be replaced with Chip8 display
            if (display[x + (y * Display::kWidth)]) {
                window.DrawBlock(x, y, Display::kScale);
            }
        }
    }

    window.PresentBackBuffer();
}