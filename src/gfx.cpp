#include "gfx.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "game.h"

using namespace gfx;

void Renderer::InitVideo()
{
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow(WindowName.c_str(),
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              core::Game::GetInstance()->GetWidth(),
                              core::Game::GetInstance()->GetHeight(),
                              SDL_WINDOW_SHOWN);
    screen = SDL_GetWindowSurface(window);

    startTicks = SDL_GetTicks();
}

Renderer::~Renderer()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}
