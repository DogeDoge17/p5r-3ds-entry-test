#pragma once
#include "../game_stuff/GameStuff.hpp"
#include "../rendering/RenderingSystem.hpp"

class Hierarchy 
{
	std::vector<GameObject*> gameObjects;
};


class Scene
{
public:
	Scene(){}
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void start() = 0;
	virtual void load() = 0;
	virtual void unload() = 0;
	virtual ~Scene() = default;
};

namespace SceneManagement{

	Scene* activeScene;

	template<class T>
	void unloadScene()
	{
		delete activeScene;
	}

	template<class T>
	void loadScene()
	{
		static_assert(std::is_base_of<Scene, T>::value, "T must be derived from Scene");
		unloadScene<T>();
		activeScene = new T();
		activeScene->load();
		RenderSystem::sceneExit();
		RenderSystem::sceneInit();
		activeScene->start();
	}

	void drawActive()
	{
		activeScene->draw();
	}
};