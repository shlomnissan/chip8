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

void Window::PresentBackBuffer() {
    SDL_RenderPresent(renderer);
}

void Window::ClearScreen() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
    SDL_RenderClear(renderer);
}

void Window::DrawBlock(int x, int y, int scale) {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_Rect block {x * scale, y * scale, scale, scale};
    SDL_RenderDrawRect(renderer, &block);
    SDL_RenderFillRect(renderer, &block);
}

Window::~Window() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
