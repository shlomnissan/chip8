// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "rom.h"

#include <sstream>

using namespace c8;

bool Rom::WithFile(std::string_view filename) {
    std::ifstream s {filename.data(), std::ios::binary};

    stream.open(filename.data(), std::ios::binary | std::ios::ate);
    if (!stream) {
        return false;
    }
    stream_size = stream.tellg();
    stream.seekg(0);
    if (stream_size == 0 || stream_size > kMaxRomFileSize) {
        return false;
    }
    return true;
}

std::string Rom::Data() const {
    std::ostringstream ss;
    ss << stream.rdbuf();
    return ss.str();
}

Rom::~Rom() {
    if (stream) {
        stream.close();
    }
}
