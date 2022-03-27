// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef CHIP8_WINDOW_H
#define CHIP8_WINDOW_H

#include <SDL2/SDL.h>
#include <string_view>
#include <functional>

namespace c8 {

class Window {
public:
    bool running = false;

    ~Window();

    [[nodiscard]] bool Initialize(int width, int height, std::string_view title);
    void PollEvents(const std::function<void(int, int)>& on_key);
    void PresentBackBuffer();
    void ClearScreen();
    void DrawPixel(int x, int y, int scale);

private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
};

}


#endif  // CHIP8_WINDOW_H
