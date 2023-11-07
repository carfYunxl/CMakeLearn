#include "pch.h"
#include "OpenGLContext.h"

namespace GL
{
    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
        :m_WindowHandle(windowHandle)
    {
    }
    OpenGLContext::~OpenGLContext()
    {}

    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(m_WindowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    }
    void OpenGLContext::SwapBuffers()
    {
        glBegin(GL_TRIANGLES);
        glfwSwapBuffers(m_WindowHandle);
        glEnd();
    }
}
