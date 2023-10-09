#include "Printer.hpp"

Printer::Printer(const std::string& str)
    : message(str)
{}

Printer::Printer(std::string&& str)
    : message(std::move(str))
{}