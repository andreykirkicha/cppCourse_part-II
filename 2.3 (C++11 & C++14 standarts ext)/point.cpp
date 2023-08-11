struct Point
{
    constexpr Point(double x, double y) 
        : x(x), y(y) 
    {}

    double x = 0;
    double y = 0;
};

// ====================================================================================================================

constexpr Point operator + (Point const & p_1, Point const & p_2)
{
    return Point(p_1.x + p_2.x, p_1.y + p_2.y);
}

constexpr Point operator - (Point const & p_1, Point const & p_2)
{
    return Point(p_1.x - p_2.x, p_1.y - p_2.y);
}

constexpr double operator * (Point const & p_1, Point const & p_2)
{
    return p_1.x * p_2.x + p_1.y * p_2.y;
}