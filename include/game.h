#ifndef _GAME_H
#define _GAME_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include <memory>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include <functional>
#include <list>
#include <vector>

#include "model.h"
#include "common_defs.h"
#include "gfx.h"

namespace core
{
typedef std::vector<std::shared_ptr<model::Actor>> ActorList;

static const int SCREEN_WIDTH =		1024;
static const int SCREEN_HEIGHT =	768;

class ResourceRepository
{
public:
    ResourceRepository();
	ResourceRepository(const ResourceRepository&) = delete;
	ResourceRepository& operator =(const ResourceRepository&) = delete;
	virtual ~ResourceRepository();
	
    static ResourceRepository* GetInstance();

    template<typename T>
    inline SDL_Surface* LocateResource() const
	{
        return resources.at(std::type_index(typeid(T)));
	}
	
    bool LoadResources();

private:
    void _AttemptResourceLoad(const std::string &resId, const std::type_index &key);

    std::unordered_map<std::type_index, SDL_Surface*>   resources;
    static ResourceRepository                           *instance;
};

class Level
{
private:
    static const int NUM_ROWS =			4;
    static const int ROW_WIDTH =		800;
    static const int ROW_HEIGHT =		64;
    static const int LEFT_OFFSET =		(SCREEN_WIDTH - ROW_WIDTH) / 2;
    static const int TOP_OFFSET =		100;

    template<typename T>
    inline std::shared_ptr<T> _BuildActor() const
    {
        //return std::make_shared<T>(new T(ResourceRepository::GetInstance()->LocateResource(typeid(T))));
        return std::shared_ptr<T>(new T(ResourceRepository::GetInstance()->LocateResource<T>()));
    }
    template<typename T>
    inline std::shared_ptr<T> _BuildActor(gfx::point p, gfx::size sz) const
    {
        //return std::make_shared<T>(new T(ResourceRepository::GetInstance()->LocateResource(typeid(T)), p, sz));
        return std::shared_ptr<T>(new T(ResourceRepository::GetInstance()->LocateResource<T>(), p, sz));
    }

    int _DivideBrickRow() const;

public:
    Level() = default;
    Level(const Level&) = delete;
    Level& operator =(const Level &) = delete;
    virtual ~Level() {}

    void LoadLevel(ActorList &actors);
};

class Game : public common::InputHandler
{	
public:
    Game() :
        isRunning(true)
    {}
	Game(const Game&) = delete;
	Game& operator =(const Game&) = delete;
	virtual ~Game() {}
	
	static Game* GetInstance();
	inline int GetWidth() const { return SCREEN_WIDTH; }
	inline int GetHeight() const { return SCREEN_HEIGHT; }
	
	bool Initialize();
	
	void Launch();

    inline void AddHandler(InputHandler *h) { inputHandlers.push_back(h); }

    inline void Quit() { isRunning = false; }
	
private:
	int _DivideBrickRow();
	
    void _LoadLevel();

    void _Update();

    void HandleInput(SDL_Event *e);

    std::list<InputHandler*>    inputHandlers;
    ActorList                   actors;
    Level                       lvl;
    gfx::Renderer               renderer;
    static Game*                instance;
    bool                        isRunning;
};

}

#endif /* _GAME_H */
