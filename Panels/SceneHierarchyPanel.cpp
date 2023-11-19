#include "SceneHierarchyPanel.h"

#include "imgui.h"
#include "Components.h"
#include "Scene.h"

namespace GL
{
    SceneHierarchyPanel::SceneHierarchyPanel()
    {

    }

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
        ImGui::End();
    }

    void SceneHierarchyPanel::DrawEntityNode(Entity entity)
    {
        auto& tag = entity.GetComponent<TagComponent>();

        ImGuiTreeNodeFlags flag = (m_SelectEntity == entity ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_SpanAvailWidth;
        bool opened = ImGui::TreeNodeEx((const void*)entity.toInt(),flag, tag.Tag.c_str());

        if(ImGui::IsItemClicked())
        {
            m_SelectEntity = entity;
        }

        if(opened)
        {
            ImGuiTreeNodeFlags flag = (m_SelectEntity == entity ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_SpanAvailWidth;
            bool opened = ImGui::TreeNodeEx((const void*)entity.toInt(),flag, tag.Tag.c_str());
            if(opened)
            {
                ImGui::TreePop();
            }
            ImGui::TreePop();
        }
    }
}