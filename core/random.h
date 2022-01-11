// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef CHIP8_RANDOM_H
#define CHIP8_RANDOM_H

#include <random>

namespace c8 {

class Random {
public:
    template <typename T>
    void seed(T val) {
        rand_engine.seed(val);
    }

    [[nodiscard]] virtual uint8_t operator()() {
        return rand_dist(rand_engine);
    }

private:
    std::default_random_engine rand_engine;
    std::uniform_int_distribution<uint8_t> rand_dist {0x00, 0xFF};
};

}

#endif  // CHIP8_RANDOM_H
