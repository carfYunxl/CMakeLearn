#ifndef SCENE_H_
#define SCENE_H_

#include "entt.hpp"
#include "TimeStep.h"
#include "BatchRender_3D.hpp"
#include <string>
#include <list>

namespace GL {

	class Entity;
	class SceneHierarchyPanel;
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

		void DestroyEntity(Entity entity);

	private:
		entt::registry m_Registry;

		//std::list<Entity> m_EntityList;

		friend class Entity;
		friend class SceneHierarchyPanel;
	};

}

#endif //SCENE_H_