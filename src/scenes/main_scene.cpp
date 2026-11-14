#include "../renderer.hpp"
#include "main_scene.hpp"
#include <print>
#include <SDL3/SDL.h>
#include "../deltatime.hpp"

namespace MS = Miserable;

static bool decrementHealth(int &hp) {
    hp--;
    if (hp <= 0) {
        hp = 0;
        return true;
    }
    return false;
}

MS::MainScene::MainScene(SDL_Renderer *ren) :
    mPlayerArea(new MS::Layer),
    mBG(new MS::Layer),
    mBoxes(new MS::Layer),
    mShop(new MS::Layer),
    mTestImage("assets/BG.png", ren),
    playerImageNeutral("assets/Player Sprites/Player Char-neutral.png", ren),
    backgroundImage("assets/Backgrounds/warehouse stage 3.png", ren),
    dollyImage("assets/programmer_art/dolly_prog_art.png", ren),
    boxImage("assets/programmer_art/box_prog_art.png", ren)
    {
    mBG->next = mBoxes;
    mBoxes->next = mPlayerArea;
    mPlayerArea->next = mShop;

    mPlayerArea->rects = new MS::Rectangle;
    *mPlayerArea->rects = {
        .x = mLoadOffset, .y = 400,
        .w = 350, .h = 100,
        .r = 0x28, .g = 0x28, .b = 0x28, .a = 0xff,
        .image = &dollyImage,
    };
    mPlayerArea->rects->next = new MS::Rectangle;
    *mPlayerArea->rects->next = {
        .x = 300+mLoadOffset, .y = 400,
        .w = 50, .h = 50,
        .r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xff,
        .image = &playerImageNeutral,
    };

    mBG->rects = new MS::Rectangle;
    *mBG->rects = {
        .x = 0, .y = 0,
        .w = 512, .h = 512,
        .r = 0x28, .g = 0x28, .b = 0x28, .a = 0xff,
        .image = &backgroundImage,
    };

    mBoxes->rects = new MS::Rectangle;
    *mBoxes->rects = {
        .x = 50, .y = 250,
        .w = 100, .h = 100,
        .r = 0x28, .g = 0x28, .b = 0x28, .a = 0xff,
        .image = &boxImage,
    };
    mBoxes->rects->next = new MS::Rectangle;
    *mBoxes->rects->next = {
        .x = 450, .y = 250,
        .w = 100, .h = 100,
        .r = 0x28, .g = 0x28, .b = 0x28, .a = 0xff,
        .image = &boxImage,
    };

    doll_button = new MS::Rectangle;
    *doll_button = {
        .x = 50, .y = 50,
        .w = 100, .h = 100,
        .r = 0x00, .g = 0xFF, .b = 0xFF, .a = 0x5F,
        .image = &mTestImage,
    };
    mShop->rects = doll_button;

    upgrade_button = new MS::Rectangle;
    *upgrade_button = {
        .x = 350, .y = 50,
        .w = 100, .h = 100,
        .r = 0x00, .g = 0xFF, .b = 0xFF, .a = 0x5F,
        .image = &mTestImage,
    };
    mShop->rects->next = upgrade_button;

    bottle_button = new MS::Rectangle;

    *bottle_button = {

        .x = 200, .y = 50,
        .w = 100, .h = 100,
        .r = 0x00, .g = 0xFF, .b = 0xFF, .a = 0x5F,
        .image = &mTestImage,
    };
    mShop->rects->next->next = bottle_button;

    mPlayerArea->rects->next->x = (mPlayerArea->rects->w * (1 - player.x)) + mPlayerArea->rects->x;
}

MS::Layer *MS::MainScene::frame() {

    mBladderFilled += MS::dt / 45;
    while (mBladderFilled > 1 + 1.f/45) {
        mBladderFilled -= (1.f / 45);
        if (decrementHealth(player.hp)) {
            std::print("YOU DIED!\n");
        }
        std::print(stderr, "hp: {}\n", player.hp);
    }

    int numKeys = 0;
    float msX = -1;
    float msY = -1;
    const bool *kbState = SDL_GetKeyboardState(&numKeys);
    const SDL_MouseButtonFlags msState = SDL_GetMouseState(&msX, &msY);

    if (kbState[SDL_SCANCODE_A]) {
        player.x += MS::dt;
        if (player.x > 1) player.x = 1;
        mPlayerArea->rects->next->x = (mPlayerArea->rects->w * (1 - player.x)) + mPlayerArea->rects->x;
    }

    if (kbState[SDL_SCANCODE_D]) {
        player.x -= MS::dt;
        if (player.x < 0) player.x = 0;
        mPlayerArea->rects->next->x = (mPlayerArea->rects->w * (1 - player.x)) + mPlayerArea->rects->x;
    }

    if (msState == SDL_BUTTON_LEFT && !held_down){
        if(IsRectClicked(msX, msY, doll_button)){
            if(inventory.Buy_Doll()){
                std::print(stderr, "Bought Doll");
            } else {
                std::print(stderr, "Not Enough Money");
            };
        }
        if(IsRectClicked(msX, msY, bottle_button)){
            if(inventory.Buy_Bottle()){
                std::print(stderr, "{}", inventory.bottleCount);
            } else {
                std::print(stderr, "Not Enough Money");
            };
        }
        if(IsRectClicked(msX, msY, upgrade_button)){
            if(inventory.Upgrade_Dolly()){
                std::print(stderr, "{}", inventory.dollyLevel);
            } else {
                std::print(stderr, "Not Enough Money");
            };
        }
        held_down = true;
    }
    if (!msState){
        held_down = false;
    }

    return mBG;
}

void MS::MainScene::Resize(int w, int h) {

}

bool MS::MainScene::IsRectClicked(float msX, float msY, MS::Rectangle *button){
    return msX > button->x && msX < button->x + button->w && msY > button->y && msY < button->y + button->h;
}

MS::MainScene::~MainScene() {
    delete mPlayerArea;
    delete mBG;
    delete mBoxes;
    delete mShop;
}   

