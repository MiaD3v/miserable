#pragma once
#include <cstddef>
#include <string>
#include <cstdint>

#include <SDL3/SDL.h>

#include "../scene.hpp"
#include "game_over_screen.hpp"
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
            TTF_Text* IntToTTF(int);
            ~MainScene();
        private:

            // 0 is empty, 1 is full!
            float mBladderFilled = 0.f;
            bool pissing = false;
            Layer *mPlayerArea = nullptr;
            Image mTestImage;
            Image playerImageNeutral;
            Image playerImageRight;
            Image backgroundImage;
            Image backgroundPeekImage;
            Image backgroundOpenImage;
            Image dollyImage;
            Image bearzosNeutralImage;
            Image bearzosMadImage;
            Image bearzosGladImage;
            Image boxImage;
            Image upgradeImage;
            Image dollImage;
            Image bottleImage;
            Image jankBoxImage;
            Inventory inventory;
            Layer *mBearzos = nullptr;

            Layer *mBG = nullptr;
            Layer *mBoxes = nullptr;
            Layer *mShop = nullptr;
            Layer *mGui = nullptr;
            Layer *mJankBox = nullptr;
            Layer *mMoney = nullptr;

            Rectangle *unload_doll_button;
            Rectangle *load_doll_button; 
            Rectangle *bottle_button; 
            Rectangle *upgrade_button;
            Rectangle *load_bar_bg;
            Rectangle *load_bar_mg;
            Rectangle *load_bar_fg;
            Rectangle *hp_display;
            Rectangle *udoll_display;
            Rectangle *ldoll_display;
            Rectangle *bottle_display;
            Rectangle *level_display;
            bool held_down = false;
            int height = 512;
            int width = 512;
            struct {
                float timeSinceBearzos = 0.0f;
                int bearzosAttackStage = 0;
                float fluff_bearzos_countdown = 30.0;
                bool pissing_seen = false;
                float curtainCloseCooldown = 0.0;
            } bearzos;
            double mLoadOffset = 56;
            struct {
                // All of these are 0 - 1;
                float x = 0.f;
                float loadingProgress = 0.f;
                float loadingSpeed = 15;
                size_t nLoadingDolls = 0;
                size_t nUnloadingDolls = 0;

                int hp = 100;
            } player;

            TTF_TextEngine *mTtfEngine = nullptr;
            TTF_Font *mFont = nullptr;

            TTF_Text *moneyText = nullptr;
            TTF_Text *hpText = nullptr;
            TTF_Text *ldollText = nullptr;
            TTF_Text *udollText = nullptr;
            TTF_Text *bottleText = nullptr;
            TTF_Text *levelText = nullptr;

            float mLoaded = 0.f;

            float loadTime = 7.5f;

            float moneyMult = 500;
            float unloadMult = 1;
            float loadMult = 1;

            float frameCount;
            std::string getMoneyAsString(uint64_t money);

    };
};

