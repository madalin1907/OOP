#include <iostream>
using namespace std;

/*
   TODO discutam despre metode virtual si object slicing pe un exemplu mai simplu
   Avem clasa de baza CakeShape = o forma de tort despre care stim inaltimea, dar nu si baza (patrat, dreptunghi, etc)
   Chiar si asa, putem calcula volumul, cu ajutorul unei functii virtuale care va calcula aria bazei:
*/

class CakeShape {
protected:
    double height;
public:
    CakeShape() : height(0) {}
    explicit CakeShape(double height) : height(height) {}

    double volume() {
        return baseArea() * height;
    }

    virtual double baseArea() { // Aria bazei va fi calculata in copii, prin suprascrierea metodei virtuale.
        return 0;               // Deocamdată returnăm 0, deoarece nu stim forma bazei.
    }
};


// TODO Pentru fiecare dintre clasele de mai jos vom:
//      * adauga laturile/raza;
//      * genera constructorii cu parametrii;
//      * calcula aria bazei, prin suprascriere.


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
public:


};


class CircleCake : public CakeShape {
private:
    double radius;
public:
    CircleCake() : radius(0) {}
    CircleCake(double height, double radius) : CakeShape(height), radius(radius) {}

    double baseArea() override {
        return radius * radius * 3.1415;
    }
};


int main() {
    CakeShape cake(4);
    SquareCake cube(2, 2);

    cout << cake.volume() << '\n'; // 0
    cout << cube.volume() << '\n'; // 8

    SquareCake squareCake(4, 5);
    RectangleCake rectangleCake(1, 5, 2);
    CircleCake circleCake(1, 5);

    cout << squareCake.volume() << '\n';    //     100
    cout << rectangleCake.volume() << '\n'; //  10
    cout << circleCake.volume() << '\n';    //  78.6475

    return 0;
}