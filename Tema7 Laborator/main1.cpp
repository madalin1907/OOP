#include <iostream>
#include <cmath>
#include "util/IoBase.h"
using namespace std;


class Fraction : public IoBase {
protected:
    int a, b;
public:
    Fraction() : a(0), b(0) {}
    Fraction(int a, int b) : a(a), b(b) {}

    istream &read(istream &is) override {
        IoBase::read(is);
        cout << "a:";
        is >> a;
        cout << "b:";
        is >> b;
        return is;
    }

    ostream &write(ostream &os) const override {
        IoBase::write(os);
        os << a << "/" << b;
        return os;
    }

    int get_a() const{
        return a;
    }
    int get_b() const{
        return b;
    }
};


class IrrationalFraction : public Fraction {
private:
    double underSqrt;
public:
    IrrationalFraction() : underSqrt(0) {}
    IrrationalFraction(int a, int b, double c) : Fraction(a, b), underSqrt(c) {}


    istream &read(istream &is) override {
        Fraction::read(is);
        cout << "underSqrt:";
        is >> underSqrt;
        return is;
    }

    ostream &write(ostream &os) const override {
        Fraction::write(os);
        os <<"*sqrt(" << underSqrt << ")";
        return os;
    }

    double get_rad() const{
        return underSqrt;
    }
};


void show(const Fraction &f) {
    cout << "Fractia este: " << f << '\n';
}


bool operator < (const Fraction& f1, const IrrationalFraction& f2){
    double mezi = f1.get_a() * f2.get_b() * sqrt(f2.get_rad()); //produsul mezilor
    double extremi = f2.get_a() * f1.get_b(); //produsul extremilor
    return (mezi < extremi);
}


IrrationalFraction operator * (const Fraction &f1, const IrrationalFraction& f2) {
    int a = f1.get_a() * f2.get_a();
    int b = f1.get_b() * f2.get_b();
    return {a, b, f2.get_rad()};
}



int main() {
//     Fraction f1(2,3);
//     IrrationalFraction f2(1,2,2);

    // TODO Level 1: operator de citire si afisare
    Fraction f1;
    IrrationalFraction f2;
    cin>>f1>>f2;
    cout<<"Fractiile sunt "<<f1<<" si "<<f2<<"\n\n";

    // TODO level 2: Operator supraincarcat cu clase diferite
    if (f1 < f2) {
        cout << f1 << " < " << f2 << "\n\n";
    } else {
        cout << f2 << " < " << f1 << "\n\n";
    }

    // TODO Level 3: operatori si metode
    cout << "f1 * f2 = " << f1 * f2 << "\n\n";


    // TODO Intrebari spre rezolvare:

    // TODO Cand scadem doua fractii, una de forma a/b si cealalta a/b*sqrt(c), la ce forma ajungem?
    // A doua fractie se amplifica initial cu radicalul si va deveni ceva de forma a*sqrt(c) / b*c
    // Apoi cele doua fractii se aduc la acelasi numitor, care, scazute, vor ajunge la o forma generala de (a - b*sqrt(c)) / d).

    // TODO Ce se intampla cand rulam urmatoarele 2 linii de cod?
    show(f1);
    show(f2);
    // Fara "&", se va apela mereu functia de afisare din clasa de baza, adica Fraction. Deci, indiferent de tipul fractiei, se va afisa doar ceva de forma a/b.
    // TODO dar daca adaugam & la parametrul din show?
    // Cu "&", se va apela functia de afisare din clasa pe care o are parametrul. Deci, pentru un obiect de tip Fraction se va apela afisarea din clasa Fraction,
    // iar pentru un obiect din clasa IrrationalFraction se apeleaza functia de afisare suprascrisa in aceasta clasa.
}