#include <cstddef>

#include <SDL3/SDL.h>

#include "../scene.hpp"
#include "../image.hpp"

namespace Miserable {
    class MainScene {
        public:
            MainScene(SDL_Renderer *ren);
            Layer* frame();
            void Resize(int w, int h);
            bool IsRectClicked(float msX, float msY, Rectangle *button);
            ~MainScene();
        private:
            Layer *mPlayerArea = nullptr;
            Image mTestImage;
            Layer *mBG = nullptr;
            Layer *mBoxes = nullptr;
            Layer *mShop = nullptr;
            Rectangle *doll_button; 
            Rectangle *bottle_button; 
            Rectangle *upgrade_button;
            bool held_down = false;

            double mLoadOffset = 112;
            struct {
                // All of these are 0 - 1;
                float x = 0.f;
                // Negative if not loading or unloading respectively;
                float loadingProgress = -1.f, unloadingProgress = -1.f;
                size_t nLoadingDolls = 0;
                size_t nUnloadingDolls = 0;
            } player;
    };
};

