#include <bits/stdc++.h>
using namespace std;

class IoBase {
private:
public:
    virtual istream& read(istream& is) {
        return is;
    }

    virtual ostream& write(ostream& os) const {
        return os;
    }

    friend istream &operator >>(istream &is, IoBase &base) {
        return base.read(is);
    }

    friend ostream &operator <<(ostream &os, const IoBase &base) {
        return base.write(os);
    }
};

class PongGame : public IoBase {
private:
    string player1, player2;
public:
    istream &read(istream &is) override {
        IoBase::read(is);
        cout << "Player1:";
        is >> player1;
        cout << "Player2:";
        is >> player2;
        return is;
    }

    ostream &write(ostream &os) const override {
        IoBase::write(os);
        os << "Player1:" << player1 << "\n";
        os << "Player2:" << player2;
        return os;
    }
};


int main(){
    PongGame p;
    cin>>p;
    cout<<p;
    return 0;
}