#include <bits/stdc++.h>
using namespace std;

struct Nota {
    int value{};
    string subject;
};

class PersoanaEvaluata {
protected:
    vector<Nota> note;
public:
    PersoanaEvaluata() = default;
    explicit PersoanaEvaluata(const vector<Nota> &note) : note(note) {}

    double mean() {
        double sum = 0;
        for(auto &nota : note) {
            sum += nota.value;
        }
        return sum / double(note.size());
    }
};

class Pupil : public PersoanaEvaluata {
private:
    string cycle;
public:
    Pupil() : PersoanaEvaluata() {}
    Pupil(const vector<Nota> &note, const string &cycle) : PersoanaEvaluata(note), cycle(cycle) {}

    void showGradeSheet() {
        for (auto &x : note){
            cout<<x.subject<<": "<<x.value<<"\n";
        }
    }

    void gradesGroupedBySubject() {
        vector<string>subjects={"mate", "romana", "info"};
        for (auto &materie : subjects){
            cout<<materie<<": ";
            for (auto &nota : note){
                if (materie == nota.subject)
                    cout<<nota.value<<" ";
            }
            cout<<endl;
        }
    }
};


class Student : public PersoanaEvaluata {
private:
    string college;
public:
    Student() : PersoanaEvaluata() {}
    Student(const vector<Nota> &note, const string &college) : PersoanaEvaluata(note), college(college) {}
};


class CourseTaker : public PersoanaEvaluata {
private:
    string courseName;
public:
    CourseTaker() : PersoanaEvaluata() {}
    CourseTaker(const vector<Nota> &note, const string &courseName) : PersoanaEvaluata(note), courseName(courseName) {}
};


int main(){
    vector<Nota>v;
    int n;
    cout<<"Numarul de note:"; cin>>n;

    for (int i=0; i<n; ++i){
        Nota x;
        cin>>x.value>>x.subject;
        v.push_back(x);
    }

    Pupil P = Pupil(v, "gimnaziu");
    P.showGradeSheet(); cout<<"\n";
    P.gradesGroupedBySubject();
    cout<<"\nMedia tuturor notelor: "<<P.mean();
}
