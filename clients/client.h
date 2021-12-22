// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef CHIP8_CLIENT_H
#define CHIP8_CLIENT_H

namespace c8 {

class Client {
public:
    bool running;

    [[nodiscard]] virtual bool Initialize(int width, int height) = 0;
    virtual void PollEvents() = 0;
    virtual void Draw() = 0;

    virtual ~Client() = default;
};

}

#endif  // CHIP8_CLIENT_H
