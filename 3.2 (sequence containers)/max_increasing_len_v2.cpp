#include <iostream>
#include <list>

// ====================================================================================================================

template<typename IteratorType>
size_t max_increasing_len(IteratorType start, IteratorType end)
{
    size_t max_increasing_len = 0;

    if (start == end) return max_increasing_len;
    
    ++start;
    if (start-- == end) max_increasing_len = 1;

    for (start++; start != end; ++start)
    {
        auto prev = start, next = prev--;
        size_t current_len = 1;

        while (*prev < *next)
        {
            if (next != end) ++current_len, ++prev, ++next;
            else break;
        }

        if (max_increasing_len < current_len) { max_increasing_len = current_len; }
    }

    return max_increasing_len;
}

// ====================================================================================================================

int main()
{
    std::list<int> const l1 = {3, 2, 1};
    int len1 = max_increasing_len(l1.begin(), l1.end());
    if (len1 == 1) std::cout << "1  TRUE" << std::endl;
    else std::cout << "1  FALSE. Expected 1, recieved " << len1 << std::endl;
//
    std::list<int> const l2 = {7, 8, 9, 4, 5, 6, 1, 2, 3, 4};
    size_t len2 = max_increasing_len(l2.begin(), l2.end());
    if (len2 == 4) std::cout << "2  TRUE" << std::endl;
    else std::cout << "2  FALSE. Expected 4, recieved " << len2 << std::endl;
//
    std::list<int> const l3 = {-3, -2, -1, 0, 0, 1, 2, 3, 4, 5};
    size_t len3 = max_increasing_len(l3.begin(), l3.end());
    if (len3 == 6) std::cout << "3  TRUE" << std::endl;
    else std::cout << "3  FALSE. Expected 6, recieved " << len3 << std::endl;
//
    std::list<int> const l4 = {1, 2, 3};
    int len4 = max_increasing_len(l4.begin(), l4.end());
    if (len4 == 3) std::cout << "4  TRUE" << std::endl;
    else std::cout << "4  FALSE. Expected 3, recieved " << len4 << std::endl;
//
    std::list<int> const l5 = {};
    int len5 = max_increasing_len(l5.begin(), l5.end());
    if(len5 == 0) std::cout << "5  TRUE" << std::endl;
    else std::cout << "5  FALSE. Expected 0, recieved " << len5 << std::endl;
//
    std::list<int> const l6 = {1, 1, 1, 1, 1};
    int len6 = max_increasing_len(l6.begin(), l6.end());
    if(len6 == 1) std::cout << "6  TRUE" << std::endl;
    else std::cout << "6  FALSE. Expected 1, recieved " << len6 << std::endl;
// 
    std::list<int> const l7 = {1};
    int len7 = max_increasing_len(l7.begin(), l7.end());
    if(len7 == 1) std::cout << "7  TRUE" << std::endl;
    else std::cout << "7  FALSE. Expected 1, recieved " << len7 << std::endl;
// 
    std::list<int> const l8 = {1, 2, 3, 4, 1, 2};
    int len8 = max_increasing_len(l8.begin(), l8.end());
    if (len8 == 4) std::cout << "8  TRUE" << std::endl;
    else std::cout << "8  FALSE. Expected 4, received " << len8 << std::endl;
// 
    std::list<int> const l9 = {1, 2};
    int len9 = max_increasing_len(l9.begin(), l9.end());
    if (len9 == 2) std::cout << "9  TRUE" << std::endl;
    else std::cout << "9  FALSE. Expected 2, received " << len9 << std::endl;
// 
    std::list<int> const l10 = {2, 1};
    int len10 = max_increasing_len(l10.begin(), l10.end());
    if (len10 == 1) std::cout << "10 TRUE" << std::endl;
    else std::cout << "10 FALSE. Expected 1, received " << len10 << std::endl;
// 
    std::list<int> const l11 = {1, 1};
    int len11 = max_increasing_len(l11.begin(), l11.end());
    if (len11 == 1) std::cout << "11 TRUE" << std::endl;
    else std::cout << "11 FALSE. Expected 1, received " << len11 << std::endl;

    return 0;
}