#include "game_over_screen.hpp"
#include "../renderer.hpp"
#include <SDL3/SDL.h>
#include <format>
#include <string>
#include <print>


namespace MS = Miserable;

MS::GameOverScene::GameOverScene(SDL_Renderer *ren) : mBG(new MS::Layer), mGameOver(new MS::Layer), mSeconds(new MS::Layer) {
    mTtfEngine = TTF_CreateRendererTextEngine(ren);
    mFont = TTF_OpenFont("assets/lazy_arie.ttf", 64.0);
    msFont = TTF_OpenFont("assets/lazy_arie.ttf", 32.0);
    mTtfText = TTF_CreateText(mTtfEngine, mFont, "Game Over", sizeof("Test Text") - 1);
    
    sText = TTF_CreateText(mTtfEngine, msFont, "Give us a second...", sizeof("Give us a second...") - 1);

    mBG->next = mGameOver;
    mGameOver->next = mSeconds;

    mBG->rects = new MS::Rectangle;
    *mBG->rects = {
        .x = 0, .y = 0,
        .w = 512, .h = 512,
        .r = 0x00, .g = 0x00, .b = 0x00, .a = 0xff,
        
    };
    mGameOver->rects = new MS::Rectangle;
    *mGameOver->rects = {
        .x = 90, .y = 156,
        .w = 1, .h = 1,
        .r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xff,
        .image = nullptr, .text = mTtfText
    };
    mSeconds->rects = new MS::Rectangle;
    *mSeconds->rects = {
        .x = 90, .y = 246,
        .w = 1, .h = 1,
        .r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xff,
        .image = nullptr, .text = sText
    };
}

MS::Layer* MS::GameOverScene::frame(){
    int numKeys = 0;
    const bool *kbState = SDL_GetKeyboardState(&numKeys);
    if (kbState[SDL_SCANCODE_SPACE]) {
        goToNextScene = true;
    }
    return mBG;
}

void MS::GameOverScene::ChangeAliveText(int s){
    TTF_DestroyText(mSeconds->rects->text);
    std::string i_string = std::format("You lived {} seconds", s);
    const char* c_i_string = i_string.c_str();
    TTF_Text *iText = TTF_CreateText(mTtfEngine, msFont, c_i_string, i_string.length());
    mSeconds->rects->text = iText;
    
}

void MS::GameOverScene::Resize(int w, int h){

}

MS::GameOverScene::~GameOverScene(){
    delete mBG;
    delete mGameOver;
}