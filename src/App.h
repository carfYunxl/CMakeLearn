#ifndef APP_H_
#define APP_H_
#include "Event.h"
#include "Layer.h"
#include "LayerStack.h"
#include "ApplicationEvent.h"
#include "WindowsWindow.h"
#include "ImGuiLayer.h"
#include <memory>

namespace GL
{
    class App
    {
    public:
        App(const std::string& name = "Razel App");
        virtual ~App();

        void Run();

        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverLay(Layer* layer);

        inline WindowsWindow& GetWindow() { return *m_Window; }

        inline static App& Get() { return *s_Instance; }

        void Close() { m_Running = false; }

        ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

    private:
        bool OnWindowClose(WindowCloseEvent& e);
        bool OnWindowResize(WindowResizeEvent& e);

        std::unique_ptr<WindowsWindow> m_Window;
        bool                    m_Running = true;
        bool                    m_Minimized{false};
        LayerStack              m_LayerStack;

        float m_LastFrameTime = 0.0f;
    private:
        static App*             s_Instance;
        ImGuiLayer*             m_ImGuiLayer;
    };
}

#endif //APP_H_