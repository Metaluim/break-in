#ifndef _GFX_H
#define _GFX_H

#include "common_defs.h"

#include "SDL2/SDL.h"

#include <vector>
#include <memory>
#include <utility>
#include <string>

namespace gfx
{
typedef std::pair<unsigned, unsigned>   point;
typedef std::pair<unsigned, unsigned>   size;

static const std::string WindowName =   "Break-In IV: Electric Boogaloo";

class Renderer
{
public:
    Renderer(const Renderer&) = delete;
    Renderer& operator =(const Renderer&) = delete;
    Renderer() :
        window(NULL),
        screen(NULL),
        startTicks(0U)
    {}
    virtual ~Renderer();

    void InitVideo();

    template <typename T>
    void Draw(T &entities)
    {
        for (auto elem : entities)
            elem->Draw(screen);

        SDL_UpdateWindowSurface(window);

        unsigned frameTicks = SDL_GetTicks() - startTicks;
        if (frameTicks < TICKS_PER_FRAME)
            SDL_Delay(TICKS_PER_FRAME - frameTicks);
    }

private:
    static const int FPS =              60;
    static const int TICKS_PER_FRAME =  1000 / FPS;

    SDL_Window      *window;
    SDL_Surface     *screen;
    unsigned        startTicks;
};

}

#endif /* _GFX_H */

