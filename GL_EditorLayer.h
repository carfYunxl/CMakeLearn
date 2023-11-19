#ifndef GL_EDITOR_LAYER_H_
#define GL_EDITOR_LAYER_H_

#include "Layer.h"
#include "Camera.h"
#include "Data.h"
#include "glm.hpp"

#include "OpenGLFrameBuffer.h"
#include "BatchRender_3D.hpp"
#include "Scene/Scene.h"
#include "Panels/SceneHierarchyPanel.h"

namespace GL
{
    class SceneHierarchyPanel;
    class GL_EditorLayer : public Layer
    {
    public:
        GL_EditorLayer();
        virtual ~GL_EditorLayer() = default;

        virtual void OnUpdate(Timestep ts) override;

        virtual void OnAttach() override;
        virtual void OnDetach() override;

        virtual void OnImGuiRender() override;

        virtual void OnEvent(Event& event) override;
    private:
        Camera          m_Camera{1.778f};
        BatchRender_3D*  m_BatchRenderer;

        Attribute   m_CubeAttr{
            {0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f},
            {1.0f, 1.0f, 1.0f},
            {1.0f, 0.5f, 0.31f}
        };
        Attribute   m_AnotherCubeAttr{
            {-50.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f},
            {1.0f, 1.0f, 1.0f},
            {1.0f, 0.5f, 0.31f}
        };
        Attribute   m_LightAttr{
            {0.0f, 20.0f, 0.0f},
            {0.0f, 0.0f, 0.0f},
            {5.0f, 5.0f, 5.0f},
            {1.0f, 1.0f, 1.0f}
        };

        float           m_Frams;

        bool m_ViewportFocused {false};
        bool m_ViewportHovered {false};

        glm::vec2 m_ViewPortSize;

        std::unique_ptr<OpenGLFramebuffer> m_FrameBuffer;

        float m_CubeCnt{5};

        std::unique_ptr<Scene> m_ActiveScene;

        SceneHierarchyPanel mPanel;
    };
}


#endif //GL_EDITOR_LAYER_H_