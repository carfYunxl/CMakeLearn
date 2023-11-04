#define GLFW_INCLUDE_NONE
#include "pch.h"
#include "Shader.h"
#include "VertextBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shape.h"
#include <filesystem>
#include "Texture.h"
#include "Camera.h"
#include "ImGuiLayer.h"
#include "TimeStep.h"
#include "Data.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "glfw3.h"
#include "gtc/type_ptr.hpp"

static GL::GlobalData g_Data;

static GL::Camera g_Camera(1.778f);

GL::Attribute cubeAttr
{
    {0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f},
    {100.0f, 5.0f, 100.0f},
    {1.0f, 0.5f, 0.31f}
};

GL::Attribute AnotherCubeAttr
{
    {-50.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f},
    {5.0f, 100.0f, 100.0f},
    {1.0f, 0.5f, 0.31f}
};

GL::Attribute LightAttr
{
    {0.0f, 20.0f, 0.0f},
    {0.0f, 0.0f, 0.0f},
    {5.0f, 5.0f, 5.0f},
    {1.0f, 1.0f, 1.0f}
};

void ProcessError(int error_code, const char* description)
{
    std::cout << "Error code : " << error_code << std::endl;
    std::cout << "Error description : " << description << std::endl;
}

void ProcessKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    //`GLFW_PRESS`, `GLFW_RELEASE` or `GLFW_REPEAT`
    float v = g_Data.m_TS * g_Camera.m_Data.m_MoveSpeed;
    auto front = g_Camera.GetFront();
    auto right = g_Camera.GetRight();
    auto up = g_Camera.GetUp();
    switch(action)
    {
        case GLFW_PRESS:
        {
            if(key == GLFW_KEY_W)
            {
                g_Camera.AddCameraPos(v * front);
            }

            if(key == GLFW_KEY_S)
            {
                g_Camera.SubCameraPos(v * front);
            }

            if(GLFW_KEY_A == key)
            {
                g_Camera.SubCameraPos(v * glm::normalize(glm::cross(front,up)));
            }

            if(GLFW_KEY_D == key)
            {
                g_Camera.AddCameraPos(v * glm::normalize(glm::cross(front,up)));
            }

            if(key == GLFW_KEY_ESCAPE)
            {
                glfwSetWindowShouldClose(window, true);
            }

            if(key == GLFW_KEY_Q)
            {
                g_Camera.AddCameraPos(v * up);
            }

            if(key == GLFW_KEY_E)
            {
                g_Camera.SubCameraPos(v * up);
            }

            if(key == GLFW_KEY_LEFT)
            {
                LightAttr.m_Pos.x -= v;
            }

            if(key == GLFW_KEY_RIGHT)
            {
                LightAttr.m_Pos.x += v;
            }

            if(key == GLFW_KEY_UP)
            {
                LightAttr.m_Pos.z -= v;
            }

            if(key == GLFW_KEY_DOWN)
            {
                LightAttr.m_Pos.z += v;
            }
        }
        break;
        case GLFW_REPEAT:
        {
            if(key == GLFW_KEY_W)
            {
                g_Camera.AddCameraPos(v * front);
            }

            if(key == GLFW_KEY_S)
            {
                g_Camera.SubCameraPos(v * front);
            }

            if(GLFW_KEY_A == key)
            {
                g_Camera.AddCameraPos(-v * glm::normalize(glm::cross(front,up)));
            }

            if(GLFW_KEY_D == key)
            {
                g_Camera.AddCameraPos(v * glm::normalize(glm::cross(front,up)));
            }

            if(key == GLFW_KEY_Q)
            {
                g_Camera.AddCameraPos(v * up);
            }

            if(key == GLFW_KEY_E)
            {
                g_Camera.AddCameraPos(-v * up);
            }

            if(key == GLFW_KEY_LEFT)
            {
                LightAttr.m_Pos.x -= v;
            }

            if(key == GLFW_KEY_RIGHT)
            {
                LightAttr.m_Pos.x += v;
            }

            if(key == GLFW_KEY_UP)
            {
                LightAttr.m_Pos.z -= v;
            }

            if(key == GLFW_KEY_DOWN)
            {
                LightAttr.m_Pos.z += v;
            }
        }
        break;
    }
}

void ProcessMousePos(GLFWwindow* window, double xpos, double ypos)
{
    return;
    float x = static_cast<float>(xpos);
    float y = static_cast<float>(ypos);

    if (g_Camera.m_Data.m_isFirstMouse)
    {
        g_Data.m_LastX = x;
        g_Data.m_LastY = y;
        g_Camera.m_Data.m_isFirstMouse = false;
    }

    float xoffset = x - g_Data.m_LastX;
    float yoffset = g_Data.m_LastY - y;

    g_Data.m_LastX = x;
    g_Data.m_LastY = y;

    xoffset *= g_Camera.m_Data.m_Sensitivity;
    yoffset *= g_Camera.m_Data.m_Sensitivity;

    g_Camera.AddYaw(xoffset);
    g_Camera.AddPitch(yoffset);

    if (g_Camera.GetPitch() > 89.0f)
        g_Camera.SetPitch(89.0f);
    if (g_Camera.GetPitch() < -89.0f)
        g_Camera.SetPitch(-89.0f);

    g_Camera.Update();
}

