#include <iostream>

// ====================================================================================================================

template<typename Type>
int * find_if(int * start, int * end, Type function)
{
    for (int * ptr = start; ptr != end; ++ptr)
        if (function(*ptr))
            return ptr;
    return end;
}

// variable "gen_finder" contains nameless function which gets array of ints by two pointers and
// returns nameless function which gets int value and checks if this value is in recieved array
auto gen_finder = [](int * start, int * end)
{
    return [start, end](int value) -> bool
    {
        for (int * ptr = start; ptr != end; ++ptr)
        {
            if (*ptr == value) { return true; }
        }

        return false;
    };
};

// ====================================================================================================================

int main()
{
    int primes[5] = {2, 3, 5, 7, 11};
    int m[10] = {0, 0, 1, 1, 4, 6, 7, 8, 9, 10};

    int * first_prime = find_if(m, m + 10, gen_finder(primes, primes + 5));     // points to 7

    std::cout << *first_prime << std::endl;

    return 0;
}