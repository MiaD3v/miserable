#include <SDL3/SDL.h>

namespace Miserable {
    typedef struct Layer Layer;
    class Scene {
        public:
            void* mRender_Tree;

            explicit Scene();
            virtual Layer* frame() = delete;
            virtual void Resize(int w, int h) = delete;
            virtual ~Scene() = default;

    };
};
