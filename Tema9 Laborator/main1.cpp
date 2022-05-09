#include <iostream>
using namespace std;



class CakeShape {
protected:
    double height;
public:
    CakeShape() : height(0) {}
    explicit CakeShape(double height) : height(height) {}

    virtual double volume() {
        return baseArea() * height;
    }

    virtual double baseArea() = 0;
};



class SquareCake : public CakeShape {
private:
    double side;
public:
    SquareCake() : side(0) {}
    SquareCake(double height, double side) : CakeShape(height), side(side) {}

    double baseArea() override {
        return side * side;
    }
};



class RectangleCake : public CakeShape {
private:
    double length, width;
public:
    RectangleCake() : length(0), width(0) {}
    RectangleCake(double height, double length, double width) : CakeShape(height), length(length), width(width) {}

    double baseArea() override {
        return length * width;
    }
};



class CircleCake : virtual public CakeShape {
private:
    double radius;
public:
    CircleCake() : radius(0) {}
    CircleCake(double height, double radius) : CakeShape(height), radius(radius) {}

    double baseArea() override {
        return radius * radius * 3.1415;
    }
};



class ConeCake : virtual public CakeShape{
private:
    double radius;
public:
    ConeCake() : radius(0) {}
    ConeCake(double height, double radius) : CakeShape(height), radius(radius) {}

    double baseArea() override {
        return radius * radius * 3.1415;
    }

    double volume() override{
        return baseArea() * height / 3;
    }
};



class SpecialCake : public CircleCake, public ConeCake {
public:
    SpecialCake(double height, double radius) : CakeShape(height), CircleCake(height, radius), ConeCake(height, radius) {}

    double baseArea() final{
        return ConeCake::baseArea();
    }

    double volume() override {
        return height * (CircleCake::baseArea() + ConeCake::baseArea() / 3);
    }
};



int main() {
    SquareCake squareCake(4, 5);
    RectangleCake rectangleCake(1, 5, 2);
    CircleCake circleCake(1, 5);
    ConeCake coneCake(1, 5);

    cout << squareCake.volume() << '\n';    //     100
    cout << rectangleCake.volume() << '\n'; //  10
    cout << circleCake.volume() << '\n';    //  78.5375
    cout << coneCake.volume() << "\n\n";

    SpecialCake specialCake(3, 5);
    cout << specialCake.volume() << '\n';
    return 0;
}