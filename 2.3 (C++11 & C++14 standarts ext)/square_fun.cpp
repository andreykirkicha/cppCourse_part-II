#include <iostream>

// ====================================================================================================================

template<class Typename>
void for_each_int(int * top, int * end, Typename function)
{
    for ( ; top != end; ++top)
        function(*top);
}

// variable "square_fun" contains nameless function which squares a number
auto square_fun = [](int & x) { x *= x; };

// ====================================================================================================================

int main()
{
    int m[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    for (size_t i = 0; i < 10; ++i) { std::cout << m[i] << " "; }
    std::cout << std::endl;

    for_each_int(m, m + 10, square_fun);

    for (size_t i = 0; i < 10; ++i) { std::cout << m[i] << " "; }
    std::cout << std::endl;
    
    return 0;
}