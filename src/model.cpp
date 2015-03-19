#include "model.h"

#include "common_defs.h"
#include "game.h"
#include "physics.h"

#include "SDL2/SDL.h"
#include "box2d/Box2D.h"

#include <iostream>

using namespace model;

void Actor::Draw(SDL_Surface *screen)
{
    SDL_BlitSurface(img, NULL, screen, &pos);
}

Paddle::Paddle(SDL_Surface *s) :
    Actor(s)
{
    core::Game *g = core::Game::GetInstance();

    pos.x = CENTER(g->GetWidth(), s->w);
    pos.y = g->GetHeight() - BOTTOM_OFFSET - s->h;

    g->AddHandler(this);

    bodyDef.active = true;
    bodyDef.position.Set((float) pos.x, (float) pos.y);
    bodyDef.type = b2_staticBody;
    bodyIdx = physics::PhysicsEngine::GetInstance()->AddBody(&bodyDef, s->w, s->h);
}

void Paddle::HandleInput(SDL_Event *e)
{
    switch (e->type)
    {
    case SDL_MOUSEMOTION:
            // move paddle
            break;

    case SDL_KEYDOWN:
        switch (e->key.keysym.sym)
        {
        case SDLK_LEFT:
            pos.x -= 4;
            movementDir = LEFT;
            break;

        case SDLK_RIGHT:
            pos.x += 4;
            movementDir = RIGHT;
            break;

        default:
            movementDir = NONE;
        }
        break;

    case SDL_KEYUP:
        switch (e->key.keysym.sym)
        {
        case SDLK_RIGHT:
        case SDLK_LEFT:
            movementDir = NONE;
            break;
        }
        break;
    }
}

void Paddle::Update()
{
    // set pos accordingly
}

void Ball::BeginContact(b2Contact *contact)
{
}

void Ball::EndContact(b2Contact *contact)
{}

Ball::Ball(SDL_Surface *s) :
    Actor(s)
{
    core::Game *g = core::Game::GetInstance();
    physics::PhysicsEngine *f = physics::PhysicsEngine::GetInstance();

    pos.x = CENTER(g->GetWidth(), s->w);
    pos.y = CENTER(g->GetHeight(), s->h);

    bodyDef.position.Set((float) pos.x, (float) pos.y);
    bodyDef.type = b2_dynamicBody;
    bodyIdx = f->AddBody(&bodyDef, (float) s->w/10, (float) s->h/10);
    f->AddContactListener(this);
}

void Ball::Update()
{
    // set pos accordingly
    b2Vec2 _pos = physics::PhysicsEngine::GetInstance()->GetBodyPos(bodyIdx);
    pos.x = _pos.x;
    pos.y = _pos.y;
}

void Brick::Draw(SDL_Surface *screen)
{
    SDL_BlitScaled(img, NULL, screen, &pos);
}

void Brick::Update()
{
    // check collision

    // if collided then break
}

Background::Background(SDL_Surface *s) :
    Actor(s)
{
    pos.x = pos.y = 0;
}



