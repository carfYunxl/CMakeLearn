#ifndef SCENE_H_
#define SCENE_H_

#include "entt.hpp"
#include "TimeStep.h"
#include "BatchRender_3D.hpp"
#include <string>

namespace GL {

	class Entity;
	class Scene
	{
	public:
		Scene(){};
		~Scene(){};

		Entity CreateEntity();

		// TEMP
		entt::registry& Reg() { return m_Registry; }

		Entity CreateEntity(const std::string& name = std::string());

		void OnUpdate(BatchRender_3D& rendeer, Timestep ts);

	private:
		entt::registry m_Registry;

		friend class Entity;
	};

}

#endif //SCENE_H_