// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "emulator.h"
#include "core/display.h"

using namespace c8;

bool Emulator::Initialize() {
    return client->Initialize(Display::width(), Display::height());
}

void Emulator::LoadRom(const Rom& rom) {
    cpu.Reset();
    cpu.ReadProgram(rom.Data());
}

void Emulator::Start() {
    // TODO: while(cpu.ProgramLoaded())
}
