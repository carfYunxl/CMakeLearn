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
    void ImGuiLayer::OnUpdate(Attribute& data, const char* title)
    {
        ImGui::Begin(title);
        ImGui::DragFloat3("Position", glm::value_ptr(data.m_Pos));
        ImGui::DragFloat3("Rotation", glm::value_ptr(data.m_Rotation));
        ImGui::DragFloat3("Scale", glm::value_ptr(data.m_Scale));
        ImGui::ColorPicker3("Color", glm::value_ptr(data.m_Color));
        ImGui::End();
    }

    void ImGuiLayer::OnUpdate(Camera& camera)
    {
        ImGui::Begin("Camera Settings");
        if(ImGui::InputFloat3("Position", glm::value_ptr(camera.CameraPos())))
        {
            camera.Update();
        }
        
        if( ImGui::DragFloat("Yaw", camera.Yaw(), 1.0f,-180.0f, 180.0f) )
        {
            camera.Update();
        }

        if( ImGui::DragFloat("Pitch", camera.Pitch() , 1.0f,-89.0f,89.0f))
        {
            camera.Update();
        }

        ImGui::Text("View Direction");

        if( ImGui::Button("Z", ImVec2(50,35)) )
        {
            camera.SetCameraPos({0.0f, 0.0, 200.0f});
            camera.SetPitch(0.0f);
            camera.SetYaw(-90.0f);
        }

        ImGui::SameLine();

        if( ImGui::Button("X", ImVec2(50,35)) )
        {
            camera.SetCameraPos({200.0f, 0.0, 00.0f});
            camera.SetPitch(0.0f);
            camera.SetYaw(-180.0f);
        }
        ImGui::SameLine();
        if( ImGui::Button("Y", ImVec2(50,35)) )
        {
            camera.SetCameraPos({0.0f, 200.0, 00.0f});
            camera.SetPitch(-89.0f);
            camera.SetYaw(-90.0f);
        }
        ImGui::SameLine();
        if( ImGui::Button("Normal", ImVec2(50,35)) )
        {
            camera.SetCameraPos({100.0f, 100.0, 100.0f});
            camera.SetPitch(-45.0f);
            camera.SetYaw(-135.0f);
        }

        static bool lineMode{false};
        if(ImGui::Checkbox("SHOW MODE", &lineMode))
        {
            if(lineMode)
                camera.m_Data.m_DrawMode = GL_LINE;
            else
                camera.m_Data.m_DrawMode = GL_FILL;
        }
        ImGui::End();
    }
}