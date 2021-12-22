// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef CHIP8_SDL_H
#define CHIP8_SDL_H

#include "../client.h"

#include <SDL2/SDL.h>

namespace c8 {

class SDL : public Client {
public:
    [[nodiscard]] bool Initialize(int width, int height, std::string_view title) override;
    void PollEvents() override;
    void Draw() override;

    ~SDL() override;

private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
};

}


#endif  // CHIP8_SDL_H
