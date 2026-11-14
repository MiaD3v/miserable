#include <cstdint>
#include <SDL/SDL_timer.h>

namespace Miserable {
    DeltaTime del();

    class DeltaTime {
        double deltatime;
        uint64_t last_frame_start;
        public:
        explicit DeltaTime();
        void start_frame();
        double get_delta_time();
    }
}