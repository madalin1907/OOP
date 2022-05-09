#include <bits/stdc++.h>
#include "util/IoBase.h"
using namespace std;



class Jucarie : public IoBase{
protected:
    string denumire, tip;
    double dimensiune;
public:
    Jucarie();

    Jucarie(const string &denumire, const string &tip, double dimensiune);

    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;
};

Jucarie::Jucarie() : dimensiune(0) {}

Jucarie::Jucarie(const string &denumire, const string &tip, double dimensiune) : denumire(denumire), tip(tip),
                                                                                 dimensiune(dimensiune) {}

istream &Jucarie::read(istream &is) {
    IoBase::read(is);
    cout << "Denumire:";
    getline(is, denumire);
    cout << "Tip:";
    getline(is, tip);
    cout << "Dimensiune:";
    is >> dimensiune;
    is.get();
    return is;
}

ostream &Jucarie::write(ostream &os) const {
    IoBase::write(os);

    os << "Denumire: " << denumire
       << ", Tip: " << tip
       << ", Dimensiune: " << dimensiune;

    return os;
}



class JucarieClasica : public Jucarie{
private:
    string material, culoare;
public:
    JucarieClasica();

    JucarieClasica(const string &denumire, const string &tip, double dimensiune, const string &material,
                   const string &culoare);

    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;
};

JucarieClasica::JucarieClasica() = default;

JucarieClasica::JucarieClasica(const string &denumire, const string &tip, double dimensiune, const string &material,
                               const string &culoare) : Jucarie(denumire, tip, dimensiune), material(material),
                                                        culoare(culoare) {}

istream &JucarieClasica::read(istream &is) {
    Jucarie::read(is);
    cout << "Material:";
    getline(is, material);
    cout << "Culoare:";
    getline(is, culoare);
    return is;
}

ostream &JucarieClasica::write(ostream &os) const {
    Jucarie::write(os);
    cout << ", Material: " << material
         << ", Culoare: " << culoare;
    return os;
}



class JucarieEducativa : virtual public Jucarie{
protected:
    string abilitateDezvoltata;
public:
    JucarieEducativa();

    JucarieEducativa(const string &denumire, const string &tip, double dimensiune, const string &abilitateDezvoltata);

    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;
};

JucarieEducativa::JucarieEducativa() = default;

JucarieEducativa::JucarieEducativa(const string &denumire, const string &tip, double dimensiune,
                                   const string &abilitateDezvoltata) : Jucarie(denumire, tip, dimensiune),
                                                                        abilitateDezvoltata(abilitateDezvoltata) {}

istream &JucarieEducativa::read(istream &is) {
    Jucarie::read(is);
    cout << "Abilitate dezvoltata:";
    getline(is, abilitateDezvoltata);
    return is;
}

ostream &JucarieEducativa::write(ostream &os) const {
    Jucarie::write(os);
    cout << ", Abilitate dezvoltata: " << abilitateDezvoltata;
    return os;
}



class JucarieElectronica : virtual public Jucarie{
protected:
    unsigned int nrBaterii;
public:
    JucarieElectronica();

    JucarieElectronica(const string &denumire, const string &tip, double dimensiune, unsigned int nrBaterii);

    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;
};

JucarieElectronica::JucarieElectronica() : nrBaterii(0) {}

JucarieElectronica::JucarieElectronica(const string &denumire, const string &tip, double dimensiune,
                                       unsigned int nrBaterii) : Jucarie(denumire, tip, dimensiune),
                                                                 nrBaterii(nrBaterii) {}

istream &JucarieElectronica::read(istream &is) {
    Jucarie::read(is);
    cout << "Nr. baterii:";
    is >> nrBaterii;
    is.get();
    return is;
}

ostream &JucarieElectronica::write(ostream &os) const {
    Jucarie::write(os);
    cout << ", Nr. baterii: " << nrBaterii;
    return os;
}



class JucarieModerna : public JucarieEducativa, public JucarieElectronica{
private:
    string brand, model;
public:
    JucarieModerna();

