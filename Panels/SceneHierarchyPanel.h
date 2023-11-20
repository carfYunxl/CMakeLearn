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
    private:
        void DrawEntityNode(Entity entity);
        void DrawComponents(Entity entity);
    private:
        Scene* m_Scene;
        friend class Scene;
        Entity m_SelectedEntity;
    };
}


#endif //SCENE_HIERARCHY_PANEL_H_