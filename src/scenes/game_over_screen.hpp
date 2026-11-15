#pragma once
#include <SDL3/SDL.h>
#include <cstddef>

#include "../scene.hpp"
#include "../image.hpp"
#include "../renderer.hpp"

namespace Miserable {
    class GameOverScene {
        public:
            bool goToNextScene = false;

            GameOverScene(SDL_Renderer *ren);
            Layer* frame();
            void Resize(int w, int h);
            ~GameOverScene();
        private:
            Layer *mBG = nullptr;
            Layer *mGameOver = nullptr;
            TTF_TextEngine *mTtfEngine = nullptr;
            TTF_Text *mTtfText = nullptr;
            TTF_Font *mFont = nullptr;
    };

    
}
       