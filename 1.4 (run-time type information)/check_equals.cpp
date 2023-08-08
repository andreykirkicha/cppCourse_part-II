#include <typeinfo>
#include "../include/expression.hpp"

// Returns 'true' if types of left and right objects are the same
bool check_equals(Expression const *left, Expression const *right)
{
    return (typeid(*left) == typeid(*right));
}