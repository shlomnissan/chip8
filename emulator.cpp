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
    cpu.Reset();
    cpu.ReadProgram(rom.Data());
}

void Emulator::Start() {
    while (cpu.ProgramLoaded() && window.running) {
        window.PollEvents();
        cpu.Tick();
    }
}
