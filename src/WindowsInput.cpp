#include "pch.h"
#include "WindowsInput.h"

#include "App.h"

namespace GL
{
    WindowsInput* WindowsInput::s_Instance = new WindowsInput();

    bool WindowsInput::IsKeyPressedImpl(int keycode)
    {
        auto window = static_cast<GLFWwindow*>( App::Get().GetWindow().GetNativeWindow() );

        int state = glfwGetKey( window, keycode );
        
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool WindowsInput::IsMouseButtonPressedImpl(int button)
    {
        auto window = static_cast<GLFWwindow*>(App::Get().GetWindow().GetNativeWindow());

        int state = glfwGetMouseButton(window, button);

        return state == GLFW_PRESS;
    }

    std::pair<float, float> WindowsInput::GetMousePosImpl()
    {
        auto window = static_cast<GLFWwindow*>(App::Get().GetWindow().GetNativeWindow());

        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);

        return { (float)xPos, (float)yPos };
    }

    float WindowsInput::GetMouseXImpl()
    {
        auto [x, y] = GetMousePosImpl();

        return x;
    }
    float WindowsInput::GetMouseYImpl()
    {
        auto [x, y] = GetMousePosImpl();

        return y;
    }
}
