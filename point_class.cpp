#include<iostream>
#include<cmath>
using namespace std;

class Point
{
    public:
        double x;
        double y;

        Point(double a = 0, double b = 0)
        {
            x = a;
            y = b;
        };

        Point operator+(const Point &P)
        {
            Point c;
            c.x = this -> x + P.x;
            c.y = this -> y + P.y;
            return c;
        }

        Point operator-(const Point &P)
        {
            Point c;
            c.x = this -> x - P.x;
            c.y = this -> y - P.y;
            return c;
        }

        Point operator*(const int &a)
        {
            Point c;
            c.x = this -> x * a;
            c.y = this -> y * a;
            return c;
        }

        Point operator/(const int &a)
        {
            Point c;
            c.x = this -> x / a;
            c.y = this -> y / a;
            return c;
        }

        double module()
        {
            return sqrt(this -> x * this -> x + this -> y * this -> y);
        }

        double distance(const Point &P2)
        {
            return (*this - P2).module();
        }

        friend ostream& operator<<(ostream& out, const Point &P)
        {  
            out << "(" << P.x << ", " << P.y << ")"; 
            return out;
        }
};

int main(void)
{
    Point x;
    Point y (3, 2.1);
    Point z, a;

    x.x = 5;
    z = x + y;
    a = x - y;

    cout << "x = " << x << endl;
    cout << "y = " << y << endl;
    cout << "z = " << z << endl;
    cout << "a = " << a << endl;

    z = z * 2;
    a = a / 2;
    cout << "z = " << z << endl;
    cout << "a = " << a << endl;

    cout << "dist = " << x.distance(y) << endl;

    return 0;
}