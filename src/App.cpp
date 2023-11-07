#include "App.h"
#include "TimeStep.h"

#include "glfw3.h"

namespace GL
{
    #define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

    App* App::s_Instance = nullptr;

    App::App(const std::string& name)
    {
        s_Instance = this;

        m_Window = std::unique_ptr<WindowsWindow>(new WindowsWindow(WindowProps(name)));
        m_Window->SetEventCallback( BIND_EVENT_FN(App::OnEvent) );

        //Renderer::Init();

        m_ImGuiLayer = new ImGuiLayer();
        PushLayer(m_ImGuiLayer);
    }

    App::~App()
    {

    }

    void App::Run()
    {
        while (m_Running)
        {
            float time = (float)glfwGetTime();
            Timestep timestep = time - m_LastFrameTime;
            m_LastFrameTime = time;

            if (!m_Minimized)
            {
                for (Layer* layer : m_LayerStack)
                    layer->OnUpdate(timestep);
            }

            m_ImGuiLayer->Begin();
            for ( Layer* layer : m_LayerStack )
            {
                layer->OnImGuiRender();
            }
            m_ImGuiLayer->End();

            m_Window->OnUpdate();
        }
    }

    void App::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);

        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(App::OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(App::OnWindowResize));

        for ( auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
        {
            (*--it)->OnEvent(e);
            if (e.Handled)
                break;
        }
    }

    bool App::OnWindowClose(WindowCloseEvent& e)
    {
        m_Running = false;
        return true;
    }

    bool App::OnWindowResize(WindowResizeEvent& e)
    {
        if ( e.GetWidth() == 0 || e.GetHeight() )
        {
            m_Minimized = true;
        }
        m_Minimized = false;

        //Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
        return false;
    }

    void App::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);

        layer->OnAttach();
    }

    void App::PushOverLay(Layer* layer)
    {
        m_LayerStack.PushOverlay(layer);

        layer->OnAttach();

    }
}