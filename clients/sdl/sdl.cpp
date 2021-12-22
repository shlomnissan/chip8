// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "sdl.h"

using namespace c8;

bool SDL::Initialize(int width, int height) {
    return true;
}

void SDL::PollEvents() {

}

void SDL::Draw() {

}

SDL::~SDL() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
