#include <SDL3/SDL.h>

namespace Miserable {
    class Game {
        public:

            SDL_Window *mWindow;
            SDL_Renderer *mRenderer;

            explicit Game();
            int run();
            ~Game();
    };
};

