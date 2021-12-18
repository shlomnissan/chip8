// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "emulator.h"

using namespace c8;

void Emulator::LoadRom(Rom* rom) {
    cpu.Reset();
    cpu.ReadProgram(rom->Data());
}

void Emulator::Start() {
    // TODO: implement
}
