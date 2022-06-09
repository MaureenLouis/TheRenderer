#pragma once

class ScriptableEntity
{
public:


private:
	entt::entity _entity;
};

struct NativeScriptComponent
{
	ScriptableEntity* instance = nullptr;

	std::function<void()> onCreateFunction;
	std::function<void()> instantiateFunction;
	std::function<void()> destroyInstanceFunction;

	template<typename T>
	void bind()
	{
		instantiateFunction = [&instance]()
		{
			instance = new T();
		};

		destroyInstanceFunction = [&instance]()
		{
			if (instance && T* pInstance = static_cast<T*>(instance))
			{
				delete pInstance;
			}
		};

		onCreateFunction = [](ScriptableEntity* instance)
		{
			T* pInstance = static_cast<T*>(instance);
			if (pInstance)
			{
    			pInstance->onCreate();
			}
		};
	}
};