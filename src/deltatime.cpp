#include "deltatime.hpp"

explicit Miserable::DeltaTime::DeltaTime() {
    deltatime = 0.0;
    last_frame_start = 0;
}
Miserable::DeltaTime::start_frame() {
    uint64_t time_now = SDL_GetTicksNS();
    if(!last_frame_start)
        return;
    uint64_t nano_delta = time_now - last_frame_start;
    uint64_t last_frame_start = time_now;

    deltatime = nano_delta / 1.0e9;
}
double Miserable::DeltaTime::get_delta_time() {
    return deltatime;
}
