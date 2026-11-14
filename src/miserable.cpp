#include <SDL3/SDL.h>

#include "miserable.hpp"
#include "panic.hpp"
#include "deltatime.hpp"
#include "scenes/main_scene.hpp"

namespace MS = Miserable;

const char *WINDOW_NAME = "Miserable";

constexpr int WIDTH  = 512;
constexpr int HEIGHT = 512;

MS::Game::Game() {
    if (!SDL_Init(SDL_INIT_VIDEO)) PANIC("Failed to initialize SDL3!");

    if (!SDL_CreateWindowAndRenderer(WINDOW_NAME,
                                     WIDTH, HEIGHT,
                                     SDL_WINDOW_RESIZABLE,
                                     &mWindow, &mRenderer))
        PANIC("Failed to create window and renderer!");

    mRendererEngine = MS::Renderer(mWindow, mRenderer, WIDTH, HEIGHT);

    mRendererEngine.render(nullptr);

}

int MS::Game::run() {

    MS::MainScene mainScene;

    SDL_Event event;
    bool running = true;
    while (running) {
        MS::updateDeltaTime();
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT: running = false; break;
                case SDL_EVENT_WINDOW_CLOSE_REQUESTED: running = false; break;
            }
        }

        mRendererEngine.render(mainScene.frame());

    }

    return 0;
}

MS::Game::~Game() {
    ;
}

