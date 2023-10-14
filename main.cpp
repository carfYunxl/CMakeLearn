#include <iostream>

#include "Printer.hpp"
#include "test.hpp"

#include "glfw3.h"

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
    std::cout << "Hello World!" << std::endl; 

    Printer print(std::string("hello cmake!"));
    
    print.print();

    TEST::TS::print();

    glfwInit();
    
    GLFWwindow* window = glfwCreateWindow(1200, 800, "My Title", nullptr, nullptr);

    glfwSetErrorCallback(ProcessError);
    glfwSetKeyCallback(window, ProcessKey);
    glfwSetMouseButtonCallback(window, ProcessMouseButton);
    // glfwSetScrollCallback();
    // glfwSetCharCallback();
    // glfwSetCharModsCallback();
    // glfwSetCursorEnterCallback();
    glfwSetCursorPosCallback(window,ProcessMousePos);
    // glfwSetDropCallback();
    // glfwSetFramebufferSizeCallback();
    glfwSetWindowSizeCallback(window, ProcessWinResize);

    while (!glfwWindowShouldClose(window)) 
    {
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();

    std::cin.get();
    
    return 0;    
}