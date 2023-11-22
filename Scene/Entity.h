#ifndef ENTITY_H_
#define ENTITY_H_
#include "entt.hpp"

namespace GL
{
	class Scene;

	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default;

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
		}

		template<typename T>
		T& GetComponent()
		{
			return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}

		template<typename T>
		bool HasComponent()
		{
			return m_Scene->m_Registry.all_of<T>(m_EntityHandle);
		}

		template<typename T>
		void RemoveComponent()
		{
			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}

		operator bool() const { return m_EntityHandle != entt::null; }

		uint32_t toInt() const {return static_cast<uint32_t>(m_EntityHandle);}

		bool operator==(const Entity& other){
			return (*this).m_EntityHandle == other.m_EntityHandle && (*this).m_Scene == other.m_Scene;
		}

		bool operator!=(const Entity& other){
			return !operator==(other);
		}

		entt::entity GetHandleID() const { return m_EntityHandle;}
	private:
		entt::entity m_EntityHandle{ entt::null };
		Scene* m_Scene{nullptr};
	};

}


#endif //ENTITY_H_