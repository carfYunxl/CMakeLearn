#ifndef SCENE_HIERARCHY_PANEL_H_
#define SCENE_HIERARCHY_PANEL_H_

#include "Entity.h"

namespace GL
{
    class Scene;

    class SceneHierarchyPanel
    {
    public:
        SceneHierarchyPanel();

        void SetContext(Scene* scene);

        void OnRender();

        Entity GetSelectEntity() const { return m_SelectedEntity; }
    private:
        void DrawEntityNode(Entity entity);
        void DrawComponents(Entity entity);

        template<typename T>
	    void DisplayAddComponentEntry(const std::string& entryName);

    private:
        Scene* m_Scene;
        friend class Scene;
        friend class SceneSerializer;
        Entity m_SelectedEntity{};
    };
}


#endif //SCENE_HIERARCHY_PANEL_H_