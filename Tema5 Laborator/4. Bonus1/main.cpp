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


struct Nota {
    int value{};
    string subject;
};

class PersoanaEvaluata : public IoBase{
protected:
    int n;
    vector<Nota> note;
public:
    PersoanaEvaluata() : n(0) {};
    explicit PersoanaEvaluata(int n, const vector<Nota> &note) : n(n), note(note) {}

    istream &read(istream &is) override {
        IoBase::read(is);
        cout << "Numarul de note:";
        is >> n;
        for (int i=0; i<n; i++) {
            Nota x;
            is >> x.value >> x.subject;
            note.push_back(x);
        }
        return is;
    }

    ostream &write(ostream &os) const override {
        IoBase::write(os);
        os<<"Numarul de note: "<<n<<"\n";
        for (int i=0; i<n; i++)
            os<<note[i].subject<<" "<<note[i].value<<"\n";
        return os;
    }
};

class Pupil : public PersoanaEvaluata {
private:
    string cycle;
public:
    Pupil() : PersoanaEvaluata() {}
    Pupil(int n, const vector<Nota> &note, const string &cycle) : PersoanaEvaluata(n, note), cycle(cycle) {}

    istream &read(istream &is) override {
        PersoanaEvaluata::read(is);
        cout<<"Ciclul:";
        is>>cycle;
        return is;
    }

    ostream &write(ostream &os) const override {
        PersoanaEvaluata::write(os);
        os<<"Ciclul: "<<cycle<<"\n";
        return os;
    }
};


class Student : public PersoanaEvaluata {
private:
    string college;
public:
    Student() : PersoanaEvaluata() {}
    Student(int n, const vector<Nota> &note, const string &college) : PersoanaEvaluata(n, note), college(college) {}

    istream &read(istream &is) override {
        PersoanaEvaluata::read(is);
        cout<<"Facultatea:";
        is>>college;
        return is;
    }

    ostream &write(ostream &os) const override {
        PersoanaEvaluata::write(os);
        os<<"Facultatea: "<<college<<"\n";
        return os;
    }
};


class CourseTaker : public PersoanaEvaluata {
private:
    string courseName;
public:
    CourseTaker() : PersoanaEvaluata() {}
    CourseTaker(int n, const vector<Nota> &note, const string &courseName) : PersoanaEvaluata(n, note), courseName(courseName) {}

    istream &read(istream &is) override {
        PersoanaEvaluata::read(is);
        cout<<"Numele cursului:";
        is>>courseName;
        return is;
    }

    ostream &write(ostream &os) const override {
        PersoanaEvaluata::write(os);
        os<<"Numele cursului: "<<courseName<<"\n";
        return os;
    }
};


int main(){
    cout<<"---PersoanaEvaluata---\n";
    PersoanaEvaluata p1;
    cin>>p1;
    cout<<p1<<"\n";

    cout<<"---Pupil---\n";
    Pupil p2;
    cin>>p2;
    cout<<p2<<"\n";

    cout<<"---Student---\n";
    Student p3;
    cin>>p3;
    cout<<p3<<"\n";

    cout<<"---CourseTaker---\n";
    CourseTaker p4;
    cin>>p4;
    cout<<p4<<"\n";

    return 0;
}