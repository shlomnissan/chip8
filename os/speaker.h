// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef CHIP8_SPEAKER_H
#define CHIP8_SPEAKER_H

#include <SDL.h>
#include <array>

namespace c8 {

class Speaker {
public:
    ~Speaker();

    bool Initialize();

    void Beep(int length);

private:
    static constexpr double kFrequency = 48000;
    static constexpr double kTone = 440;
    static constexpr int kAmplitude = 7;
    static constexpr int kBias = 127;
    static constexpr int kSamplesPerFrame = (kFrequency / 60) * 3;

    std::array<unsigned char, kSamplesPerFrame * 30> audio_buffer;

    double wave_position = 0;
    double wave_increment = (kTone * (2.0 * M_PI)) / kFrequency;

    SDL_AudioDeviceID device;

    void SineWave(int length);
};

}


#endif  // CHIP8_SPEAKER_H
