#include <iostream>

#include "Printer.hpp"
#include "test.hpp"

#include "glfw3.h"

int main()
{
    std::cout << "Hello World!" << std::endl; 

    Printer print(std::string("hello cmake!"));
    
    print.print();

    TEST::TS::print();

    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Hello Cmake!", nullptr, nullptr);

    while (!glfwWindowShouldClose(window)) 
    {
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();

    std::cin.get();
    
    return 0;    
}