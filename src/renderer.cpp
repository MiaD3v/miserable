#include <print>
#include <SDL3/SDL.h>
#include <cassert>
#include "renderer.hpp"

#include "panic.hpp"
#include "image.hpp"

namespace MS = Miserable;

MS::Renderer::Renderer() {
    ;
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

            SDL_FColor col = {
                .r = 1.f,
                .g = 1.f,
                .b = 1.f,
                .a = 1.f,
            };

            if (!rect->image) {
                col = {
                    .r = rect->r / 255.f,
                    .g = rect->g / 255.f,
                    .b = rect->b / 255.f,
                    .a = rect->a / 255.f,
                };
            }

            SDL_Vertex verts[] = {
                {
                    .position = {(float)rect->x, (float)rect->y},
                    .color = col,
                    .tex_coord = {0, 0},
                },
                {
                    .position = {(float)(rect->x + rect->w), (float)rect->y},
                    .color = col,
                    .tex_coord = {1, 0},
                },
                {
                    .position = {(float)rect->x, (float)(rect->y + rect->h)},
                    .color = col,
                    .tex_coord = {0, 1},
                },
                {
                    .position = {
                        (float)(rect->x + rect->w),
                        (float)(rect->y + rect->h),
                    },
                    .color = col,
                    .tex_coord = {1, 1},
                },
            };

            if (!rect->text) {

                (void) SDL_SetRenderDrawColor(
                    mRenderer,
                    rect->r, rect->g, rect->b, rect->a);

                SDL_Texture *tex =
                    (rect->image) ? rect->image->mTexture : nullptr;
                (void) SDL_RenderGeometry(mRenderer,
                                          tex,
                                          verts,
                                          4,
                                          (int[]){0,1,2,1,2,3}, 6);

            } else {
                assert(rect->text);
                (void) TTF_SetTextColor(rect->text, rect->r, rect->g, rect->b, rect->a);
                (void) TTF_DrawRendererText(rect->text, rect->x, rect->y);
            }
        }
    }
    SDL_RenderPresent(mRenderer);
}

MS::Renderer::~Renderer() {
    ;
}

