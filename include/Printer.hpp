#ifndef PRINTER_HPP_
#define PRINTER_HPP_

#include <iostream>
#include <string>
class Printer
{
public:
    Printer(const std::string& str);
    Printer(std::string&& str);

    void print()
    {
        std::cout << message << std::endl;
    }
private:
    std::string message;
};

#endif //PRINTER_HPP_