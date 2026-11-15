#include <SDL3/SDL.h>

#include "miserable.hpp"
#include "panic.hpp"
#include "deltatime.hpp"
#include "scenes/main_scene.hpp"
#include "scenes/game_over_screen.hpp"

namespace MS = Miserable;

const char *WINDOW_NAME = "Miserable";

constexpr int WIDTH  = 512;
constexpr int HEIGHT = 512;

MS::Game::Game() {
    if (!SDL_Init(SDL_INIT_VIDEO)) PANIC("Failed to initialize SDL3!");
    if (!TTF_Init()) PANIC("Failed to initialize SDL3_ttf!");

    if (!SDL_CreateWindowAndRenderer(WINDOW_NAME,
                                     WIDTH, HEIGHT,
                                     SDL_WINDOW_RESIZABLE,
                                     &mWindow, &mRenderer))
        PANIC("Failed to create window and renderer!");

    mRendererEngine = MS::Renderer(mWindow, mRenderer, WIDTH, HEIGHT);

    mRendererEngine.render(nullptr);

}

int MS::Game::run() {

    MS::MainScene mainScene(mRenderer);
    MS::GameOverScene gameOverScene(mRenderer);
    mainScene.next = &gameOverScene;
    Layer *mCurrentScene = mainScene.frame();

    SDL_Event event;
    bool running = true;
    while (running) {
        MS::updateDeltaTime();
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT: running = false; break;
                case SDL_EVENT_WINDOW_CLOSE_REQUESTED: running = false; break;
                case SDL_EVENT_WINDOW_RESIZED: mainScene.Resize(event.window.data1, event.window.data2);
            }
        }
        
        if(!mainScene.dead){
            mCurrentScene = mainScene.frame();
        } else {
            mCurrentScene = mainScene.next->frame();
            gameOverScene.ChangeAliveText(mainScene.frameCount);
        }
        mRendererEngine.render(mCurrentScene);

    }

    return 0;
}

MS::Game::~Game() {
    ;
}

