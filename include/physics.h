#ifndef _PHYSICS_H
#define _PHYSICS_H

#include "box2d/Box2D.h"

#include <memory>
#include <list>

namespace physics
{
class Body
{
public:
    Body() = delete;
    Body(const Body &rhs) :
        body(rhs.body),
        bodyDef(rhs.bodyDef),
        fixture(rhs.fixture),
        world(rhs.world)
    {}
    Body& operator =(const Body&) = delete;
    Body(b2BodyDef _bodyDef, b2Body *_body, b2Fixture *_fixture, b2World *_world);
    ~Body();

    inline const b2Body *const GetBody() const { return body; }
    inline const b2BodyDef& GetBodyDef() const { return bodyDef; }
    inline const b2Fixture* GetFixture() const { return fixture; }

private:
    b2Body      *body;
    b2BodyDef   bodyDef;
    b2Fixture   *fixture;
    b2World     *world;
};
typedef std::list<std::shared_ptr<Body>>::const_iterator BodyIndex;

class ContactDispatcher : public b2ContactListener
{
public:
    ContactDispatcher() = default;
    ContactDispatcher(const ContactDispatcher&) = delete;
    ContactDispatcher& operator =(const ContactDispatcher&) = delete;
    virtual ~ContactDispatcher() {}

    inline void AddListener(b2ContactListener *l) { listeners.push_back(l); }

    void BeginContact(b2Contact *contact);
    void EndContact(b2Contact *contact);

private:
    std::list<b2ContactListener*>   listeners;
};

class PhysicsEngine
{
public:
    PhysicsEngine(const PhysicsEngine&) = delete;
    PhysicsEngine& operator =(const PhysicsEngine&) = delete;
    virtual ~PhysicsEngine();

    static PhysicsEngine* GetInstance();
    void Init();
    BodyIndex AddBody(const b2BodyDef *bodyDef, float w, float h);
    inline b2Vec2 GetBodyPos(const BodyIndex &idx) const { return (*idx)->GetBody()->GetPosition(); }
    inline void AddContactListener(b2ContactListener *listener) { dispatcher.AddListener(listener); }
    void Step();

private:
    PhysicsEngine() { Init(); }

    static constexpr float TIME_STEP =  1.0f / 60.0f;
    static const int VELOCITY_ITRS =    6;
    static const int POS_ITRS =         2;

    static PhysicsEngine                *instance;
    b2World                             *world;
    std::list<std::shared_ptr<Body>>    bodies;
    ContactDispatcher                   dispatcher;
};
}

#endif /* _PHYSICS_H */

