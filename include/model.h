#ifndef _MODEL_H
#define _MODEL_H

#include "SDL2/SDL.h"
#include "box2d/Box2D.h"

#include "common_defs.h"
#include "physics.h"
#include "gfx.h"

namespace model
{

class Actor
{
public:
    Actor() = delete;
    Actor(const Actor&) = delete;
    Actor& operator =(const Actor&) = delete;
    Actor(SDL_Surface *s) : img(s) {}
    virtual ~Actor() {}

    virtual void Update() {}
    virtual void Draw(SDL_Surface *screen);

protected:
    SDL_Surface         *img;
    SDL_Rect            pos;
    b2BodyDef           bodyDef;
    physics::BodyIndex  bodyIdx;
};

class Brick : public Actor
{
public:
    Brick(SDL_Surface *s, gfx::point _pos, gfx::size sz) :
        Actor(s)
    {
        pos.w = sz.first;
        pos.h = sz.second;
        pos.x = _pos.first;
        pos.y = _pos.second;

        bodyDef.active = true;
        bodyDef.position.Set((float) pos.x, (float) pos.y);
        bodyDef.type = b2_staticBody;
        bodyIdx = physics::PhysicsEngine::GetInstance()->AddBody(&bodyDef, pos.w, pos.h);
    }
    virtual ~Brick() {}

    void Draw(SDL_Surface *screen);

    void Update();

private:
    gfx::size   size;
};

class Ball : public Actor, public b2ContactListener
{
public:
    Ball(SDL_Surface *s);

    void Update();

    void BeginContact(b2Contact *contact);
    void EndContact(b2Contact *contact);
};

class Paddle : public Actor, public common::InputHandler
{
public:
    Paddle(SDL_Surface *s);

    void Update();

    void HandleInput(SDL_Event *e);

private:
    typedef enum
    {
        LEFT,
        RIGHT,
        NONE
    } MovementDirection;

    static const int BOTTOM_OFFSET =    32;
    MovementDirection movementDir;
};

class Background : public Actor
{
public:
    Background(SDL_Surface *s);
};

}

#endif /* _MODEL_H */

