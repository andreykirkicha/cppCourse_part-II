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
        std::type_index i1(class1);
        std::type_index i2(class2);

        if (Commutative) { if (i2 < i1) std::swap(i1, i2); }

        Pair const & key = std::make_pair(i1, i2);
        auto iterator = impl.find(key);

        if (iterator == impl.end()) { impl.emplace(std::move(key), std::move(func)); }
        else { iterator->second = std::move(func); }
    }

    // Checks if there is implementation of multimethod for
    // "object1" and "object2" types
    bool hasImpl(Base * object1, Base * object2) const
    {
        std::type_index i1(typeid(*object1));
        std::type_index i2(typeid(*object2));

        if (Commutative) { if (i2 < i1) std::swap(i1, i2); }
        
        Pair const & key = std::make_pair(i1, i2);

        return (impl.find(key) != impl.end()) ? true : false;
    }

    // Applies multimethod to the objects using pointers "object1" and "object2"
    Result call(Base * object1, Base * object2) const
    {
        std::type_index i1(typeid(*object1));
        std::type_index i2(typeid(*object2));

        if (Commutative) { if (i2 < i1) std::swap(i1, i2); }

        Pair const & key = std::make_pair(i1, i2);

        return impl.find(key)->second(object1, object2);
    }

private:
    std::map<Pair, FunctionType> impl;
};

// ====================================================================================================================

// Application example

struct Shape 
{
    virtual void foo() {}
};

struct Rectangle : Shape {};
struct Triangle : Shape {};

bool is_intersect_r_r(Shape * a, Shape * b) { std::cout << "R x R"; return true; }
bool is_intersect_rr(Shape * a, Shape * b) { std::cout << "r x r"; return true; }
bool is_intersect_r_t(Shape * a, Shape * b) { std::cout << "R x T"; return true; }
bool is_intersect_t_r(Shape * a, Shape * b) { std::cout << "T x R"; return true; }

template<typename Base, typename Result, bool Commutative>
void test(Multimethod2<Base, Result, Commutative> const & m, Shape * shape1, Shape * shape2)
{
    if (m.hasImpl(shape1, shape2)) { bool res = m.call(shape1, shape2); }
    std::cout << std::endl;
}

// ====================================================================================================================

int main()
{
    // Multimethod for heirs of 'Shape'
    // Returns 'bool'
    // Commutative
    Multimethod2<Shape, bool, true> is_intersect;

    std::cout << "=== Commutative ===" << std::endl;

    is_intersect.addImpl(typeid(Rectangle), typeid(Rectangle), is_intersect_r_r);
    is_intersect.addImpl(typeid(Rectangle), typeid(Triangle), is_intersect_r_t);

    Shape * shape1 = new Triangle();
    Shape * shape2 = new Rectangle();

    test(is_intersect, shape1, shape2); // R x T
    test(is_intersect, shape2, shape1); // R x T

    is_intersect.addImpl(typeid(Triangle), typeid(Rectangle), is_intersect_t_r);

    test(is_intersect, shape1, shape2); // T x R
    test(is_intersect, shape2, shape1); // T x R

    is_intersect.addImpl(typeid(Rectangle), typeid(Triangle), is_intersect_t_r);
    test(is_intersect, shape1, shape2); // T x R
    test(is_intersect, shape2, shape1); // T x R

    test(is_intersect, shape1, shape1); // 
    test(is_intersect, shape2, shape2); // R x R

    is_intersect.addImpl(typeid(Rectangle), typeid(Rectangle), is_intersect_rr);
    test(is_intersect, shape2, shape2); // r x r

    // ================================================================================================================

    // Multimethod for heirs of 'Shape'
    // Returns 'bool'
    // Not commutative
    Multimethod2<Shape, bool, false> is_intersect_not_com;

    std::cout << "=== Not commutative ===" << std::endl;

    is_intersect_not_com.addImpl(typeid(Rectangle), typeid(Rectangle), is_intersect_r_r);
    is_intersect_not_com.addImpl(typeid(Rectangle), typeid(Triangle), is_intersect_r_t);

    test(is_intersect_not_com, shape1, shape2); // 
    test(is_intersect_not_com, shape2, shape1); // R x T

    test(is_intersect_not_com, shape1, shape1); // 
    test(is_intersect_not_com, shape2, shape2); // R x R

    is_intersect_not_com.addImpl(typeid(Rectangle), typeid(Rectangle), is_intersect_rr);
    test(is_intersect_not_com, shape2, shape2); // r x r

    is_intersect_not_com.addImpl(typeid(Triangle), typeid(Rectangle), is_intersect_t_r);
    test(is_intersect_not_com, shape1, shape2); // T x R
    test(is_intersect_not_com, shape2, shape1); // R x T

    return 0;
}