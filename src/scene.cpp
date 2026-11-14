#include <SDL3/SDL.h>

#include "scene.hpp"
#include "panic.hpp"

namespace MS = Miserable;

MS::Scene::Scene(){
    ;
}

void* MS::Scene::frame(){
    return NULL;
}

void MS::Scene::Key_Event(SDL_Event event){
    ;
}

void MS::Scene::Mouse_Event(SDL_Event event){
    ;
}

void MS::Scene::Resize(){
    ;
}

MS::Scene::~Scene(){
    ;
}
