#include <bits/stdc++.h>
#include "IoBase.h"
using namespace std;


class Chair : public IoBase {
protected:
    double price;
    string color;
public:
    Chair() : price(0) {}
    Chair(double price, const string &color) : price(price), color(color) {}

    istream &read(istream &is) override {
        IoBase::read(is);
        cout << "price:"; is >> price; is.get();
        cout << "color:"; getline(is, color);
        return is;
    }

    ostream &write(ostream &os) const override {
        IoBase::write(os);
        cout << "price: " << price;
        cout << ", color: " << color;
        return os;
    }
};


class ArmChair : public Chair {
protected:
    string armRestMaterial;
public:
    ArmChair() = default;
    ArmChair(double price, const string &color, const string &armRestMaterial) :
              Chair(price, color),
              armRestMaterial(armRestMaterial) {}

    istream &read(istream &is) override {
        Chair::read(is);
        cout << "armRestMaterial:"; getline(is, armRestMaterial);
        return is;
    }

    ostream &write(ostream &os) const override {
        Chair::write(os);
        cout << ", armRestMaterial: " << armRestMaterial;
        return os;
    }
};


class Sofa : public Chair {
private:
    int maxPeople;
    double length;
public:
    Sofa() : maxPeople(0), length(0) {}
    Sofa(double price, const string &color, int maxPeople, double length) :
            Chair(price, color), maxPeople(maxPeople), length(length) {}

    istream &read(istream &is) override {
        Chair::read(is);
        cout << "maxPeople:"; is >> maxPeople;
        cout << "length:"; is >> length;
        is.get();
        return is;
    }

    ostream &write(ostream &os) const override {
        Chair::write(os);
        cout << ", maxPeople: " << maxPeople;
        cout << ", length: " << length;
        return os;
    }
};


class MassageChair : public ArmChair {
private:
    int cntLevels;
    double cableLength;
public:
    MassageChair() : cntLevels(0), cableLength(0) {}
    MassageChair(double price, const string &color, const string &armRestMaterial, int cntLevels, double cableLength)
            : ArmChair(price, color, armRestMaterial), cntLevels(cntLevels), cableLength(cableLength) {}

    istream &read(istream &is) override {
        ArmChair::read(is);
        cout << "cntLevels:"; is >> cntLevels;
        cout << "cableLength:"; is >> cableLength;
        is.get();
        return is;
    }

    ostream &write(ostream &os) const override {
        ArmChair::write(os);
        cout << ", cntLevels: " << cntLevels;
        cout << ", cableLength: " << cableLength;
        return os;
    }
};


// Pentru a citi un scaun in mai multe zone ale codului, dar si pentru a refolosi
// usor cod, am implementat o functie globala de citire.
void citire(shared_ptr<Chair> &newChair){
    cout << "Choose chair type (0 = simple, 1 = ArmChair, 2 = Sofa, 3 = MassageChair):";
    int type; cin >> type;

    if (type == 0)
        newChair = make_shared<Chair>();
    else if (type == 1)
        newChair = make_shared<ArmChair>();
    else if (type == 2)
        newChair = make_shared<Sofa>();
    else if (type == 3)
        newChair = make_shared<MassageChair>();

    cin >> *newChair;
}


int main(){
    vector <shared_ptr <Chair> > allKindsOfChairs = {
            make_shared <ArmChair> (
                ArmChair(200, "brown", "Metal")
            ),
            make_shared <Sofa> (
                Sofa(790, "cream", 5, 6.7)
            ),
            make_shared <MassageChair> (
                MassageChair(590, "silver", "Plastic", 3, 2.7)
            ),
    };

    for (auto &chair : allKindsOfChairs)
        cout << *chair << '\n';


    shared_ptr <Chair> newChair;
    citire(newChair);
    cout << *newChair;

    return 0;
}