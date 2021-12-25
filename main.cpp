#include <iostream>
#include <string_view>
#include <gflags/gflags.h>

#include "emulator.h"
#include "messages.h"
#include "core/rom.h"

DEFINE_string(rom, "", c8::message::InvalidPath);

int main(int argc, char** argv) {
    gflags::SetUsageMessage("chip8 -rom <PATH>");
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
    if (!emulator.Initialize()) {
        std::cerr << c8::message::FailedToInit << '\n';
        return EXIT_FAILURE;
    }

    emulator.LoadRom(rom);
    emulator.Start();

    return EXIT_SUCCESS;
}
