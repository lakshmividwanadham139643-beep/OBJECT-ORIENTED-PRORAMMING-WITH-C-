#include <iostream>
#include <cmath>
using namespace std;

class Point {
public:
    int x, y;

    Point(int a=0, int b=0) {
        x = a;
        y = b;
    }

    Point operator+(Point p) {
        return Point(x + p.x, y + p.y);
    }

    Point operator-(Point p) {
        return Point(x - p.x, y - p.y);
    }

    Point operator-() {
        return Point(-x, -y);
    }

    void display() {
        cout << "(" << x << "," << y << ")" << endl;
    }
};

class Line {
public:
    Point p1, p2;

    Line(Point a, Point b) {
        p1 = a;
        p2 = b;
    }

    double length() {
        return sqrt(pow(p2.x - p1.x,2) + pow(p2.y - p1.y,2));
    }
};

int main() {

    Point p1, p2, result;
    cout<<"----------2D GEOMERTY TOOLKIT-----------"<<endl;

    cout<<"Enter Point 1 (x y): ";
    cin>>p1.x>>p1.y;

    cout<<"Enter Point 2 (x y): ";
    cin>>p2.x>>p2.y;

    cout<<"\n---- Results ----\n";

    result = p1 + p2;
    cout<<"Addition of Points: ";
    result.display();

    result = p1 - p2;
    cout<<"Subtraction of Points: ";
    result.display();

    result = -p1;
    cout<<"Negated Point 1: ";
    result.display();

    Line l(p1,p2);
    cout<<"Length of Line = "<<l.length()<<endl;

    return 0;
}
