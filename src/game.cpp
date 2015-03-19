#include "game.h"
#include "model.h"
#include "gfx.h"
#include "physics.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include <ctime>
#include <iostream>
#include <memory>
#include <random>
#include <typeinfo>
#include <exception>

using namespace core;

ResourceRepository::ResourceRepository()
{
}

ResourceRepository::~ResourceRepository()
{
	for (auto elem : resources)
	{
		// TODO: free SDL surfaces / IMGs
	}
}

void ResourceRepository::_AttemptResourceLoad(const std::string &resId, const std::type_index &key)
{
    SDL_Surface *s = IMG_Load(resId.c_str());
    if (s == NULL)
        throw std::logic_error("Couldn't load " + resId);
    resources[key] = s;
}

bool ResourceRepository::LoadResources()
{
    bool ret = true;
    try
    {
        _AttemptResourceLoad("..\\res\\paddle.png", std::type_index(typeid(model::Paddle)));
        _AttemptResourceLoad("..\\res\\brick.png", std::type_index(typeid(model::Brick)));
        _AttemptResourceLoad("..\\res\\ball.png", std::type_index(typeid(model::Ball)));
        _AttemptResourceLoad("..\\res\\bg.png", std::type_index(typeid(model::Background)));
    }
    catch (const std::logic_error &e)
    {
        std::cerr << std::endl << "ERROR: " << e.what() << " -> " << IMG_GetError() << std::endl;
        ret = false;
    }

    return ret;
}

ResourceRepository* ResourceRepository::instance = NULL;
ResourceRepository* ResourceRepository::GetInstance()
{
    if (instance == NULL)
        instance = new ResourceRepository();

    return instance;
}

Game* Game::instance = NULL;
Game* Game::GetInstance()
{
	if (instance == NULL)
		instance = new Game();
		
	return instance;
}

void Game::HandleInput(SDL_Event *e)
{
    if (e->type == SDL_KEYDOWN)
    {
        switch (e->key.keysym.sym)
        {
        case SDLK_F5:
            // restart
            break;

        case SDLK_ESCAPE:
            Quit();
            break;
        }
    }
    else if (e->type == SDL_QUIT)
    {
        Quit();
    }
}

bool Game::Initialize()
{
    if (!ResourceRepository::GetInstance()->LoadResources())
        return false;

    renderer.InitVideo();
    lvl.LoadLevel(actors);
    AddHandler(this);

    return true;
}

void Game::Launch()
{
    SDL_Event event;
    while (isRunning)
    {
        while (SDL_PollEvent(&event))
        {
            for (auto h : inputHandlers)
                h->HandleInput(&event);
        }

        _Update();

        renderer.Draw(actors);
    }
}

void Game::_Update()
{
    physics::PhysicsEngine::GetInstance()->Step();

    for (auto actor : actors)
    {
        actor->Update();
    }
}

int Level::_DivideBrickRow() const
{
    static std::mt19937 mt(time(0));
    std::uniform_int_distribution<int> dist(2, 10);
    return dist(mt);
}

void Level::LoadLevel(ActorList &actors)
{
    actors.push_back(_BuildActor<model::Background>());

	for (int i = 0; i < NUM_ROWS; ++i)
	{
        int div = _DivideBrickRow();
		int w = ROW_WIDTH / div;
        int h = ROW_HEIGHT;
		for (int j = 0; j < div; ++j)
        {
            gfx::size sz { w,  h};
            gfx::point pos { LEFT_OFFSET + j * w, TOP_OFFSET + i * h };
            actors.push_back(_BuildActor<model::Brick>(pos, sz));
		}
	}

	actors.push_back(_BuildActor<model::Paddle>());
    actors.push_back(_BuildActor<model::Ball>());
}
