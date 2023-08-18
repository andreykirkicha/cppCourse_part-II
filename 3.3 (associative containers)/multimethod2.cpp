#include <typeinfo>
#include <typeindex>
#include <functional>
#include <map>
#include <iostream>

// ====================================================================================================================

// 'Base' - base class of hierarchy
// 'Result' - multimethod return value type
// 'Commutative' - flag that reports if the class is commutative
template<typename Base, typename Result, bool Commutative>
struct Multimethod2
{
    using FunctionType = std::function<Result (Base *, Base *)>;
    using Pair = std::pair<std::type_index, std::type_index>;

    // Sets implementation of multimethod for classes "class1" and "class2" given by
    // typeid, "func" is a function or functional object which gets two pointers to 'Base' and
    // returns 'Result' value
    void addImpl(std::type_index const & class1, std::type_index const & class2, FunctionType func)
    {
        impl.insert(std::make_pair(class1, class2), func);
    }

    // Checks if there is implementation of multimethod for
    // "object1" and "object2" types
    bool hasImpl(Base * object1, Base * object2) const
    {
        if (Commutative)
        {
            if (hasImpl(object2, object1))
                return true; 
        }

        return (impl.find(std::make_pair(*object1, *object2)) != impl.end()) ? true : false; 
    }

    // Applies multimethod to the objects using pointers "object1" and "object2"
    Result call(Base * object1, Base * object2) const
    {
        // возвращает результат применения реализации
        // мультиметода к a и b
        return *(impl.find(std::make_pair(*object1, *object2)));
    }

    std::map<Pair, FunctionType> impl;
};

// ====================================================================================================================

// Application example

struct Shape {};

struct Rectangle : Shape {};

struct Triangle : Shape {};

bool is_intersect_r_r(Shape * a, Shape * b) { std::cout << "R x R" << std::endl; return true; }

bool is_intersect_r_t(Shape * a, Shape * b) { std::cout << "R x T" << std::endl; return true; }

// ====================================================================================================================

int main() 
{
    // Multimethod for heirs of 'Shape'
    // Returns 'bool'
    // Commutative
    Multimethod2<Shape, bool, true> is_intersect;

    // Add implementation of multimethod for two rectangles
    is_intersect.addImpl(typeid(Rectangle), typeid(Rectangle), is_intersect_r_r);

    // Add implementation of multimethod for rectangle and triangle
    is_intersect.addImpl(typeid(Rectangle), typeid(Triangle), is_intersect_r_t);

    // Make two shapes
    Shape * shape1 = new Triangle();
    Shape * shape2 = new Rectangle();

    // Check if some implementation for "shape1" and "shape2" exists
    if (is_intersect.hasImpl(shape1, shape2))
    {
         // Call is_intersect_r_t(s2, s1)
         bool res = is_intersect.call(shape1, shape2);

         std::cout << res << std::endl;
    }

    return 0;
}