    JucarieModerna(const string &denumire, const string &tip, double dimensiune,
                   const string &brand, const string &model);

    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;
};

JucarieModerna::JucarieModerna(){
    JucarieElectronica::nrBaterii = 1;
    JucarieEducativa::abilitateDezvoltata = "generala";
}

JucarieModerna::JucarieModerna(const string &denumire, const string &tip, double dimensiune, const string &brand,const string &model) :
        JucarieEducativa(denumire, tip, dimensiune, "generala"), JucarieElectronica(denumire, tip, dimensiune, 1),
        brand(brand), model(model) {}

istream &JucarieModerna::read(istream &is) {
    Jucarie::read(is);
    cout << "Brand:";
    is >> brand;
    cout << "Model:";
    is >> model;
    return is;
}

ostream &JucarieModerna::write(ostream &os) const {
    JucarieEducativa::write(os);
    cout << ", Nr. baterii: " << nrBaterii
         << ", Brand: " << brand << ", Model: " << model;
    return os;
}

void afiseazaTipuriJucarii(){
    cout << "\n1. Jucarie clasica\n2. Jucarie educativa\n3. Jucarie electronica\n4. Jucarie moderna\n";
}



class Copil : public IoBase{
protected:
    static unsigned int staticID;
    string nume, prenume, adresa;
    unsigned int id, varsta, nrFapteBune;
    vector < shared_ptr < Jucarie > > jucariiPrimite;
public:
    Copil();

    Copil(const string &nume, const string &prenume, const string &adresa, unsigned int varsta,
          unsigned int nrFapteBune, const vector<shared_ptr<Jucarie>> &jucariiPrimite);

    const string &getNume() const;

    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;

    friend bool operator>(Copil &a, Copil &b);
};

bool verificareCopilCuminte(Copil &copil);

unsigned int Copil::staticID = 0;

Copil::Copil() : id(++staticID), varsta(0), nrFapteBune(0) {}

Copil::Copil(const string &nume, const string &prenume, const string &adresa, unsigned int varsta,
             unsigned int nrFapteBune, const vector<shared_ptr<Jucarie>> &jucariiPrimite) : id(++staticID),
                                                                                            nume(nume),
                                                                                            prenume(prenume),
                                                                                            adresa(adresa),
                                                                                            varsta(varsta),
                                                                                            nrFapteBune(nrFapteBune),
                                                                                            jucariiPrimite(jucariiPrimite) {}

bool operator>(Copil &a, Copil &b) {
    return a.nrFapteBune > b.nrFapteBune;
}

istream &Copil::read(istream &is) {
    IoBase::read(is);
    cout << "Nume:";
    getline(is, nume);
    cout << "Prenume:";
    getline(is, prenume);
    cout << "Varsta:";
    is >> varsta; is.get();
    cout << "Adresa:";
    getline(is, adresa);

    cout << "Nr. fapte bune:";
    is >> nrFapteBune;
    if (verificareCopilCuminte(*this))
        while (nrFapteBune < 10){
            cout << "Un copil cuminte trebuie sa aiba cel putin 10 fapte bune.\nNr. fapte bune:";
            is >> nrFapteBune;
        }
    is.get();

    for (int i = 1; i <= nrFapteBune; ++i){
        afiseazaTipuriJucarii();
        int tip;
        cout << i <<'/' << nrFapteBune << ". Alegeti tipul de jucarie care va fi citit (1/2/3/4):";
        shared_ptr <Jucarie> jucarieNoua;
        is >> tip;
        while (tip < 1 || tip > 4){
            cout << "Tip invalid, incercati din nou:";
            is >> tip;
        }
        if (tip == 1) {
            jucarieNoua = make_shared <JucarieClasica>();
            cout << "Se citeste o jucarie clasica...\n";
        }
        else if (tip == 2) {
            jucarieNoua = make_shared<JucarieEducativa>();
            cout << "Se citeste o jucarie educativa...\n";
        }
        else if (tip == 3) {
            jucarieNoua = make_shared<JucarieElectronica>();
            cout << "Se citeste o jucarie electronica...\n";
        }
        else if (tip == 4) {
            jucarieNoua = make_shared<JucarieModerna>();
            cout << "Se citeste o jucarie moderna...\n";
        }
        is.get();
        is >> *jucarieNoua;
        jucariiPrimite.push_back(jucarieNoua);
        cout << "Jucarie citita.\n";
    }
    if (nrFapteBune)
        cout << "S-a terminat citirea jucariilor.\n";
    return is;
}

