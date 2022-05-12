#ifndef POO_IOBASE_H
#define POO_IOBASE_H

#include <iostream>

using namespace std;

class IoBase {
private:
public:
    // metoda citire
    virtual istream &read(istream &is) {
        return is;
    }

    // metoda scriere
    virtual ostream &write(ostream &os) const {
        return os;
    }


    friend ostream &operator<<(ostream &os, const IoBase &base) {
        return base.write(os);
    }

    friend istream &operator>>(istream &is, IoBase &base) {
        return base.read(is);
    }
};


#endif //POO_IOBASE_H
