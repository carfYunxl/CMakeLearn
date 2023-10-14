#include <iostream>

namespace TEST
{
    class TS
    {
        public:
        static inline void print()
        {
            std::cout << "Hello from another file.hpp!" << std::endl;
        } 
    };
}