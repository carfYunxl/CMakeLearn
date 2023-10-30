#define GLFW_INCLUDE_NONE
#include "pch.h"
#include "Shader.h"
#include "VertextBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shape.h"
#include <filesystem>
#include "Texture.h"
#include "TimeStep.h"
#include "Camera.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "glfw3.h"

static float m_lastFrameTime = 0.0f;
static GL::Timestep m_TS = 0.0f;
static float g_LightX = 0.0f;
static float g_LightY = 12.0f;
static float g_LightZ = 0.0f;

GL::Camera camera(1.778f);

void ProcessError(int error_code, const char* description)
{
    std::cout << "Error code : " << error_code << std::endl;
    std::cout << "Error description : " << description << std::endl;
}

void ProcessKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    //`GLFW_PRESS`, `GLFW_RELEASE` or `GLFW_REPEAT`
    float v = m_TS * camera.g_MoveSpeed;
    auto front = camera.GetFront();
    auto right = camera.GetRight();
    auto up = camera.GetUp();
    switch(action)
    {
        case GLFW_PRESS:
        {
            if(key == GLFW_KEY_W)
            {
                camera.AddCameraPos(v * front);
            }

            if(key == GLFW_KEY_S)
            {
                camera.SubCameraPos(v * front);
            }

            if(GLFW_KEY_A == key)
            {
                camera.SubCameraPos(v * glm::normalize(glm::cross(front,up)));
            }

            if(GLFW_KEY_D == key)
            {
                camera.AddCameraPos(v * glm::normalize(glm::cross(front,up)));
            }

            if(key == GLFW_KEY_ESCAPE)
            {
                glfwSetWindowShouldClose(window, true);
            }

            if(key == GLFW_KEY_Q)
            {
                camera.AddCameraPos(v * up);
            }

            if(key == GLFW_KEY_E)
            {
                camera.SubCameraPos(v * up);
            }

            if(key == GLFW_KEY_LEFT)
            {
                g_LightX -= v;
            }

            if(key == GLFW_KEY_RIGHT)
            {
                g_LightX += v;
            }

            if(key == GLFW_KEY_UP)
            {
                g_LightZ -= v;
            }

            if(key == GLFW_KEY_DOWN)
            {
                g_LightZ += v;
            }
        }
        break;
        case GLFW_REPEAT:
        {
            if(key == GLFW_KEY_W)
            {
                camera.AddCameraPos(v * front);
            }

            if(key == GLFW_KEY_S)
            {
                camera.SubCameraPos(v * front);
            }

            if(GLFW_KEY_A == key)
            {
                camera.AddCameraPos(-v * glm::normalize(glm::cross(front,up)));
            }

            if(GLFW_KEY_D == key)
            {
                camera.AddCameraPos(v * glm::normalize(glm::cross(front,up)));
            }

            if(key == GLFW_KEY_Q)
            {
                camera.AddCameraPos(v * up);
            }

            if(key == GLFW_KEY_E)
            {
                camera.AddCameraPos(-v * up);
            }

            if(key == GLFW_KEY_LEFT)
            {
                g_LightX -= v;
            }

            if(key == GLFW_KEY_RIGHT)
            {
                g_LightX += v;
            }

            if(key == GLFW_KEY_UP)
            {
                g_LightZ -= v;
            }

            if(key == GLFW_KEY_DOWN)
            {
                g_LightZ += v;
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

    if (camera.g_isFirstMouse)
    {
        camera.g_LastX = x;
        camera.g_LastY = y;
        camera.g_isFirstMouse = false;
    }

    float xoffset = x - camera.g_LastX;
    float yoffset = camera.g_LastY - y;

    camera.g_LastX = x;
    camera.g_LastY = y;

    xoffset *= camera.g_Sensitivity;
    yoffset *= camera.g_Sensitivity;

    camera.AddYaw(xoffset);
    camera.AddPitch(yoffset);

    if (camera.GetPitch() > 89.0f)
        camera.SetPitch(89.0f);
    if (camera.GetPitch() < -89.0f)
        camera.SetPitch(-89.0f);

    camera.Update();
}

void ProcessWinResize(GLFWwindow* window, int width, int height)
{
    glfwSetWindowSize(window, width, height);
    glViewport(0,0,width,height);

    camera.SetAspectio((float)width / (float)height);
}

void ProcessMouseScroll(GLFWwindow* window, double xoffset, double yoffset)
{
    float fov = camera.GetZoom();
    if(fov >= 1.0f && fov <= 45.0f)
        camera.AddZoom(-(float)yoffset);

    if ( fov< 1.0f )
        camera.SetZoom(1.0f);
    if ( fov > 45.0f )
        camera.SetZoom(45.0f);
}

int main()
{
    if(!glfwInit())
        return -1; 

    GLFWwindow* window = glfwCreateWindow(GL::WIDTH, GL::HEIGHT, "My Title", nullptr, nullptr);
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
    glfwSwapInterval(1); // 开启垂直同步

    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    //io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

    //Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init("#version 410");

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

        float time = glfwGetTime();
        m_TS = time - m_lastFrameTime;
        m_lastFrameTime = time;

        //std::cout << "FPS = " << 1000 / m_TS.GetMilliseconds() << std::endl;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {
            ImGui::Begin("Test");

            ImGui::Text("Hello World!");

            float arr[4];
            if( ImGui::ColorPicker4("Color",arr) )
            {
                ImGui::Text("change color %d %d %d %d", arr[0], arr[1], arr[2], arr[3]);
            }

            ImGui::End();
        }

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Bind();
        shader.Set3f( "u_ObjColor", {1.0f, 0.5f, 0.31f});
        shader.Set3f( "u_LightColor", {1.0f, 1.0f, 1.0f});
        shader.Set3f( "u_LightPos", {g_LightX, g_LightY, g_LightZ});
        shader.Set3f( "u_ViewPos", camera.GetCameraPos());
        texture2.Bind();

        // for(int i = -25; i < 25; ++i)
        // {
        //     for(int j = -25; j < 25; ++j)
        //     {
        //         cube.Draw(camera, {0.0f + 3.0f * i, 0.0f, 0.0f + 3.0f * j}, 0.0f, {1.0f, 1.0f, 1.0f});
        //     }
        // }
        cube.Draw(camera, {0.0f, 0.0f, 0.0f}, 0.0f, {150.0f, 1.0f, 150.0f});
        //texture2.UnBind();

        LightShader.Bind();
        texture1.Bind();
        LightCube.Draw(camera, {g_LightX, g_LightY, g_LightZ}, 0.0f, {5.0f, 5.0f, 5.0f});

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);

    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}