#include <cstddef>

#include "../scene.hpp"

namespace Miserable {
    class MainScene {
        public:
            MainScene();
            Layer* frame();
            void Resize(int w, int h);
            ~MainScene();
        private:
            Layer *mBG = nullptr;
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

