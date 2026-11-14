#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>


namespace Miserable {
    typedef struct Rectangle Rectangle;
    typedef struct Layer Layer;
    typedef struct Layer {
        Rectangle *rects = nullptr;
        Layer *next = nullptr;
    } Layer;

    class Image;
    // You can _either_ have 'image', a color, or 'text';
    typedef struct Rectangle {
        double x,y,w,h;
        int r,g,b,a;
        Miserable::Image *image    = nullptr;
        Miserable::Rectangle *next = nullptr;
        TTF_Text *text             = nullptr;
    } Rectangle;

    class Renderer {
        public:
        Renderer(); // WARNING: TEMPORARY OBJECT ONLY
        explicit Renderer(SDL_Window *win, SDL_Renderer *ren, int w, int h);

        void resize(int w, int h);

        void render(Layer *tree);

        ~Renderer();

        private:
        SDL_Window *mWindow;
        SDL_Renderer *mRenderer;
        int mW, mH;

    };

};

