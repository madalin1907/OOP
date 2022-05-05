#include <bits/stdc++.h>
#include "IoBase.h"
using namespace std;


class Fruit : public IoBase{
protected:
    string name, variety;
public:
    Fruit() = default;
    Fruit(const string &name, const string &variety) : name(name), variety(variety) {}

    istream &read(istream &is) override {
        IoBase::read(is);
        cout << "name:"; is >> name;
        cout << "variety:"; is >> variety;
        return is;
    }

    ostream &write(ostream &os) const override {
        IoBase::write(os);
        os << "name: " << name << "\n";
        os << "variety: " << variety << "\n";
        return os;
    }
};


class Juice : public IoBase{
protected:
    double quantity;
public:
    Juice() : quantity(0) {}
    explicit Juice(double quantity) : quantity(quantity) {}

    istream &read(istream &is) override {
        IoBase::read(is);
        cout << "quantity:"; is >> quantity;
        return is;
    }

    ostream &write(ostream &os) const override {
        IoBase::write(os);
        os << "quantity: " << quantity << "\n";
        return os;
    }

    virtual double juice_quantity(){
        return quantity;
    }
};


class SimpleJuice : public Juice{
protected:
    Fruit fruit;
public:
    SimpleJuice() = default;
    SimpleJuice(double quantity, const Fruit &fruit) : Juice(quantity), fruit(fruit) {}

    istream &read(istream &is) override {
        Juice::read(is);
        is >> fruit;
        return is;
    }

    ostream &write(ostream &os) const override {
        Juice::write(os);
        os << fruit;
        return os;
    }
};


class MixedJuice : public Juice{
protected:
    vector <Fruit> fruits;
public:
    MixedJuice() = default;
    MixedJuice(double quantity, const vector<Fruit> &fruits) : Juice(quantity), fruits(fruits) {}

    istream &read(istream &is) override {
        Juice::read(is);
        int nr_fructe;
        is >> nr_fructe;
        for (int i = 1; i<= nr_fructe; ++i){
            Fruit f;
            is >> f;
            fruits.push_back(f);
        }
        return is;
    }

    ostream &write(ostream &os) const override {
        Juice::write(os);
        for (auto &f : fruits)
            os << f;
        return os;
    }
};


class IcedJuice : public MixedJuice{
protected:
    double ice_quantity;
public:
    IcedJuice() : ice_quantity(0) {}
    IcedJuice(double quantity, const vector<Fruit> &fruits, double iceQuantity) : MixedJuice(quantity, fruits),
                                                                                  ice_quantity(iceQuantity) {}

    istream &read(istream &is) override {
        MixedJuice::read(is);
        cout<<"ice quantity:";
        is >> ice_quantity;
        return is;
    }

    ostream &write(ostream &os) const override {
        MixedJuice::write(os);
        os << "ice quantity: " << ice_quantity;
        return os;
    }

    double juice_quantity() override {
        return quantity + ice_quantity;
    }
};


int main(){
    vector <shared_ptr <Juice> > stock = {
            make_shared<SimpleJuice>(
                    SimpleJuice(550, Fruit("Apple", "Granny Smith"))
            ),
            make_shared<MixedJuice>(
                    MixedJuice(
                            560,
                            {
                                    Fruit("Apple", "Granny Smith"),
                                    Fruit("Banana", "Musa balbisiana"),
                            }
                    )
            ),
            make_shared<IcedJuice>(
                    IcedJuice(
                            560,
                            {
                                    Fruit("Apple", "Granny Smith"),
                                    Fruit("Banana", "Musa balbisiana"),
                            },
                            150
                    )
            ),
    };

    for (auto &juice : stock) {
        cout << juice -> juice_quantity() << ' ';
    }

    return 0;
}