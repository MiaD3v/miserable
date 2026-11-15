#pragma
#include <cstddef>

#include <SDL3/SDL.h>

#include "../scene.hpp"
#include "/game_over_screen.hpp"
#include "../image.hpp"
#include "../inventory.hpp"

namespace Miserable {
    class MainScene {
        public:
            bool dead = false;
            GameOverScene *next;

            MainScene(SDL_Renderer *ren);
            Layer* frame();
            void Resize(int w, int h);
            bool IsRectClicked(float msX, float msY, Rectangle *button);
            void bearzos_attack();
            ~MainScene();
        private:

            // 0 is empty, 1 is full!
            float mBladderFilled = 0.f;
            bool pissing = false;
            Layer *mPlayerArea = nullptr;
            Image mTestImage;
            Image playerImageNeutral;
            Image backgroundImage;
            Image backgroundPeekImage;
            Image backgroundOpenImage;
            Image dollyImage;
            Image bearzosNeutralImage;
            Image bearzosMadImage;
            Image bearzosGladImage;
            Image boxImage;
            Image jankBoxImage;
            Inventory inventory;
            Layer *mBearzos = nullptr;
            Layer *mBG = nullptr;
            Layer *mBoxes = nullptr;
            Layer *mShop = nullptr;
            Layer *mGui = nullptr;
            Layer *mJankBox = nullptr;
            Rectangle *unload_doll_button;
            Rectangle *load_doll_button; 
            Rectangle *bottle_button; 
            Rectangle *upgrade_button;
            bool held_down = false;
            int height = 512;
            int width = 512;
            struct {
                float timeSinceBearzos = 0.0f;
                int bearzosAttackStage = 0;
                float fluff_bearzos_countdown = 50.0;
                bool pissing_seen = false;
                float curtainCloseCooldown = 0.0;
            } bearzos;
            double mLoadOffset = 56;
            struct {
                // All of these are 0 - 1;
                float x = 0.f;
                // Negative if not loading or unloading respectively;
                float loadingProgress = -1.f, unloadingProgress = -1.f;
                size_t nLoadingDolls = 0;
                size_t nUnloadingDolls = 0;
                int hp = 100;
            } player;

            TTF_TextEngine *mTtfEngine = nullptr;
            TTF_Text *mTtfText = nullptr;
            TTF_Font *mFont = nullptr;

    };
};

