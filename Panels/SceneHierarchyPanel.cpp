#include "SceneHierarchyPanel.h"

#include "imgui.h"
#include "Components.h"
#include "Scene.h"
#include "glm/gtc/type_ptr.hpp"

namespace GL
{
    SceneHierarchyPanel::SceneHierarchyPanel()
    {}

    void SceneHierarchyPanel::SetContext(Scene* scene)
    {
        m_Scene = scene;
    }

    void SceneHierarchyPanel::OnRender()
    {
        ImGui::Begin("Scene Hierarchy");
        m_Scene->m_Registry.each([&](auto entityID){

            Entity entity{entityID, m_Scene};

            DrawEntityNode(entity);
        });

        if(ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
            m_SelectedEntity = {};

        ImGui::End();

        ImGui::Begin("Properties");
        if( m_SelectedEntity )
        {
            DrawComponents(m_SelectedEntity);
        }
        ImGui::End();
    }

    void SceneHierarchyPanel::DrawEntityNode(Entity entity)
    {
        auto& tag = entity.GetComponent<TagComponent>();

        ImGuiTreeNodeFlags flags = ((m_SelectedEntity == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
        bool opened = ImGui::TreeNodeEx((const void*)(uint64_t)entity.toInt(), flags, tag.Tag.c_str());

        if(ImGui::IsItemClicked())
        {
            m_SelectedEntity = entity;
        }

        if(opened)
        {
            ImGuiTreeNodeFlags flagS = ImGuiTreeNodeFlags_OpenOnArrow;
            bool opened = ImGui::TreeNodeEx((const void*)(uint64_t)entity.toInt(), flagS, tag.Tag.c_str());
            if(opened)
            {
                ImGui::TreePop();
            }
            ImGui::TreePop();
        }
    }

    void SceneHierarchyPanel::DrawComponents(Entity entity)
    {
        if( entity.HasComponent<TagComponent>() )
        {
            auto& tag = entity.GetComponent<TagComponent>();

            char buffer[512]{0};
            strcpy_s(buffer, sizeof(buffer), tag.Tag.c_str());
            if( ImGui::InputText("Tag", buffer, sizeof(buffer)) )
            {
                tag = std::string(buffer);
            }
        }

        if( entity.HasComponent<TransformComponent>() )
        {
            if(ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform"))
            {
                auto& transform = entity.GetComponent<TransformComponent>().Transform;

                ImGui::DragFloat4("Position0", glm::value_ptr(transform[0]), 0.1f);
                ImGui::DragFloat4("Position1", glm::value_ptr(transform[1]), 0.1f);
                ImGui::DragFloat4("Position2", glm::value_ptr(transform[2]), 0.1f);
                ImGui::DragFloat4("Position3", glm::value_ptr(transform[3]), 0.1f);

                ImGui::TreePop();
            }
        }
    }
}