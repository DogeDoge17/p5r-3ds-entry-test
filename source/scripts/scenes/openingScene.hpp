#pragma once
#include <iostream>
#include "../../loading/scene.hpp"

class OpeningScene : public Scene
{
public:

	GameObject penis = GameObject();


	OpeningScene()
	{

	}

	void update()
	{
		std::cout << "but can it do this????";
		
	}

	void draw()
	{
		penis.GetComponent<MeshRenderer>()->render();
	}

	void start()
	{
		penis.AddComponent<MeshRenderer>();

		//auto renderer = penis.GetComponent<MeshRenderer>();
	}

	void load()
	{

	}

	void unload()
	{

	}

	~OpeningScene()
	{
		unload();
	}
};