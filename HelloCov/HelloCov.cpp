#include<iostream>
#include "HelloCov.h"

bool is_power_of_two(int n)
{
    if (n < 0)
        return false;

    return (n & (n - 1)) == 0;
}

int multiply_by_two(int n)
{
    return n << 1;
}

int divide_by_two(int n)
{
    return n >> 1;
}


int main(int argc, char** argv)
{
    std::cout << "4 is power of two?" << is_power_of_two(4) << "\n";
    std::cout << "4 multiply by two?" << multiply_by_two(4) << "\n";
    std::cout << "4 divide by two?" << divide_by_two(4) << "\n";

    return 0;
}//*/