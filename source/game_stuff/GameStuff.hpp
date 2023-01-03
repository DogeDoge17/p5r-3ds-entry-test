#pragma once
#include "../main.h"

class GameObject;
class MonoBehaviour;

class MonoBehaviour {
public:
	GameObject* gameObject;
	virtual void baseMethod() {
		std::cout << "Called baseMethod" << std::endl;
	}
	MonoBehaviour(GameObject& par){ gameObject = &par; }
	~MonoBehaviour(){}
	
};

class Transform : public MonoBehaviour {
public:
	using MonoBehaviour::MonoBehaviour;
	Vector3 position;
	Vector3 scale;
	Quaternion rotation;
};

class GameObject {
public:
	static std::vector<GameObject> gameObjects;

	std::vector<MonoBehaviour> monoBehaviours;

	/*void AddComponent(std::unique_ptr<MonoBehaviour> item)
	{
		monoBehaviours.push_back(std::move(item));
	}*/

	template<class T, class... Args>
	void AddComponent(Args&&... args) {
		monoBehaviours.push_back(T(std::forward<Args>(args)...));
	}

	template <typename T>
	T* GetComponent()
	{
		for (auto& elem : monoBehaviours) {
			if (T* p = dynamic_cast<T*>(&elem)) {
				return p;
			}
		}
		return nullptr;
	}


	GameObject()
	{
		//gameObjects.push_back(this);
		AddComponent<Transform>(*this);//monoBehaviours.emplace_back(std::make_unique<Transform>(this));
	}

	~GameObject()
	{
		/*for(int i = 0; i < gameObjects.end(); i++)
		{
			if(gameObjects[i] == this)
			{

			}
		}*/
		//gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), this), gameObjects.end());
	}
};

