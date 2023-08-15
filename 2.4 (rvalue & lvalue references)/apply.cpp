#include <utility>
#include <string>
#include <iostream>

// ====================================================================================================================

// Function "apply" gets some function or functional object with arguments to call this object
// and calls it using perfect forwarding
template<typename Type, typename ... Args>
auto apply(Type function, Args && ... args)
    -> decltype(function(std::forward<Args>(args) ...))
{
    return function(std::forward<Args>(args) ...);
}

// ====================================================================================================================

int main()
{
    auto fun = [](std::string a, std::string const & b) { return a += b; };

    std::string s("world!");

    std::cout << s << std::endl;

    // s is passed by lvalue reference
    // а is a temporary object by rvalue reference
    s = apply(fun, std::string("Hello, "), s);

    std::cout << s << std::endl;
    
    return 0;
}