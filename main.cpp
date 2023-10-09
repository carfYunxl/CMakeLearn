#include <iostream>

#include "Printer.hpp"

int main()
{
    std::cout << "Hello World!" << std::endl; 

    Printer print(std::string("hello cmake!"));
    
    print.print();
    
    return 0;    
}