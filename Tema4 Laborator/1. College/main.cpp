#include <bits/stdc++.h>

using namespace std;

class Student{
private:
    string name;
    int group, semigroup;
    vector<int>grades;
public:
    Student(string name, int group, int semigroup, const vector<int> &grades):
            name(std::move(name)), group(group), semigroup(semigroup), grades(grades) {}
    Student(): group(0), semigroup(0) {}

    friend ostream &operator<<(ostream &os, const Student &student) {
        os<<"name: "<<student.name<<" \ngroup: "<<student.group<<" \nsemigroup: "<<student.semigroup<<" \ngrades: ";
        for (auto grade : student.grades)
            os<<grade<<' ';
        os<<"\n\n";
        return os;
    }

    friend istream &operator>>(istream &is, Student &student) {
        cout << "name:"; getline(is, student.name);
        cout << "group:"; is >> student.group;
        cout << "semigroup:"; is >> student.semigroup;
        int n, nota;
        cout << "Nr. of grades:"; is >> n;
        cout << "Grades:";
        student.grades.clear();
        for (int i = 0; i < n; ++i) {
            is >> nota;
            student.grades.push_back(nota);
        }
        return is;
    }

    void operator+=(int newGrade) {
        grades.push_back(newGrade);
        cout<<"New grade added ("<<newGrade<<")\n\n";
    }
};


int main(){
    Student s;
    cin>>s;
    cout<<"\n"<<s;

    int grade;
    cout<<"Add a new grade:";
    cin>>grade;
    s += grade;
    cout<<s;


    Student S = Student(
            "Enrique Neville",
            154,
            2,
            {9, 10, 7});
    cout<<S;

    return 0;
}
