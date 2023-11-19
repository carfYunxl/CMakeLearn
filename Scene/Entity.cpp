#include "Scene.h"
#include "Entity.h"

namespace GL {

	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityHandle(handle), m_Scene(scene)
	{
	}

}