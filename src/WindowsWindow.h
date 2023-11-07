#pragma once

#include "WindowsWindow.h"
#include "OpenGLContext.h"
#include "Event.h"
#include <functional>
#include <memory>

struct GLFWwindow;

namespace GL {

	struct WindowProps
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		WindowProps(const std::string& title = "GL Engine",
			uint32_t width = 1920,
			uint32_t height = 1080)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	class WindowsWindow
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate();

		inline unsigned int GetWidth() const { return m_Data.Width; }
		inline unsigned int GetHeight() const { return m_Data.Height; }

		// Window attributes
		inline void SetEventCallback(const EventCallbackFn& callback) { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled);
		bool IsVSync() const;

		inline virtual void* GetNativeWindow() const { return m_Window; }

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
		std::unique_ptr<OpenGLContext> m_Context;
	};

}