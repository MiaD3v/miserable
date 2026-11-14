#include "../renderer.hpp"
#include "main_scene.hpp"
#include <print>
#include <SDL3/SDL.h>
#include "../deltatime.hpp"

namespace MS = Miserable;

MS::MainScene::MainScene(SDL_Renderer *ren) : mPlayerArea(new MS::Layer), mBG(new MS::Layer), mBoxes(new MS::Layer), mDolly(new MS::Layer), mTestImage("assets/BG.png", ren) 
    {
    mBG->next = mBoxes;
    mBoxes->next = mPlayerArea;
    mPlayerArea->next = mDolly;
    
    mPlayerArea->rects = new MS::Rectangle;
    *mPlayerArea->rects = {
        .x = mLoadOffset, .y = 400,
        .w = 350, .h = 100,
        .r = 0x28, .g = 0x28, .b = 0x28, .a = 0xff,
        .image = &mTestImage,
    };
    mPlayerArea->rects->next = new MS::Rectangle;
    *mPlayerArea->rects->next = {
        .x = 300+mLoadOffset, .y = 400,
        .w = 50, .h = 50,
        .r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xff,
    };
    
}

MS::Layer *MS::MainScene::frame() {
    int numKeys = 0;
    const bool *kbState = SDL_GetKeyboardState(&numKeys);

    if (kbState[SDL_SCANCODE_A]) {
        if(player.x < 1 ){
            --mPlayerArea->rects->next->x;
            --mDolly->rects->x;
            player.x = 1 - (mPlayerArea->rects->next->x - mLoadOffset)/mPlayerArea->rects->w; //gross, why are you looking at this
        }
        std::print(stderr, "{}\n", player.x);
    }

    if (kbState[SDL_SCANCODE_D]) {
        if(player.x > 0){
            ++mPlayerArea->rects->next->x;
            ++mDolly->rects->x;
            player.x = 1 - (mPlayerArea->rects->next->x )/(mPlayerArea->rects->w + mLoadOffset/2);
        }
        std::print(stderr, "{}\n", player.x);
    }


    return mBG;
}

void MS::MainScene::Resize(int w, int h) {

}

MS::MainScene::~MainScene() {

    for (MS::Layer *lay = mBG; lay != nullptr;) {
        MS::Layer *next_lay = lay->next;
        for (MS::Rectangle *rect; rect != nullptr;) {
            MS::Rectangle *next_rect = rect->next;
            delete rect;
            rect = next_rect;
        }
        delete lay;
        lay = next_lay;
    }
}

