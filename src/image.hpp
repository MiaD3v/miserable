#include <SDL3/SDL.h>

namespace Miserable {
    class Image {
        public:
            SDL_Surface *mSurface = nullptr;
            SDL_Texture *mTexture = nullptr;

            explicit Image(const char *path, SDL_Renderer *ren);
            ~Image();
    };
}

