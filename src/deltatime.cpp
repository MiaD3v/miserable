#include <cstdint>
#include <SDL3/SDL.h>
#include "deltatime.hpp"

namespace MS = Miserable;

float MS::dt = 0.;

static uint64_t last_frame_start = 0;

void MS::updateDeltaTime() {
    uint64_t time_now = SDL_GetTicksNS();
    uint64_t nano_delta = time_now - last_frame_start;
    last_frame_start = time_now;

    MS::dt = nano_delta / 1.0e9;
}

