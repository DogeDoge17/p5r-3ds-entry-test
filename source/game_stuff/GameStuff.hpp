#pragma once
#include "../main.h"

class GameObject;
class MonoBehaviour;


class MonoBehaviour {
public:
	GameObject* gameObject;
	virtual void baseMethod()
	{
		std::cout << "Called baseMethod\n";
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
	std::vector<MonoBehaviour> monoBehaviours;

	Transform* transform;

	template<class T, class... Args>
	void AddComponent(Args&&... args) {
		static_assert(std::is_base_of<MonoBehaviour, T>::value,
			"T must be derived from MonoBehaviour");
		monoBehaviours.emplace_back(T(*this, std::forward<Args>(args)...));
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
		//Hierarchy::gameObjects.push_back(this);
		AddComponent<Transform>();//monoBehaviours.emplace_back(std::make_unique<Transform>(this));
		transform = GetComponent<Transform>();
	}

	~GameObject()
	{
		/*for(int i = 0; i < gameObjects.end(); i++)
		{
			if(gameObjects[i] == this)
			{

			}
		}*/
		//Hierarchy::gameObjects.erase(std::remove(Hierarchy::gameObjects.begin(), Hierarchy::gameObjects.end(), this), Hierarchy::gameObjects.end());
	}
};