ostream &Copil::write(ostream &os) const {
    IoBase::write(os);
    cout << "ID: " << id << ", Nume: " << nume << ", Prenume: " << prenume
         << ", Varsta: " << varsta << ", Adresa: " << adresa
         << ", Nr. fapte bune: " <<nrFapteBune;
    return os;
}

const string &Copil::getNume() const {
    return nume;
}


class CopilCuminte : public Copil{
private:
    int nrDulciuri;
public:
    CopilCuminte();

    CopilCuminte(const string &nume, const string &prenume, const string &adresa, unsigned int varsta,
                 unsigned int nrFapteBune, const vector<shared_ptr<Jucarie>> &jucariiPrimite, int nrDulciuri);

    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;
};

CopilCuminte::CopilCuminte() : nrDulciuri(0) {}

CopilCuminte::CopilCuminte(const string &nume, const string &prenume, const string &adresa, unsigned int varsta,
                           unsigned int nrFapteBune, const vector<shared_ptr<Jucarie>> &jucariiPrimite, int nrDulciuri)
        : Copil(nume, prenume, adresa, varsta, nrFapteBune, jucariiPrimite), nrDulciuri(nrDulciuri) {}

istream &CopilCuminte::read(istream &is) {
    Copil::read(is);
    cout << "Nr. dulciuri:";
    is >> nrDulciuri; is.get();
    return is;
}

ostream &CopilCuminte::write(ostream &os) const {
    Copil::write(os);
    cout << ", Nr. dulciuri: " << nrDulciuri << "\nJucarii:\n";
    int cnt = 0;
    for (auto &jucarie : jucariiPrimite)
        os << ++cnt << ". " << *jucarie << '\n';
    return os;
}

bool verificareCopilCuminte(Copil &copil){
    return dynamic_cast <CopilCuminte*> (&copil) != nullptr;
}



class CopilNeastamparat : public Copil{
private:
    int nrCarbuni;
public:
    CopilNeastamparat();

    CopilNeastamparat(const string &nume, const string &prenume, const string &adresa, unsigned int varsta,
                      unsigned int nrFapteBune, const vector<shared_ptr<Jucarie>> &jucariiPrimite, int nrCarbuni);

    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;
};

CopilNeastamparat::CopilNeastamparat() : nrCarbuni(0) {}

CopilNeastamparat::CopilNeastamparat(const string &nume, const string &prenume, const string &adresa,
                                     unsigned int varsta, unsigned int nrFapteBune,
                                     const vector<shared_ptr<Jucarie>> &jucariiPrimite, int nrCarbuni) : Copil(nume,
                                                                                                               prenume,
                                                                                                               adresa,
                                                                                                               varsta,
                                                                                                               nrFapteBune,
                                                                                                               jucariiPrimite),
                                                                                                         nrCarbuni(nrCarbuni) {}

istream &CopilNeastamparat::read(istream &is) {
    Copil::read(is);
    cout << "Nr. carbuni:";
    is >> nrCarbuni; is.get();
    return is;
}

ostream &CopilNeastamparat::write(ostream &os) const {
    Copil::write(os);
    os << ", Nr. carbuni: " << nrCarbuni << "\nJucarii:\n";
    int cnt = 0;
    for (auto &jucarie : jucariiPrimite)
        os << ++cnt << ". " << *jucarie << '\n';
    if (!nrFapteBune)
        os << "Acest copil nu primeste jucarii deoarece nu are nicio fapta buna\n";
    return os;
}





