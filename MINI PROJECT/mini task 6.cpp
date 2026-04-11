#include <iostream>
using namespace std;

class Shape {
public:
    virtual float area() = 0;
    virtual float perimeter() = 0;

    virtual ~Shape() {
        cout << "Shape Destructor Called" << endl;
    }
};

class Circle : public Shape {
private:
    float radius;

public:
    Circle(float r) {
        radius = r;
    }

    float area() {
        return 3.14 * radius * radius;
    }

    float perimeter() {
        return 2 * 3.14 * radius;
    }

    ~Circle() {
        cout << "Circle Destructor Called" << endl;
    }
};

class Rectangle : public Shape {
private:
    float length, width;

public:
    Rectangle(float l, float w) {
        length = l;
        width = w;
    }

    float area() {
        return length * width;
    }

    float perimeter() {
        return 2 * (length + width);
    }

    ~Rectangle() {
        cout << "Rectangle Destructor Called" << endl;
    }
};

int main() {
    Shape* s;

    float radius, length, width;

    cout << "Enter radius of circle: ";
    cin >> radius;

    s = new Circle(radius);
    cout << "Circle Area: " << s->area() << endl;
    cout << "Circle Perimeter: " << s->perimeter() << endl;
    delete s;

    cout << endl;

    cout << "Enter length of rectangle: ";
    cin >> length;
    cout << "Enter width of rectangle: ";
    cin >> width;

    s = new Rectangle(length, width);
    cout << "Rectangle Area: " << s->area() << endl;
    cout << "Rectangle Perimeter: " << s->perimeter() << endl;
    delete s;

    return 0;
}