void ProcessWinResize(GLFWwindow* window, int width, int height)
{
    glfwSetWindowSize(window, width, height);
    glViewport(0,0,width,height);

    g_Camera.SetAspectio((float)width / (float)height);

    g_Data.m_WIDTH = width;
    g_Data.m_HEIGHT = height;
}

void ProcessMouseScroll(GLFWwindow* window, double xoffset, double yoffset)
{
    float fov = g_Camera.GetZoom();
    if(fov >= 1.0f && fov <= 45.0f)
        g_Camera.AddZoom(-(float)yoffset);

    if ( fov< 1.0f )
        g_Camera.SetZoom(1.0f);
    if ( fov > 45.0f )
        g_Camera.SetZoom(45.0f);
}

int main()
{
    if(!glfwInit())
        return -1; 

    GLFWwindow* window = glfwCreateWindow(g_Data.m_WIDTH, g_Data.m_HEIGHT, "My Title", nullptr, nullptr);
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
    glfwSetCursorPosCallback(window,ProcessMousePos);
    glfwSetWindowSizeCallback(window, ProcessWinResize);
    glfwSetScrollCallback(window, ProcessMouseScroll);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); 

    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    GL::ImGuiLayer::OnInit(window);

    glEnable(GL_DEPTH_TEST);

    std::filesystem::path path = std::filesystem::current_path();
    std::filesystem::path sPath = path / "shaders" / "Obj.shader";
    std::filesystem::path lPath = path / "shaders" / "Light.shader";

    std::filesystem::path iPath = path / "texture" / "wall.jpg";
    std::filesystem::path iiPath = path / "texture" / "container.jpg";

    GL::Shader shader(sPath.string().c_str());
    GL::Shader LightShader(lPath.string().c_str());

    GL::Cube cube(shader);
    GL::Cube LightCube(LightShader);

    GL::Texture texture1(iPath.string().c_str());
    GL::Texture texture2(iiPath.string().c_str());
    
    shader.SetInt("u_Texture", 0);

    while (!glfwWindowShouldClose(window)) 
    {
        glfwPollEvents();

        GL::ImGuiLayer::Begin();

        GL::ImGuiLayer::OnUpdate(cubeAttr,"Obj");
        GL::ImGuiLayer::OnUpdate(AnotherCubeAttr,"Ano Obj");
        GL::ImGuiLayer::OnUpdate(LightAttr, "Light");
        GL::ImGuiLayer::OnUpdate(g_Camera);

        float time = glfwGetTime();
        g_Data.m_TS = time - g_Data.m_lastFrameTime;
        g_Data.m_lastFrameTime = time;

        //std::cout << "FPS = " << 1000 / GL::g_SceneData.m_TS.GetMilliseconds() << std::endl;

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Bind();
        //shader.Set3f( "u_ObjColor",     cubeAttr.m_Color);
        shader.Set3f( "u_LightPos",     LightAttr.m_Pos);
        shader.Set3f( "u_ViewPos",      g_Camera.GetCameraPos());
        //shader.Set3f( "u_LightColor",   LightAttr.m_Color);

        shader.Set3f("material.ambient",  {1.0f, 0.5f, 0.31f});
        shader.Set3f("material.diffuse",  {1.0f, 0.5f, 0.31f});
        shader.Set3f("material.specular", {0.5f, 0.5f, 0.5f});
        shader.SetFloat("material.shininess", 32.0f);

        glm::vec3 diffuseColor = LightAttr.m_Color * glm::vec3(0.5f); // 降低影响
        glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // 很低的影响

        shader.Set3f("u_LightColor.ambient",  ambientColor);
        shader.Set3f("u_LightColor.diffuse",  diffuseColor); // 将光照调暗了一些以搭配场景
        shader.Set3f("u_LightColor.specular", {1.0f, 1.0f, 1.0f}); 
        texture1.Bind();
        cube.Draw(g_Camera, cubeAttr.m_Pos, cubeAttr.m_Rotation, cubeAttr.m_Scale);

        cube.Draw(g_Camera, AnotherCubeAttr.m_Pos, AnotherCubeAttr.m_Rotation, AnotherCubeAttr.m_Scale);

        LightShader.Bind();
        LightShader.Set3f("u_LightObjColor",  LightAttr.m_Color);
        texture1.Bind();
        glm::vec3 mv{0.0f, 10 * (float)sin(glfwGetTime()), 0.0f};
        LightCube.Draw(g_Camera, LightAttr.m_Pos + mv, LightAttr.m_Rotation, LightAttr.m_Scale);

        GL::ImGuiLayer::End(g_Data.m_WIDTH,g_Data.m_HEIGHT);

        glfwSwapBuffers(window);
    }

    GL::ImGuiLayer::OnDestroy();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}