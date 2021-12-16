#include <iostream>
#include <string_view>
#include <gflags/gflags.h>

const auto valid_path_message = "Specify a path to a valid Chip-8 program";
DEFINE_string(rom, "", valid_path_message);

bool validateRom(std::string_view value) {
    return !value.empty();
}

int main(int argc, char** argv) {
    gflags::SetUsageMessage("chip8 -rom <PATH>");
    gflags::SetVersionString("1.0.0");
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    if (!validateRom(FLAGS_rom)) {
        std::cerr << valid_path_message << "\n" << "Usage: chip8 -rom <PATH>\n";
        return EXIT_FAILURE;
    }

    // TODO: instantiate emulator
    // TODO: load rom
    // TODO: run

    return EXIT_SUCCESS;
}
