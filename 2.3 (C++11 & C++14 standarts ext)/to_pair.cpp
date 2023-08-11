#include <tuple>
#include <iostream>

// ====================================================================================================================

// This implementation works for C++11

// Makes a pair of values taken from input tuple at the given indexes
template<size_t index_1, size_t index_2, typename... Args>
auto to_pair(std::tuple<Args...> tuple) ->
    decltype(std::make_pair(std::get<index_1>(tuple), std::get<index_2>(tuple)))
{
    return std::make_pair(std::get<index_1>(tuple), std::get<index_2>(tuple));
}

// ====================================================================================================================

int main()
{
    auto tuple = std::make_tuple(0, 3.5, "Hello");

    std::pair<double, char const *> pair_1 = to_pair<1, 2>(tuple);
    std::pair<int, double> pair_2 = to_pair<0, 1>(tuple);

    std::cout <<    "PAIR 1: "
              <<    std::get<0>(pair_1)
              <<    ", "
              <<    std::get<1>(pair_1) << std::endl;

    std::cout <<    "PAIR 2: "
              <<    std::get<0>(pair_2)
              <<    ", "
              <<    std::get<1>(pair_2) << std::endl;

    return 0;
}