#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "image.hpp"
#include "panic.hpp"

namespace MS = Miserable;

MS::Image::Image(const char *path, SDL_Renderer *ren) {
    mSurface = IMG_Load(path);
    if (!mSurface) PANIC("Failed to create image surface!");

    mTexture = SDL_CreateTextureFromSurface(ren, mSurface);
    if (!mTexture) PANIC("Failed to create a texture!");
}

MS::Image::~Image() {
    SDL_DestroyTexture(mTexture);
    SDL_DestroySurface(mSurface);
}

