#define GLFW_INCLUDE_NONE
#include "pch.h"
#include "Shader.h"
#include "VertextBuffer.h"
#include "VertexArray.h"
#include <filesystem>

void ProcessError(int error_code, const char* description)
{
    std::cout << "Error code : " << error_code << std::endl;
    std::cout << "Error description : " << description << std::endl;
}

void ProcessKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    //`GLFW_PRESS`, `GLFW_RELEASE` or `GLFW_REPEAT`
    switch(action)
    {
        case GLFW_PRESS:
        {
            switch(key)
            {
                case GLFW_KEY_A:
                std::cout << "move left" << std::endl;
                break;
            }
        }
        break;
        case GLFW_RELEASE:
        {
            std::cout << "[key release] " << key << " released!" << std::endl;
        }
        break;
        case GLFW_REPEAT:
        {
            std::cout << "[key repeat] " << key << " repeat!" << std::endl;
        }
        break;
    }
}

void ProcessMouseButton(GLFWwindow* window, int button, int action, int mods)
{
    switch (action)
    {
        case GLFW_PRESS:
        {
            std::cout << "mouse button : " << button << "pressed!" << std::endl;
            break;
        }
        case GLFW_RELEASE:
        {
            std::cout << "mouse button : " << button << "released!" << std::endl;
            break;
        }
    }
}

void ProcessMousePos(GLFWwindow* window, double xpos, double ypos)
{
    std::cout << "[ " << xpos << "," << ypos << " ]" << std::endl;
}

void ProcessWinResize(GLFWwindow* window, int width, int height)
{
    glfwSetWindowSize(window, width, height);
}

int main()
{
    if(!glfwInit())
        return -1; 
    GLFWwindow* window = glfwCreateWindow(1200, 800, "My Title", nullptr, nullptr);
    if(!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwSetErrorCallback(ProcessError);
    glfwSetKeyCallback(window, ProcessKey);
    glfwSetMouseButtonCallback(window, ProcessMouseButton);
    glfwSetCursorPosCallback(window,ProcessMousePos);
    glfwSetWindowSizeCallback(window, ProcessWinResize);
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    GL::VertexArray vArray;
    
    std::filesystem::path path = std::filesystem::current_path();
    path /= "shaders/Basic.shader";
    GL::Shader shader(path.string().c_str());
    GL::VertexBuffer vBuffer;
    vArray.Bind();
    vBuffer.Bind();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    vArray.UnBind();
    
    while (!glfwWindowShouldClose(window)) 
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.Bind();
        vArray.Bind();

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();  
    return 0;    
}