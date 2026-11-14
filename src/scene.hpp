#include <SDL3/SDL.h>

namespace Miserable {
    class Scene {
        public:
            void* mRender_Tree;
            
            explicit Scene();
            virtual void* frame() = delete;
            virtual void Key_Event(SDL_Event event) = delete;
            virtual void Mouse_Event(SDL_Event event) = delete;
            virtual void Resize() = delete;
            virtual ~Scene() = {};
        
    };
};