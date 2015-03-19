#include "physics.h"

#include "box2d/Box2D.h"

#include <iostream>

using namespace physics;

Body::Body(b2BodyDef _bodyDef, b2Body *_body, b2Fixture *_fixture, b2World *_world) :
    bodyDef(_bodyDef),
    body(_body),
    fixture(_fixture),
    world(_world)
{}

Body::~Body()
{
    body->DestroyFixture(fixture);
    world->DestroyBody(body);
}

void ContactDispatcher::BeginContact(b2Contact *contact)
{
    for (auto l : listeners)
        l->BeginContact(contact);
}

void ContactDispatcher::EndContact(b2Contact *contact)
{
    for (auto l : listeners)
        l->EndContact(contact);
}

PhysicsEngine::~PhysicsEngine()
{
    delete world;
}

PhysicsEngine* PhysicsEngine::instance = NULL;
PhysicsEngine* PhysicsEngine::GetInstance()
{
    if (instance == NULL)
        instance = new PhysicsEngine();

    return instance;
}

void PhysicsEngine::Init()
{
    b2Vec2 gravity(0.0f, 9.8f);
    world = new b2World(gravity);
    world->SetContactListener((b2ContactListener *) (&dispatcher));
}

void PhysicsEngine::Step()
{
    world->Step(TIME_STEP, VELOCITY_ITRS, POS_ITRS);
}

BodyIndex PhysicsEngine::AddBody(const b2BodyDef *bodyDef, float w, float h)
{
    b2Body *body = world->CreateBody(bodyDef);
    b2PolygonShape box;
    box.SetAsBox(w / 2.0f, h / 2.0f);
    b2FixtureDef fdef;
    fdef.shape = &box;
    fdef.density = 0.1f;
    fdef.friction = 0.0f;
    fdef.restitution = 2.0f;
    b2Fixture *f = body->CreateFixture(&fdef);

    bodies.push_back(std::shared_ptr<Body>(new Body(*bodyDef, body, f, world)));

    return --bodies.cend();
}
