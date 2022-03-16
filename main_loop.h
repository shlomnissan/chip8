// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef CHIP8_MAIN_LOOP_H
#define CHIP8_MAIN_LOOP_H

#include <chrono>
#include <functional>

using namespace std::chrono;

struct MainLoopArgs {
    int frames_per_sec;
    const std::function<bool()>& is_running;
};

class MainLoop {
public:
    void StartMainLoop(MainLoopArgs args) {
        auto start_time = GetTime();
        while (args.is_running()) {
            auto delta = GetTime() - start_time;
            if (delta > (1000.0 / args.frames_per_sec)) {
                start_time = GetTime();
                Update();
                Draw();
            }
        }
    }

private:
    virtual void Update() = 0;
    virtual void Draw() = 0;

    inline long GetTime() {
        return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    }
};

#endif  // CHIP8_MAIN_LOOP_H