class Menu {
private:
    int n;
    vector <shared_ptr <Copil> > copii;
public:
    Menu();

    Menu(int n, const vector<shared_ptr<Copil>> &copii);

    static void listOptions();
    static int chooseOption(int first, int last);
    void mainLoop();

    void citireCopii();
    void afisareCopii();
    void cautareCopil();
    void sortareCopii();
};

Menu::Menu() : n(0) {}

Menu::Menu(int n, const vector<shared_ptr<Copil>> &copii) : n(n), copii(copii) {}


void Menu::citireCopii() {
    cout << "Numarul de copii:";
    cin >> n; cin.get();
    for (int i = 1; i <= n; ++i){
        cout << '\n' << i << "/" << n << '\n';
        cout << "1. Citeste copil cuminte.\n";
        cout << "2. Citeste copil neastamparat.\n";
        cout << "Alegere:";

        int tipCopil = 3;
        cin >> tipCopil; cin.get();
        while (tipCopil < 1 || tipCopil > 2){
            cout << "Invalid, incercati din nou:";
            cin >> tipCopil; cin.get();
        }

        shared_ptr <Copil> copilCitit;
        if (tipCopil == 1)
            copilCitit = make_shared <CopilCuminte> ();
        else if (tipCopil == 2)
            copilCitit = make_shared <CopilNeastamparat> ();

        cin >> *copilCitit;
        copii.push_back(copilCitit);
    }
}


void Menu::afisareCopii() {
    if (copii.empty())
        cout << "Nu s-au citit copii pana in acest moment.\n";
    else{
        for (auto &copil : copii)
            cout << "\n" << *copil;
    }
}


void Menu::cautareCopil() {
    cout << "Numele cautat:";
    string numeCautat;
    cin >> numeCautat;
    transform(numeCautat.begin(), numeCautat.end(), numeCautat.begin(), ::tolower);

    bool ok = false;
    for (auto &copil : copii){
        string nume = copil->getNume();
        transform(nume.begin(), nume.end(), nume.begin(), ::tolower);
        if (nume.find(numeCautat) != string::npos){
            ok = true;
            cout << '\n' << *copil;
        }
    }

    if (!ok)
        cout << "Nu s-a gasit niciun copil care sa contina " << numeCautat << " in nume.\n";
}


void Menu::sortareCopii() {
    shared_ptr <Copil> aux;
    for (int i = 0; i < copii.size() - 1; ++i)
        for (int j = i + 1; j < copii.size(); ++j)
            if (*copii[i] > *copii[j]){
                aux = copii[i];
                copii[i] = copii[j];
                copii[j] = aux;
            }

    cout << "Copiii au fost sortati.\n";
}


void Menu::listOptions() {
    cout << "1. Citeste cei n copii.\n";
    cout << "2. Afiseaza cei n copii.\n";
    cout << "3. Cauta un copil dupa nume.\n";
    cout << "4. Ordoneaza crescator copiii dupa numarul de fapte bune.\n";
    cout << "5. Iesire.\n";
}

int Menu::chooseOption(int first, int last) {
    int option = -1;
    while (option < first || option > last) {
        cout << '\n';
        listOptions();
        cout << "Alegeti un numar intre " << first << " si " << last << " pentru a efectua o operatie:";
        cin >> option; cin.get();
    }
    return option;
}

void Menu::mainLoop() {
    while (true) {
        int option = chooseOption(1, 5);
        if (option == 1) {
            citireCopii();
        } else if (option == 2) {
            afisareCopii();
        } else if (option == 3) {
            cautareCopil();
        } else if (option == 4) {
            sortareCopii();
        } else if (option == 5) {
            break;
        }
    }
    cout << "\n---------------------------------\nProgramul s-a incheiat cu succes.";
}




int main(){
    Menu meniu;
    meniu.mainLoop();
    return 0;
}