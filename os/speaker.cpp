// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "speaker.h"

#include <iostream>

bool c8::Speaker::Initialize() {
    SDL_AudioSpec spec;
    spec.freq = kFrequency;
    spec.format = AUDIO_U8;
    spec.channels = 1;
    spec.samples = 2048;
    spec.callback = nullptr;
    spec.userdata = nullptr;

    device = SDL_OpenAudioDevice(nullptr, 0, &spec, nullptr, SDL_AUDIO_ALLOW_ANY_CHANGE);

    if (!device) {
        std::cerr << "SDL Error: " << SDL_GetError() << '\n';
        return false;
    }

    SDL_PauseAudioDevice(device, 0);

    return true;
}

void c8::Speaker::Beep(int length) {
    if (SDL_GetQueuedAudioSize(device) < (kSamplesPerFrame * 2)) {
        SineWave(length);
        SDL_QueueAudio(device, audio_buffer.data(), length);
    }
}

void c8::Speaker::SineWave(int length) {
    for (int i = 0; i < length; i++) {
        audio_buffer[i] = (unsigned char) ((kAmplitude * sin(wave_position)) + kBias);
        wave_position += wave_increment;
    }
}

c8::Speaker::~Speaker() {
    SDL_PauseAudioDevice(device, 1);
    if (device) {
        SDL_CloseAudioDevice(device);
    }
}