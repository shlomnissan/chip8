// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "emulator.h"

using namespace c8;

bool Emulator::Initialize(int cycles_per_sec) {
    this->cycles_per_sec = cycles_per_sec;

    auto didInitWindow = window.Initialize(
        Display::width(),
        Display::height(),
        "Chip 8"
    );

    auto didInitAudio = speaker.Initialize();

    return didInitWindow && didInitAudio;
}

void Emulator::LoadRom(const Rom& rom) {
    chip8.Reset();
    chip8.ReadProgram(rom.Data());
}

void Emulator::Start() {
    StartMainLoop({
        .frames_per_sec = kFramesPerSec,
        .is_running = [&]() {
            return chip8.ProgramLoaded() && window.running;
        }
    });
}

void Emulator::Update() {
    chip8.UpdateDelayTimer();

    auto shouldBeep = chip8.UpdateSoundTimer();
    if (shouldBeep) {
        speaker.Beep(1500);
    }

    window.PollEvents([&](int key, int value) {
        chip8.SetKey(key, value);
    });

    for (int i = 0; i < cycles_per_sec; ++i) {
        chip8.Tick();
    }
}

void Emulator::Draw() {
    window.ClearScreen();
    for (int y = 0; y < Display::kHeight; ++y) {
        for (int x = 0; x < Display::kWidth; ++x) {
            if (chip8.DisplayAt(x + (y * Display::kWidth))) {
                window.DrawPixel(x, y, Display::kScale);
            }
        }
    }

    window.PresentBackBuffer();
}