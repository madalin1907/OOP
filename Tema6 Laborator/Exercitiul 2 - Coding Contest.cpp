#include <bits/stdc++.h>
#include "IoBase.h"
using namespace std;



class Participant : public IoBase{
private:
    string nume, cnp;
public:
    Participant() = default;
    Participant(const string &nume, const string &cnp) : nume(nume), cnp(cnp) {}

    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;
};


istream &Participant::read(istream &is) {
    IoBase::read(is);
    cout << "nume:"; getline(is, nume);
    cout << "cnp:"; getline(is, cnp);
    return is;
}

ostream &Participant::write(ostream &os) const {
    IoBase::write(os);
    os << "nume: " << nume << "\n";
    os << "cnp: " << cnp << "\n";
    return os;
}


void citire(shared_ptr<Participant> &newParticipant);


class Elev : public Participant{
private:
    string limbaj;
public:
    Elev() = default;
    Elev(const string &name, const string &cnp, const string &limbaj) : Participant(name, cnp), limbaj(limbaj) {}

    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;
};


istream &Elev::read(istream &is) {
    Participant::read(is);
    cout << "limbaj:"; getline(is, limbaj);
    return is;
}

ostream &Elev::write(ostream &os) const {
    Participant::write(os);
    os << "limbaj: " << limbaj << "\n";
    return os;
}



class Student  : public Participant{
private:
    int an_studii;
    vector <string> limbaje;
public:
    Student() : an_studii(0) {}
    Student(const string &name, const string &cnp, int anStudii, const vector<string> &limbaje) : Participant(name, cnp),
                                                                                                    an_studii(anStudii),
                                                                                                    limbaje(limbaje) {}

    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;
};


istream &Student::read(istream &is) {
    Participant::read(is);
    cout << "an studii:"; is >> an_studii;
    int n;
    cout << "nr limbaje:"; is>>n; is.get();
    string s;
    for (int i = 1; i <= n; i++){
        cin >> s;
        limbaje.push_back(s);
    }
    return is;
}

ostream &Student::write(ostream &os) const {
    Participant::write(os);
    os << "an studii: " << an_studii << "\nlimbaje: " ;
    for (auto &x : limbaje)
        os << x << ' ';
    os << "\n";
    return os;
}



class ProgramatorProfesional : public Participant{
private:
    vector <string> limbaje;
    vector <string> firme;
public:
    ProgramatorProfesional() = default;
    ProgramatorProfesional(const string &name, const string &cnp, const vector<string> &limbaje,
                           const vector<string> &firme) : Participant(name, cnp), limbaje(limbaje), firme(firme) {}

    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;
};


istream &ProgramatorProfesional::read(istream &is) {
    Participant::read(is);
    int n; string s;

    cout << "nr limbaje:"; is >> n;
    for (int i = 1; i <= n; i++){
        cin >> s;
        limbaje.push_back(s);
    }

    cout << "nr firme:"; is >> n;
    for (int i = 1; i <=n; i++){
        cin >> s;
        firme.push_back(s);
    }
    return is;
}

ostream &ProgramatorProfesional::write(ostream &os) const {
    Participant::write(os);
    os << "limbaje: ";
    for (auto &x : limbaje)
        os << x << " ";

    os << "\nfirme: ";
    for (auto &x : firme)
        os << x << " ";
    os << "\n";
    return os;
}



class Echipa : public IoBase{
private:
    int nr_max_participanti;
    string nume, domeniu;
    ProgramatorProfesional mentor;
    vector <shared_ptr <Participant>> membri;
public:
    Echipa() : nr_max_participanti(0) {}
    Echipa(int nrMaxParticipanti, const string &nume, const string &domeniu, const ProgramatorProfesional &mentor,
           const vector<shared_ptr<Participant>> &membri) : nr_max_participanti(nrMaxParticipanti), nume(nume),
                                                             domeniu(domeniu), mentor(mentor), membri(membri) {}

    const string &getNume() const {
        return nume;
    }

    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;

