#pragma once
#include <SDL3/SDL.h>

#include "../scene.hpp"
#include "../renderer.hpp"

namespace Miserable {
    class GameOverScene {
        public:
            bool goToNextScene = false;
            int secondsAlive;

            GameOverScene(SDL_Renderer *ren);
            Layer* frame();
            void Resize(int w, int h);
            void ChangeAliveText(int);
            ~GameOverScene();
        private:
            Layer *mBG = nullptr;
            Layer *mGameOver = nullptr;
            Layer *mSeconds = nullptr;
            TTF_TextEngine *mTtfEngine = nullptr;
            TTF_Text *mTtfText = nullptr;
            TTF_Font *mFont = nullptr;
            TTF_Font *msFont = nullptr;
            TTF_Text *sText = nullptr;
    };

    
}
       