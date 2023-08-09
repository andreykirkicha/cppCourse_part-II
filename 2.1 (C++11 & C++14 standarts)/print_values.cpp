#include <iostream>
#include <typeinfo>

// ====================================================================================================================

// Function "print_values" for each argument prints its type and value

void print_values(std::ostream & os)
{
    return;
}

template<typename Type, typename... Args>
void print_values(std::ostream & os, Type value, Args... args)
{
    os << typeid(value).name() << ": " << value << std::endl;
    print_values(os, args...);
}

// ====================================================================================================================

int main()
{
    print_values(std::cout, 0, 3.5, "Hello");

    return 0;
}