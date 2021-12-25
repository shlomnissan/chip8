// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "rom.h"

#include <sstream>

using namespace c8;

bool Rom::WithFile(std::string_view filename) {
    stream.open(filename.data(), std::ios::binary);
    if (!stream) {
        return false;
    }
    stream_size = GetSize(&stream);
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

long Rom::GetSize(std::ifstream* s_ptr) {
    auto& s = *s_ptr;
    s.seekg(0, std::ios::end);
    auto size = stream.tellg();
    s.seekg(0, std::ios::beg);
    return size;
}

Rom::~Rom() {
    if (stream) {
        stream.close();
    }
}
