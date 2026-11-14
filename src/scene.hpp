#include <SDL3/SDL.h>

namespace Miserable {
    class Scene {
        public:
            void* mRender_Tree;
            
            explicit Scene();
            virtual void* frame();
            virtual void Key_Event(SDL_Event event);
            virtual void Mouse_Event(SDL_Event event);
            virtual void Resize();
            virtual ~Scene();
        
    };
};