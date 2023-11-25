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
#include "SceneSerializer.h"
#include "Scene/PlatformUtils.h"
#include "ImGuizmo.h"
#include "GLMath.h"
#include "WindowsInput.h"
#include "KeyCodes.h"
#include "MouseCodes.h"

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
        m_ActiveScene->OnUpdate(*m_BatchRenderer.get(), ts);
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

        m_BatchRenderer = std::make_unique<BatchRender_3D>();
        m_BatchRenderer->OnAttach();

        m_SceneHerarchyPanel.SetContext(m_ActiveScene.get());
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
               if (ImGui::MenuItem("Open ", "Ctrl+O"))
					OpenScene();

				ImGui::Separator();

				if (ImGui::MenuItem("New Scene", "Ctrl+N"))
					NewScene();

				if (ImGui::MenuItem("Save Scene As...", "Ctrl+Shift+S"))
					SaveSceneAs();

				ImGui::Separator();

				if (ImGui::MenuItem("Exit"))
					App::Get().Close();
				
				ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }

        ImGui::End();

        // Scene Hierarchy Panel
        m_SceneHerarchyPanel.OnRender();

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

        ImGui::Text("selected entity : %d", m_SceneHerarchyPanel.GetSelectEntity().toInt());

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

        //ImGui::ColorPicker4("Component Color", glm::value_ptr(m_BatchRenderer->GetColorCom().Color));

        ImGui::Text("Draw calls : %d", m_BatchRenderer->GetDrawCall());

        ImGui::DragFloat("Max Vertices", m_BatchRenderer->GetMaxVertices(), 100.0f, 500.0f, 50000.0f);

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

        //Gizmos
        Entity entitySelected = m_SceneHerarchyPanel.GetSelectEntity();
        if( entitySelected.isValid() && m_GizmoType != -1 )
        {
            ImGui::Begin("zmo");
            ImGui::Text("ImGuizmo running...");
            ImGui::End();

            ImGuizmo::SetOrthographic(false);
            ImGuizmo::SetDrawlist();

            float width = (float)ImGui::GetWindowWidth();
            float height = (float)ImGui::GetWindowHeight();
            ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, width, height);

            // Camera
            glm::mat4 cameraProj = m_Camera.GetProjection();
            glm::mat4 cameraView = m_Camera.GetView();

            //Entity transform
            auto& transformComponent = entitySelected.GetComponent<TransformComponent>();
            glm::mat4 transform = transformComponent.GetTransform();

            bool snap = WindowsInput::IsKeyPressed(Key::LeftControl);
            float snapValue = 0.5f;
            if(m_GizmoType == ImGuizmo::OPERATION::ROTATE)
            {
                snapValue = 45.0f;
            }
            float snapValues[3]{snapValue,snapValue,snapValue};

            ImGuizmo::Manipulate(
                glm::value_ptr(cameraView),
                glm::value_ptr(cameraProj), 
                (ImGuizmo::OPERATION)m_GizmoType, 
                ImGuizmo::MODE::LOCAL, 
                glm::value_ptr(transform),
                nullptr,
                snap ? snapValues : nullptr);

            if( ImGuizmo::IsUsing() )
            {
                glm::vec3 translate, rotate, scale;
                auto trans = ExtractTRS( transform, translate, rotate, scale );
                transformComponent.Translation = translate;
                transformComponent.Scale = scale;

                glm::vec3 deltaRotate = rotate - transformComponent.Rotation;

                transformComponent.Rotation += deltaRotate;
            }
        }

        ImGui::End();

        ImGui::PopStyleVar();
    }

    void GL_EditorLayer::OnEvent(Event& event)
    {
        m_Camera.OnEvent(event);

        EventDispatcher dispatcher(event);
		dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(GL_EditorLayer::OnKeyPressed));
		dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN(GL_EditorLayer::OnMouseButtonPressed));
    }

    void GL_EditorLayer::NewScene()
	{
		m_ActiveScene = std::make_unique<Scene>();
		m_SceneHerarchyPanel.SetContext(m_ActiveScene.get());
	}

	void GL_EditorLayer::OpenScene()
	{
		std::string filepath = FileDialogs::OpenFile("River Scene (*.river)\0*.river\0");
		if (!filepath.empty())
			OpenScene(filepath);
	}

	void GL_EditorLayer::OpenScene(const std::filesystem::path& path)
	{
		if (path.extension().string() != ".river")
		{
			return;
		}
		
        m_ActiveScene = std::make_unique<Scene>();
		SceneSerializer serializer(m_ActiveScene.get());
		if ( serializer.Deserialize(path.string()) )
		{
			m_SceneHerarchyPanel.SetContext(m_ActiveScene.get());
		}
	}

	void GL_EditorLayer::SaveSceneAs()
	{
		std::string filepath = FileDialogs::SaveFile("River Scene (*.river)\0*.river\0");
		if ( !filepath.empty() )
		{
		    SceneSerializer serializer(m_ActiveScene.get());
			serializer.Serialize(filepath);
		}
	}

    bool GL_EditorLayer::OnKeyPressed(KeyPressedEvent& e)
    {
        if ( e.GetRepeatCount() > 1 )
			return false;

		bool control = WindowsInput::IsKeyPressed(Key::LeftControl) || WindowsInput::IsKeyPressed(Key::RightControl);
		bool shift = WindowsInput::IsKeyPressed(Key::LeftShift) || WindowsInput::IsKeyPressed(Key::RightShift);

		switch ( e.GetKeyCode() )
		{
			case Key::N:
			{
				if (control)
					NewScene();

				break;
			}
			case Key::O:
			{
				if (control)
					OpenScene();

				break;
			}
			case Key::S:
			{
				if (control)
				{
					if (shift)
						SaveSceneAs();
				}

				break;
			}

			// Gizmos
			case Key::D0:
			{
				// if (!ImGuizmo::IsUsing())
				// 	m_GizmoType = -1;
                m_GizmoType = -1;
				break;
			}
			case Key::D1:
			{
				// if (!ImGuizmo::IsUsing())
				// 	m_GizmoType = ImGuizmo::OPERATION::TRANSLATE;

                m_GizmoType = ImGuizmo::OPERATION::TRANSLATE;
				break;
			}
			case Key::D2:
			{
				// if (!ImGuizmo::IsUsing())
				// 	m_GizmoType = ImGuizmo::OPERATION::ROTATE;
                m_GizmoType = ImGuizmo::OPERATION::ROTATE;
				break;
			}
			case Key::D3:
			{
				// if (!ImGuizmo::IsUsing())
				// 		m_GizmoType = ImGuizmo::OPERATION::SCALE;
                m_GizmoType = ImGuizmo::OPERATION::SCALE;
				break;
			}
		}

		return false;
    }

    bool GL_EditorLayer::OnMouseButtonPressed(MouseButtonPressedEvent& e)
    {
        if (e.GetMouseButton() == Mouse::ButtonLeft)
		{
			// if (m_ViewportHovered && !ImGuizmo::IsOver() && !WindowsInput::IsKeyPressed(Key::LeftAlt))
			// 	m_SceneHierarchyPanel.SetSelectedEntity(m_HoveredEntity);
		}
		return false;
    }

}