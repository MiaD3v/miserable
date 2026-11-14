#include <print>
#include <SDL3/SDL.h>
#include "renderer.hpp"

#include "panic.hpp"
#include "image.hpp"

namespace MS = Miserable;

MS::Renderer::Renderer() {
    
}

MS::Renderer::Renderer(SDL_Window *win, SDL_Renderer *ren, int w, int h)
    : mWindow(win), mRenderer(ren)
    , mW(w)
    , mH(h) {
    SDL_SetRenderLogicalPresentation(mRenderer, 512, 512, SDL_LOGICAL_PRESENTATION_LETTERBOX);
    return;

}

void MS::Renderer::resize(int w, int h) {
    if (!(mWindow && mRenderer)) PANIC("UNINITIALIZED RENDERER");
    mW = w;
    mH = h;
}

void MS::Renderer::render(MS::Layer *tree) {
    if (!(mWindow && mRenderer)) PANIC("UNINITIALIZED RENDERER");
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    SDL_RenderClear(mRenderer);
    for (MS::Layer *layer = tree; layer != nullptr; layer = layer->next) {
        for (MS::Rectangle *rect = layer->rects;
             rect != nullptr;
             rect = rect->next) {

            SDL_FRect SDLRect = {
                .x = (float)rect->x,
                .y = (float)rect->y,
                .w = (float)rect->w,
                .h = (float)rect->h,
            };

            if (!rect->image) {

                (void )SDL_SetRenderDrawColor(
                    mRenderer,
                    rect->r, rect->g, rect->b, rect->a);
                (void) SDL_RenderFillRect(mRenderer, &SDLRect);

            } else {

                (void) SDL_RenderTexture(mRenderer, rect->image->mTexture, nullptr, &SDLRect);

            }
        }
    }
    SDL_RenderPresent(mRenderer);
}

MS::Renderer::~Renderer() {
    ;
}

