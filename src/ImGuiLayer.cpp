#include "ImGuiLayer.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "glfw3.h"

#include "Data.h"
#include "gtc/type_ptr.hpp"

namespace GL
{
    void ImGuiLayer::OnInit(GLFWwindow* window)
    {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;      // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();
        //ImGui::StyleColorsLight();

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void ImGuiLayer::Begin()
    {
        ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
    }

    void ImGuiLayer::End(int width, int height)
    {
		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImGuiLayer::OnDestroy()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
    void ImGuiLayer::OnUpdate(SceneData& data, Camera& camera)
    {
        {
            ImGui::Begin("Object Settings");
            ImGui::ColorPicker3("Color", glm::value_ptr(data.m_ObjColor));
            ImGui::DragFloat3("Position", glm::value_ptr(data.m_ObjPos));
            ImGui::DragFloat3("Rotation", glm::value_ptr(data.m_ObjRotation));
            ImGui::DragFloat3("Scale", glm::value_ptr(data.m_ObjScale));
            ImGui::End();
        }

        {
            ImGui::Begin("Light Settings");
            ImGui::ColorPicker3("Color", glm::value_ptr(data.m_LightColor));
            ImGui::DragFloat3("Position", glm::value_ptr(data.m_LightPos));
            ImGui::DragFloat3("Rotation", glm::value_ptr(data.m_LightRotation));
            ImGui::DragFloat3("Scale", glm::value_ptr(data.m_LightScale));
            ImGui::End();
        }

        {
            ImGui::Begin("Camera Settings");
            if(ImGui::InputFloat3("Position", glm::value_ptr(camera.CameraPos())))
            {
                camera.Update();
            }
            
            if( ImGui::InputFloat("Yaw", camera.Yaw(), 0.0f,0.0f,"Hello") )
            {
                camera.Update();
            }

            if( ImGui::InputFloat("Pitch", camera.Pitch() , 0.0f,0.0f,"Hello"))
            {
                camera.Update();
            }
            ImGui::End();
        }
    }
}