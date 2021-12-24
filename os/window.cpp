// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "window.h"

using namespace c8;

bool Window::Initialize(int width, int height, std::string_view title) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return false;
    }

    SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
    if (window == nullptr || renderer == nullptr) return false;
    SDL_SetWindowTitle(window, title.data());

    running = true;
    return true;
}

void Window::PollEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
    }
}

void Window::Draw() {

}

Window::~Window() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
