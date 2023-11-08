#include "pch.h"
#include "GL_EditorLayer.h"
#include <filesystem>
#include "App.h"
#include "gtc/type_ptr.hpp"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

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
        //std::cout << "FPS = " << 1000 / GL::g_SceneData.m_TS.GetMilliseconds() << std::endl;

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (m_ViewportFocused)
            m_Camera.OnUpdate(ts);

        m_ObjShader.Bind();
        // m_ObjShader.Set3f( "u_LightPos",     m_LightAttr.m_Pos);
        // m_ObjShader.Set3f( "u_ViewPos",      m_Camera.GetCameraPos());
        // m_ObjShader.SetFloat("material.shininess", 32.0f);

        // glm::vec3 diffuseColor = m_LightAttr.m_Color * glm::vec3(0.5f); // 降低影响
        // glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // 很低的影响

        // m_ObjShader.Set3f("u_LightColor.ambient",  ambientColor);
        // m_ObjShader.Set3f("u_LightColor.diffuse",  diffuseColor); // 将光照调暗了一些以搭配场景
        // m_ObjShader.Set3f("u_LightColor.specular", {1.0f, 1.0f, 1.0f}); 
        // m_ObjShader.Set3f("u_LightColor.dir", {-1.0f, 0.0f, 0.0f}); 

        //m_ObjShader.SetInt("material.diffuse", 0);
        m_ObjShader.SetInt("u_Texture", 0);
        m_ObjShader.SetFloat("u_Repeat", m_Repeat );
        // m_ObjShader.SetInt("material.specular", 1);
        // m_ObjShader.SetInt("material.emission", 2);

        m_Texture.BindAll();

        m_ObjCube->Draw(m_Camera, m_CubeAttr.m_Pos, m_CubeAttr.m_Rotation, m_CubeAttr.m_Scale, m_DrawMode);

        //m_ObjCube->Draw(m_Camera, m_AnotherCubeAttr.m_Pos, m_AnotherCubeAttr.m_Rotation, m_AnotherCubeAttr.m_Scale, m_DrawMode);

        // for(int i = 0;i < m_CubeCnt;++i)
        // {
        //     for(int j = 0;j < m_CubeCnt;++j)
        //     {
        //         m_ObjCube->Draw(m_Camera, {0.0f + i * 5.0f, 10.0f, 0.0f + j * 5.0f}, {0.0f, 0.0f, 0.0f}, {3.0f, 3.0f, 3.0f}, m_DrawMode);
        //     }
        // }

        m_LightShader.Bind();
        m_LightShader.Set3f("u_LightObjColor",  m_LightAttr.m_Color);
        m_Texture.BindAll();

        m_LightAttr.m_Pos.y += (float)sin(glfwGetTime());
        m_LightCube->Draw(m_Camera, m_LightAttr.m_Pos, m_LightAttr.m_Rotation, m_LightAttr.m_Scale, m_DrawMode);

        m_FrameBuffer->Unbind();
    }

    void GL_EditorLayer::OnAttach()
    {
        std::filesystem::path path = std::filesystem::current_path();

        std::filesystem::path Path = path / "texture" / "wall.jpg";
        m_Texture.LoadTexture(Path.string().c_str());

        // Path = path / "texture" / "box_mirr.png";
        // m_Texture.LoadTexture(Path.string().c_str());

        // Path = path / "texture" / "happyface.png";
        // m_Texture.LoadTexture(Path.string().c_str());

        std::filesystem::path bPath = path / "shaders" / "Basic.shader";
        std::filesystem::path sPath = path / "shaders" / "Obj.shader";
        std::filesystem::path lPath = path / "shaders" / "Light.shader";

        m_ObjShader.LoadShader(bPath.string().c_str());
        m_LightShader.LoadShader(lPath.string().c_str());

        m_ObjCube = new Cube(m_ObjShader);
        m_LightCube = new Cube(m_LightShader);

        FramebufferSpecification fbSpec;
        fbSpec.Width = 1920;
        fbSpec.Height = 1080;
        m_FrameBuffer = std::make_unique<OpenGLFramebuffer>(fbSpec);
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
                if (ImGui::MenuItem("Exit")) GL::App::Get().Close();
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
            m_Camera.SetCameraPos({0.0f, 0.0, 200.0f});
            m_Camera.SetPitch(0.0f);
            m_Camera.SetYaw(-90.0f);
        }

        ImGui::SameLine();

        if( ImGui::Button("X", ImVec2(50,35)) )
        {
            m_Camera.SetCameraPos({200.0f, 0.0, 00.0f});
            m_Camera.SetPitch(0.0f);
            m_Camera.SetYaw(-180.0f);
        }
        ImGui::SameLine();
        if( ImGui::Button("Y", ImVec2(50,35)) )
        {
            m_Camera.SetCameraPos({0.0f, 200.0, 00.0f});
            m_Camera.SetPitch(-89.0f);
            m_Camera.SetYaw(-90.0f);
        }
        ImGui::SameLine();
        if( ImGui::Button("Normal", ImVec2(50,35)) )
        {
            m_Camera.SetCameraPos({100.0f, 100.0, 100.0f});
            m_Camera.SetPitch(-45.0f);
            m_Camera.SetYaw(-135.0f);
        }

        static bool lineMode{false};
        if(ImGui::Checkbox("SHOW MODE", &lineMode))
        {
            if(lineMode)
                m_DrawMode = GL_LINE;
            else
                m_DrawMode = GL_FILL;
        }

        ImGui::Text("Frame time %.2f ms, FPS : %d", m_Frams, (size_t)((float)1000 / m_Frams));
        ImGui::DragFloat("cube number",&m_CubeCnt, 1.0f, 1.0f, 150.0f);
        ImGui::DragFloat("view distance",m_Camera.vDistance(), 1.0f, 1000.0f, 10000.0f);
        ImGui::DragFloat("repeat", &m_Repeat, 1.0f, 10.0f, 100.0f);
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