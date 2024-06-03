#include "add-sub.h"

#include <iostream>
#include <string>

int main(int, char const**) {
    int a = add(1, 2);
    int b = sub(2, 1);

    std::cout << "hello world " << std::endl;
    std::cout << "1+2 => " << a << std::endl;
    std::cout << "2-1 => " << b << std::endl;

    if (a != 3)
    {
        std::cerr << "Invalid add" << std::endl;
        return -1;
    }
    if (b != 1)
    {
        std::cerr << "Invalid sub" << std::endl;
        return -1;
    }

    return 0;
}