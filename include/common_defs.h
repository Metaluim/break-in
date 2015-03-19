#ifndef _COMMON_DEFS_H
#define _COMMON_DEFS_H

#include "SDL2/SDL.h"

#define CENTER(len, x) (len / 2) - (x / 2)

namespace common
{
    class InputHandler
    {
    public:
        InputHandler() = default;
        InputHandler(const InputHandler&) = delete;
        InputHandler& operator =(const InputHandler&) = delete;
        virtual ~InputHandler() {}

        virtual void HandleInput(SDL_Event *e) = 0;
    };
}

#endif /* _COMMON_DEFS_H */
