#ifndef _POINT_HPP_
#define _POINT_HPP_
#include <iostream>
using namespace std;
class Point
{
public:
    Point():x(0),y(0){}
    Point(int a, int b):x(a), y(b){}
    bool operator==(const Point& obj) const
    {
        return this->x * this->y == obj.x * obj.y;
    }
    bool operator>=(const Point& obj) const
    {
        return this->x * this->y >= obj.x * obj.y;
    }
    bool operator<=(const Point& obj) const
    {
        return this->x * this->y <= obj.x * obj.y;
    }
    bool operator>(const Point& obj) const
    {
        return this->x * this->y > obj.x * obj.y;
    }
    bool operator<(const Point& obj) const
    {
        return this->x * this->y < obj.x * obj.y;
    }
    void show() const
    {
        cout << "x = " << x << ", y = " << y << ", x * y = " << x * y << endl;
    }
private:
    int x;
    int y;
};
#endif/*_POINT_HPP_*/