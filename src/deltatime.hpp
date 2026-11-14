#pragma once
#include <cstdint>
#include <SDL3/SDL.h>

namespace Miserable {
    class DeltaTime {
        double deltatime;
        uint64_t last_frame_start;
        public:
        explicit DeltaTime();
        void start_frame();
        double get_delta_time();
    };
    
}
extern Miserable::DeltaTime del;