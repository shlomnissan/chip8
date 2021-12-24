// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef CHIP8_WINDOW_H
#define CHIP8_WINDOW_H

#include <SDL2/SDL.h>
#include <string_view>

namespace c8 {

class Window {
public:
    bool running = false;

    [[nodiscard]] bool Initialize(int width, int height, std::string_view title);
    void PollEvents();
    void Draw();

    ~Window();

private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
};

}


#endif  // CHIP8_WINDOW_H