    void eliminaMembru(int index);
    void adaugaMembru(const shared_ptr <Participant>& p);
    void inregistreazaNouMembru();
    void modificaMentor(ProgramatorProfesional &p);
    int locuriLibere();
};


istream &Echipa::read(istream &is) {
    cout << "nr max participanti:"; is >> nr_max_participanti; is.get();
    cout << "nume echipa:"; getline(is, nume);
    cout << "domeniu:"; getline(is, domeniu);
    cout << "mentor:\n"; is >> mentor;

    for (int i = 1; i <= nr_max_participanti; ++i) {
        shared_ptr<Participant> newParticipant;
        citire(newParticipant);
        membri.push_back(newParticipant);
    }
    return is;
}


ostream &Echipa::write(ostream &os) const {
    os << "nr max participanti: " << nr_max_participanti;
    os << ", nume echipa: " << nume;
    os << ", domeniu: " << domeniu << "\n\n";
    os << "mentor:\n" << mentor <<"\n";
    for (auto &membru : membri)
        os << "membru:\n" << *membru << "\n";
    return os;
}


void Echipa::eliminaMembru(int index) {
    if (membri.empty())
        cout << "Echipa nu are membri.\n";
    else if (index >= membri.size())
        cout << "Index-ul " << index << " este prea mare.\n";
    else
        membri.erase(membri.begin() + index);
}

void Echipa::adaugaMembru(const shared_ptr<Participant> &p) {
    if (membri.size() >= nr_max_participanti)
        cout << "Nu se poate adauga un alt membru (echipa completa).\n";
    else
        membri.push_back(p);
}

void Echipa::inregistreazaNouMembru() {
    if (membri.size() >= nr_max_participanti)
        cout << "Nu se poate inregistra un alt membru (echipa completa).\n";
    else {
        shared_ptr<Participant> newParticipant;
        citire(newParticipant);
        membri.push_back(newParticipant);
    }
}

void Echipa::modificaMentor(ProgramatorProfesional &p) {
    mentor = p;
}

int Echipa::locuriLibere() {
    return nr_max_participanti - int(membri.size());
}


void citire(shared_ptr<Participant> &newParticipant){
    int type;
    cout << "Tip participant: (0-elev, 1-student, 2-programator profesional):";
    cin >> type; cin.get();
    if (type == 0)
        newParticipant = make_shared<Elev>();
    else if (type == 1)
        newParticipant = make_shared<Student>();
    else if (type == 2)
        newParticipant = make_shared<ProgramatorProfesional>();
    cin >> *newParticipant;
}



int main(){
    Echipa team = Echipa(5, "Nume echipa", "Domeniu",
                         {"Gigel", "123456789",
                                 {"C++", "Java", "Python"},
                                 {"Firma1", "Firma2", "Firma3"}},
                         {make_shared <Elev>(
                                         Elev("Nume Elev", "8754345678", "C++")
                                 ),
                                 make_shared <Student>(
                                         Student("Nume Student", "98765798", 3, {"C++", "Java", "JavaScript"})
                                 ),
                                 make_shared <ProgramatorProfesional>(
                                         ProgramatorProfesional("Nume Pro", "9656765680", {"Python", "C++", "Go"}, {"Firma1, Firma2, Firma3"})
                                 )
                         });

    team.eliminaMembru(2);


    team.adaugaMembru(make_shared <ProgramatorProfesional>(
            ProgramatorProfesional("Adaugat", "96563210", {"Python", "C++", "Go"}, {"Firma1, Firma2, Firma3"})
    ));

    team.inregistreazaNouMembru();

    ProgramatorProfesional modif = ProgramatorProfesional("Mentor Modificat", "321321", {"Python", "C++", "HTML"}, {"Firma1, Firma2, Firma3"});
    team.modificaMentor(modif);

    cout << team;

    int locuri = team.locuriLibere();
    if (!locuri)
        cout << "Echipa " << team.getNume() << " este completa (0 locuri libere).\n";
    else
        cout << "Echipa " << team.getNume() << " are " << locuri << " locuri libere.\n";

    return 0;
}