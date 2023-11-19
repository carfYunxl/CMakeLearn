#include "pch.h"
#include "GL_EditorLayer.h"
#include <filesystem>
#include "App.h"
#include "gtc/type_ptr.hpp"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "Scene/Entity.h"
#include "Scene/Components.h"

namespace GL
{
    GL_EditorLayer::GL_EditorLayer()
        :Layer("Editor Layer")
    {
    }

    void GL_EditorLayer::OnUpdate(Timestep ts)
    {
        m_FrameBuffer->Bind();
        m_Frams = ts;

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_BatchRenderer->ResetDrawCall();

        if (m_ViewportFocused)
            m_Camera.OnUpdate(ts);

        // update scene
        m_BatchRenderer->BeginScene(m_Camera);
        m_ActiveScene->OnUpdate(*m_BatchRenderer, ts);
        m_BatchRenderer->EndScene();

        m_FrameBuffer->Unbind();
    }

    void GL_EditorLayer::OnAttach()
    {

        FramebufferSpecification fbSpec;
        fbSpec.Width = 1920;
        fbSpec.Height = 1080;
        m_FrameBuffer = std::make_unique<OpenGLFramebuffer>(fbSpec);

        m_ActiveScene = std::make_unique<Scene>();
        auto& cube = (Entity)m_ActiveScene->CreateEntity("Cube");
        auto& color = cube.AddComponent<ColorComponent>();

        m_BatchRenderer = new BatchRender_3D(color);
        m_BatchRenderer->OnAttach();
    }

    void GL_EditorLayer::OnDetach()
    {}

    void GL_EditorLayer::OnImGuiRender()
    {
        static bool dockspaceOpen = true;
        static bool opt_fullscreen_persistant = true;
        bool opt_fullscreen = opt_fullscreen_persistant;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->Pos);
            ImGui::SetNextWindowSize(viewport->Size);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }

        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
        ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Exit")) 
                {
                    GL::App::Get().Close();
                }
                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }

        ImGui::End();

        ImGui::Begin("Camera Settings");
        if(ImGui::InputFloat3("Position", glm::value_ptr(m_Camera.CameraPos())))
        {
            m_Camera.Update();
        }
        
        if( ImGui::DragFloat("Yaw", m_Camera.Yaw(), 1.0f,-180.0f, 180.0f) )
        {
            m_Camera.Update();
        }

        if( ImGui::DragFloat("Pitch", m_Camera.Pitch() , 1.0f,-89.0f,89.0f))
        {
            m_Camera.Update();
        }

        ImGui::Text("View Direction");

        if( ImGui::Button("Z", ImVec2(50,35)) )
        {
            m_Camera.SetCameraPos({0.0f, 0.0, 4.0f});
            m_Camera.SetPitch(0.0f);
            m_Camera.SetYaw(-90.0f);
        }

        ImGui::SameLine();

        if( ImGui::Button("X", ImVec2(50,35)) )
        {
            m_Camera.SetCameraPos({4.0f, 0.0, 00.0f});
            m_Camera.SetPitch(0.0f);
            m_Camera.SetYaw(-180.0f);
        }
        ImGui::SameLine();
        if( ImGui::Button("Y", ImVec2(50,35)) )
        {
            m_Camera.SetCameraPos({0.0f, 4.0, 00.0f});
            m_Camera.SetPitch(-89.0f);
            m_Camera.SetYaw(-90.0f);
        }
        ImGui::SameLine();
        if( ImGui::Button("Normal", ImVec2(50,35)) )
        {
            m_Camera.SetCameraPos({4.0f, 4.0, 4.0f});
            m_Camera.SetPitch(-45.0f);
            m_Camera.SetYaw(-135.0f);
        }

        static bool lineMode{false};
        if(ImGui::Checkbox("SHOW MODE", &lineMode))
        {
            if(lineMode)
                m_BatchRenderer->SetDrawMode(PolygonMode::LINE);
            else
                m_BatchRenderer->SetDrawMode(PolygonMode::FILL);
        }

        ImGui::Text("Frame time %.2f ms, FPS : %d", 1000 * m_Frams, (size_t)((float)1 / m_Frams));
        ImGui::DragFloat("cube number",&m_CubeCnt, 1.0f, 1.0f, 150.0f);
        ImGui::DragFloat("view distance",m_Camera.vDistance(), 1.0f, 1000.0f, 10000.0f);
        ImGui::DragFloat("repeat", m_BatchRenderer->GetRepeat(), 1.0f, 1.0f, 100.0f);

        ImGui::ColorPicker4("Component Color", glm::value_ptr(m_BatchRenderer->GetColorCom().Color));

        ImGui::Text("Draw calls : %d", m_BatchRenderer->GetDrawCall());

        ImGui::DragFloat("Max Vertices", m_BatchRenderer->GetMaxVertices(), 100.0f, 500.0f, 50000.0f);

        ImGui::End();

        ImGui::Begin("Obj");
        ImGui::DragFloat3("Position", glm::value_ptr(m_CubeAttr.m_Pos));
        ImGui::DragFloat3("Rotation", glm::value_ptr(m_CubeAttr.m_Rotation));

        
        ImGui::DragFloat3("Scale", glm::value_ptr(m_CubeAttr.m_Scale));
        ImGui::ColorPicker3("Color", glm::value_ptr(m_CubeAttr.m_Color));
        ImGui::End();

        ImGui::Begin("Ano Obj");
        ImGui::DragFloat3("Position", glm::value_ptr(m_AnotherCubeAttr.m_Pos));
        ImGui::DragFloat3("Rotation", glm::value_ptr(m_AnotherCubeAttr.m_Rotation));
        ImGui::DragFloat3("Scale", glm::value_ptr(m_AnotherCubeAttr.m_Scale));
        ImGui::ColorPicker3("Color", glm::value_ptr(m_AnotherCubeAttr.m_Color));
        ImGui::End();

        ImGui::Begin("Light");
        ImGui::DragFloat3("Position", glm::value_ptr(m_LightAttr.m_Pos));
        ImGui::DragFloat3("Rotation", glm::value_ptr(m_LightAttr.m_Rotation));
        ImGui::DragFloat3("Scale", glm::value_ptr(m_LightAttr.m_Scale));
        ImGui::ColorPicker3("Color", glm::value_ptr(m_LightAttr.m_Color));
        ImGui::End();

        ImGui::PushStyleVar( ImGuiStyleVar_WindowPadding, ImVec2{0,0} );

        ImGui::Begin("ViewPort");

        m_ViewportFocused = ImGui::IsWindowFocused();
        m_ViewportHovered = ImGui::IsWindowHovered();
        App::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused || !m_ViewportHovered);

        ImVec2 viewPortSize = ImGui::GetContentRegionAvail();
        if ( m_ViewPortSize != *(glm::vec2*)&viewPortSize )
        {
            m_FrameBuffer->Resize((uint32_t)m_ViewPortSize.x, (uint32_t)m_ViewPortSize.y);
            m_ViewPortSize = {viewPortSize.x, viewPortSize.y};

            m_Camera.Update();
        }
        uint32_t textureID = m_FrameBuffer->GetColorAttachmentRendererID();
        ImGui::Image((void*)textureID, ImVec2{ m_ViewPortSize.x, m_ViewPortSize.y }, ImVec2{0,1}, ImVec2{1,0});
        ImGui::End();

        ImGui::PopStyleVar();
    }

    void GL_EditorLayer::OnEvent(Event& event)
    {
        m_Camera.OnEvent(event);
    }
}