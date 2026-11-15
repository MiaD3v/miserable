#pragma once
#include <SDL3/SDL.h>
#include "renderer.hpp"

namespace Miserable {
    class Game {
        public:
            explicit Game();
            int run();
            ~Game();

        private:
            SDL_Window *mWindow;
            SDL_Renderer *mRenderer;
            Renderer mRendererEngine;
            Layer *mCurrentScene;
    };
};

