#ifndef WINDOWS_INPUT_H_
#define WINDOWS_INPUT_H_

#include <utility>

namespace GL
{
    class WindowsInput
    {
    public:
        inline static bool IsKeyPressed( int keycode ) { return s_Instance->IsKeyPressedImpl(keycode); }

        inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }

        inline static std::pair<float, float> GetMousePos() { return s_Instance->GetMousePosImpl(); }

        inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
        inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }
    protected:
        virtual bool IsKeyPressedImpl(int keycode);
        virtual bool IsMouseButtonPressedImpl(int button);

        virtual std::pair<float, float> GetMousePosImpl();

        virtual float GetMouseXImpl();
        virtual float GetMouseYImpl();
    private:
        static WindowsInput* s_Instance;
    };
}

#endif //WINDOWS_INPUT_H_
