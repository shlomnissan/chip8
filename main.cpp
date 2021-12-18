#include <iostream>
#include <string_view>
#include <gflags/gflags.h>

#include "emulator.h"
#include "core/rom.h"

const auto kInvalidPathMessage = "Specify a path to a valid Chip-8 program";
const auto kInvalidRomMessage = "Unable to read Chip-8 program";

DEFINE_string(rom, "", kInvalidPathMessage);

int main(int argc, char** argv) {
    gflags::SetUsageMessage("chip8 -rom <PATH>");
    gflags::SetVersionString("1.0.0");
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    if (FLAGS_rom.empty()) {
        std::cerr << kInvalidPathMessage << "\n" << "Usage: chip8 -rom <PATH>\n";
        return EXIT_FAILURE;
    }

    c8::Rom rom;
    if (!rom.WithFile(FLAGS_rom)) {
        std::cerr << kInvalidRomMessage << '\n';
        return EXIT_FAILURE;
    }

    c8::Emulator emulator;
    emulator.LoadRom(rom);
    emulator.Start();

    return EXIT_SUCCESS;
}
