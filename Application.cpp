#define GLFW_INCLUDE_NONE
#include "pch.h"
#include "Shader.h"
#include "VertextBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shape.h"
#include <filesystem>
#include "Texture.h"
#include "glm/gtc/matrix_transform.hpp"

static float r = 0.0f;
static float g = 0.0f;
static float b = 0.0f;
static float x = 0.0f;
static float y = 0.0f;

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
            if(key == GLFW_KEY_W)
            {
                r += 0.1f;
                if(r > 1.0f) r = 0.1f;

                y += 0.02f;
                if(y > 1.0f) y = -1.0f;
            }

            if(key == GLFW_KEY_S)
            {
                b -= 0.1f;
                if(b < 0.1f) b = 1.0f;

                y -= 0.02f;
                if(y < -1.0f) y = 1.0f;
            }

            if(GLFW_KEY_A == key)
            {
                g -= 0.1f;
                if(g < 0.1f) g = 1.0f;

                x -= 0.02f;
                if(x < -1.0f) x = 1.0f;
            }

            if(GLFW_KEY_D == key)
            {
                g += 0.1f;
                if(g > 1.0f) g = 0.1f;

                x += 0.02f;
                if(x > 1.0f) x = -1.0f;
            }
        }
        break;
        case GLFW_REPEAT:
        {
            if(key == GLFW_KEY_W)
            {
                r += 0.1f;
                if(r > 1.0f) r = 0.1f;

                y += 0.02f;
                if(y > 1.0f) y = -1.0f;
            }

            if(key == GLFW_KEY_S)
            {
                b -= 0.1f;
                if(b < 0.1f) b = 1.0f;

                y -= 0.02f;
                if(y < -1.0f) y = 1.0f;
            }

            if(GLFW_KEY_A == key)
            {
                g -= 0.1f;
                if(g < 0.1f) g = 1.0f;

                x -= 0.02f;
                if(x < -1.0f) x = 1.0f;
            }

            if(GLFW_KEY_D == key)
            {
                g += 0.1f;
                if(g > 1.0f) g = 0.1f;

                x += 0.02f;
                if(x > 1.0f) x = -1.0f;
            }
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
    glViewport(0,0,width,height);
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

    std::filesystem::path path = std::filesystem::current_path();
    std::filesystem::path sPath = path / "shaders" / "Basic.shader";
    std::filesystem::path iPath = path / "texture" / "happyface.png";
    std::filesystem::path iiPath = path / "texture" / "wall.jpg";

    GL::Triangle triangle(iPath.string().c_str());
    GL::Rectangle rectangle(iPath.string().c_str());

    GL::Texture texture1(iPath.string().c_str());
    GL::Texture texture2(iiPath.string().c_str());
    
    GL::Shader shader(sPath.string().c_str(), iPath.string().c_str());
    shader.SetInt("u_Texture", 0);

    while (!glfwWindowShouldClose(window)) 
    {
        glClearColor(0.2f, 0.2f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.Bind();
        shader.Set4f("u_Color", {r, g, b, 1.0f });
        shader.SetMat4("u_Transform", glm::rotate(glm::mat4(1.0f),glm::radians(-90.0f) ,{0,0,1}) * glm::scale(glm::mat4(1.0), {0.5f,0.5f,0.0f}) * glm::translate(glm::mat4(1.0), {0.0f,0.0f,0.0f}));
        texture2.Bind();
        triangle.Draw();

        shader.Bind();
        shader.Set4f("u_Color", {r, g, b, 1.0f });
        shader.SetMat4("u_Transform", glm::rotate(glm::mat4(1.0f),glm::radians(90.0f) ,{0,0,1}) * glm::scale(glm::mat4(1.0), {1.5f,1.5f,0.0f}) * glm::translate(glm::mat4(1.0), {x,y,0.0f}));
        texture1.Bind();
        rectangle.Draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();  
    return 0;    
}