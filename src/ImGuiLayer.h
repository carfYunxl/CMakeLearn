#ifndef IMGUI_LAYER_H_
#define IMGUI_LAYER_H_

#include "Data.h"
#include "Camera.h"

struct GLFWwindow;
namespace GL
{
    class ImGuiLayer
    {
    public:
        static void OnInit(GLFWwindow* window);
        static void OnDestroy();
        static void Begin();
        static void End(int width, int height);
        static void OnUpdate(SceneData& data, Camera& camera);
    };

    static ImGuiLayer m_ImGuiLayer;
}



#endif