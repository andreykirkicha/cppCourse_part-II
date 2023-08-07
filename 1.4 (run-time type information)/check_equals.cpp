#include <typeinfo>
#include "../include/expression.hpp"

bool check_equals(Expression const *left, Expression const *right)
{
    return (typeid(*left) == typeid(*right));
}