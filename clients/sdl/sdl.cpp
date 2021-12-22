// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "sdl.h"

using namespace c8;

bool SDL::Initialize(int width, int height, std::string_view title) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return false;
    }

    SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
    if (window == nullptr || renderer == nullptr) return false;
    SDL_SetWindowTitle(window, title.data());

    running = true;
    return true;
}

void SDL::PollEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
    }
}

void SDL::Draw() {

}

SDL::~SDL() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
