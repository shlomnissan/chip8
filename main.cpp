#include <iostream>
#include <gflags/gflags.h>

#include "emulator.h"
#include "messages.h"
#include "core/rom.h"

DEFINE_string(rom, "", c8::message::FlagRomHelp);
DEFINE_int32(cycles_per_sec, 10, c8::message::FlagCyclesHelp);

int main(int argc, char** argv) {
    gflags::SetUsageMessage("chip8 -rom roms/invaders.ch8 -cycles_per_sec 10");
    gflags::SetVersionString("1.0.0");
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    if (FLAGS_rom.empty()) {
        std::cerr << c8::message::InvalidPath << "\n" << "Usage: chip8 -rom <PATH>\n";
        return EXIT_FAILURE;
    }

    c8::Rom rom;
    if (!rom.WithFile(FLAGS_rom)) {
        std::cerr << c8::message::InvalidRom << '\n';
        return EXIT_FAILURE;
    }

    c8::Emulator emulator;
    if (!emulator.Initialize(FLAGS_cycles_per_sec)) {
        std::cerr << c8::message::FailedToInit << '\n';
        return EXIT_FAILURE;
    }

    emulator.LoadRom(rom);
    emulator.Start();

    return EXIT_SUCCESS;
}
