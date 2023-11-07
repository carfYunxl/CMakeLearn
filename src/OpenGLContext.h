#ifndef OPENGL_CONTEXT_H_
#define OPENGL_CONTEXT_H_

struct GLFWwindow;

namespace GL
{
    class OpenGLContext
    {
    public:
        OpenGLContext(GLFWwindow* windowHandle);
        virtual ~OpenGLContext();
        virtual void Init();
        virtual void SwapBuffers();

    private:
        GLFWwindow* m_WindowHandle;
    };
}

#endif //OPENGL_CONTEXT_H_
