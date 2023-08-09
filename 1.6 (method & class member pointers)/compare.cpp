#include <iostream>

// ====================================================================================================================

template<typename Type_1, typename Type_2>
bool compare(Type_1 const & obj_1, Type_1 const & obj_2, Type_2 (Type_1::*method)() const)
{
    return (obj_1.*method)() < (obj_2.*method)();
}

// ====================================================================================================================

int main()
{
    std::string s1("Elf");
    std::string s2("Archer");

    // compare string length
    bool r1 = compare(s1, s2, &std::string::size); // true
    bool r2 = compare(s1, s1, &std::string::size); // false

    std::cout << r1 << std::endl;
    std::cout << r2 << std::endl;

    return 0;
}