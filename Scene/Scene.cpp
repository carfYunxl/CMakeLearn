#include "pch.h"
#include "Scene.h"
#include "Components.h"
#include "BatchRender_3D.hpp"
#include "Entity.h"

namespace GL
{
	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Entity" : name;
		return entity;
	}

	void Scene::OnUpdate(BatchRender_3D& rendener, Timestep ts)
	{
		auto group = m_Registry.group<TransformComponent>(entt::get<ColorComponent>);
		for (auto entity : group)
		{
			auto& [transform, color] = group.get<TransformComponent, ColorComponent>(entity);
			rendener.DrawCube(transform.Transform, color.Color);
		}
	}
}