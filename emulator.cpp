// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "emulator.h"

using namespace c8;

bool Emulator::Initialize() {
    // TODO: initialize window
    return true;
}

void Emulator::LoadRom(const Rom& rom) {
    cpu.Reset();
    cpu.ReadProgram(rom.Data());
}

void Emulator::Start() {
    // TODO: while(cpu.ProgramLoaded())
}
