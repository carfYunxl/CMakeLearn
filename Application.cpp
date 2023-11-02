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

static GL::SceneData g_SceneData;

static GL::Camera g_Camera(1.778f);

void ProcessError(int error_code, const char* description)
{
    std::cout << "Error code : " << error_code << std::endl;
    std::cout << "Error description : " << description << std::endl;
}

void ProcessKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    //`GLFW_PRESS`, `GLFW_RELEASE` or `GLFW_REPEAT`
    float v = g_SceneData.m_TS * g_Camera.m_Data.m_MoveSpeed;
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
                g_SceneData.m_LightPos.x -= v;
            }

            if(key == GLFW_KEY_RIGHT)
            {
                g_SceneData.m_LightPos.x += v;
            }

            if(key == GLFW_KEY_UP)
            {
                g_SceneData.m_LightPos.z -= v;
            }

            if(key == GLFW_KEY_DOWN)
            {
                g_SceneData.m_LightPos.z += v;
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
                g_SceneData.m_LightPos.x -= v;
            }

            if(key == GLFW_KEY_RIGHT)
            {
                g_SceneData.m_LightPos.x += v;
            }

            if(key == GLFW_KEY_UP)
            {
                g_SceneData.m_LightPos.z -= v;
            }

            if(key == GLFW_KEY_DOWN)
            {
                g_SceneData.m_LightPos.z += v;
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
        g_SceneData.m_LastX = x;
        g_SceneData.m_LastY = y;
        g_Camera.m_Data.m_isFirstMouse = false;
    }

    float xoffset = x - g_SceneData.m_LastX;
    float yoffset = g_SceneData.m_LastY - y;

    g_SceneData.m_LastX = x;
    g_SceneData.m_LastY = y;

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

    g_SceneData.m_WIDTH = width;
    g_SceneData.m_HEIGHT = height;
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

    GLFWwindow* window = glfwCreateWindow(g_SceneData.m_WIDTH, g_SceneData.m_HEIGHT, "My Title", nullptr, nullptr);
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

#ifdef IM
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();
#endif
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

        GL::ImGuiLayer::OnUpdate(g_SceneData, g_Camera);

#ifdef IM
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
#endif
        float time = glfwGetTime();
        g_SceneData.m_TS = time - g_SceneData.m_lastFrameTime;
        g_SceneData.m_lastFrameTime = time;
#ifdef IM
        ImGui::Begin("Test");

        ImGui::ColorPicker3("Color", glm::value_ptr(GL::g_SceneData.m_ObjColor));

        ImGui::End();
#endif
        //std::cout << "FPS = " << 1000 / GL::g_SceneData.m_TS.GetMilliseconds() << std::endl;

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Bind();
        shader.Set3f( "u_ObjColor",     g_SceneData.m_ObjColor);
        shader.Set3f( "u_LightColor",   g_SceneData.m_LightColor);
        shader.Set3f( "u_LightPos",     g_SceneData.m_LightPos);
        shader.Set3f( "u_ViewPos",      g_Camera.GetCameraPos());
        texture1.Bind();

        // for(int i = -25; i < 25; ++i)
        // {
        //     for(int j = -25; j < 25; ++j)
        //     {
        //         cube.Draw(g_Camera, {0.0f + 3.0f * i, 0.0f, 0.0f + 3.0f * j}, 0.0f, {1.0f, 1.0f, 1.0f});
        //     }
        // }
        cube.Draw(g_Camera, g_SceneData.m_ObjPos, g_SceneData.m_ObjRotation, g_SceneData.m_ObjScale);

        LightShader.Bind();
        LightShader.Set3f("u_LightObjColor",   g_SceneData.m_LightColor);
        texture1.Bind();
        LightCube.Draw(g_Camera, g_SceneData.m_LightPos, g_SceneData.m_LightRotation, g_SceneData.m_LightScale);

        GL::ImGuiLayer::End(g_SceneData.m_WIDTH,g_SceneData.m_HEIGHT);
#ifdef IM
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif
        glfwSwapBuffers(window);
    }
#ifdef IM
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
#endif
    GL::ImGuiLayer::OnDestroy();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}