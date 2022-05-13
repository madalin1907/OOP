// Florea Mădălin-Alexandru
// Grupa 143
// Rulat pe CLion, compilator g++.exe
// Tutore de laborator: Deaconu Ștefan

#include <bits/stdc++.h>
#include "IoBase.h"
using namespace std;





//Clasa pentru a retine o data din an
class Data : public IoBase{
private:
    int zi, luna, an;
public:
    Data();

    Data(int zi, int luna, int an);

    // metoda citire
    istream &read(istream &is) override;

    // metoda scriere
    ostream &write(ostream &os) const override;
};

Data::Data() : zi(0), luna(0), an(0) {}

Data::Data(int zi, int luna, int an) : zi(zi), luna(luna), an(an) {}

istream &Data::read(istream &is) {
    IoBase::read(is);
    cout << "zi:"; is >> zi;
    cout << "luna:"; is >> luna;
    cout << "an:"; is >> an;
    return is;
}

ostream &Data::write(ostream &os) const {
    IoBase::write(os);
    os << zi << "/" << luna << "/" << an;
    return os;
}





//Prin malware înțelegem un software rău intenționat pentru care se reține ratingul
//impactului (număr real), data de infectare (zi, luna, an), numele acestuia (care
//poate să fie format din mai multe cuvinte), metoda de infectare (dacă se cunoaște,altfel
//se reține șirul “unknown”) și un vector cu registrii modificați (reținuți ca stringuri).

class Malware : public IoBase{
protected:
    double ratingImpact;
    Data data;
    string nume, metodaInfectare;
    vector <string > registriiModificati;
public:
    virtual void calculeaza();

    Malware();

    Malware(const Data &data, const string &nume, const string &metodaInfectare,
            const vector<string> &registriiModificati);

    double getRatingImpact() const;

    // metoda citire
    istream &read(istream &is) override;

    // metoda scriere
    ostream &write(ostream &os) const override;
};


// Se adauga la final, separat de rating-ul caracteristic fiecarui malware
void Malware::calculeaza() {
    if (find(registriiModificati.begin(), registriiModificati.end(), "HKLM-run") != registriiModificati.end())
        ratingImpact += 20;
    if (find(registriiModificati.begin(), registriiModificati.end(), "HKCU-run") != registriiModificati.end())
        ratingImpact += 20;
}


Malware::Malware() : ratingImpact(0) {}

Malware::Malware(const Data &data, const string &nume, const string &metodaInfectare,
                 const vector<string> &registriiModificati) : ratingImpact(0), data(data), nume(nume),
                                                              metodaInfectare(metodaInfectare),
                                                              registriiModificati(registriiModificati) {}


istream &Malware::read(istream &is) {
    IoBase::read(is);

    cout << "Data:\n";
    is >> data; is.get();
    cout << "Nume:";
    getline(is, nume);
    cout << "Metoda infectare:";
    getline(is, metodaInfectare);

    registriiModificati.clear();
    cout << "Nr. registrii:";
    int n; is >> n; is.get();

    for (int i = 1; i <= n; ++i) {
        cout << "Registrul " << i << ":";
        string registru;
        getline(is, registru);
        registriiModificati.push_back(registru);
    }

    return is;
}

ostream &Malware::write(ostream &os) const {
    IoBase::write(os);

    os << "Rating impact: " << ratingImpact << ", Nume: " << nume << ", Metoda infectare: " << metodaInfectare;

    os << "\nRegistrii infectati: ";

    for (int i = 0; i < registriiModificati.size()-1; ++i)
        os << registriiModificati[i] << ", ";
    os << registriiModificati[registriiModificati.size()-1];

    os << '\n';
    return os;
}

double Malware::getRatingImpact() const {
    return ratingImpact;
}





//Prin rootkit înțelegem un tip de malware ce are drept scop obținerea drepturilor de administrator
//asupra dispozitivului infectat. Pentru rootkit se reține lista importurilor care poate fi unul și
//oricât de multe (importurile fac referire la numele fișierelor .dll folosite) și o listă de
//stringuri semnificative (anumite stringuri dintr-un binar pot fi un indice asupra faptului
//că fișierul este rău intenționat).

class Rootkit : virtual public Malware{
protected:
    vector <string> importuri;
    vector <string> stringuriSemnificative;
public:
    void calculeaza() override;

    Rootkit();

    Rootkit(const Data &data, const string &nume, const string &metodaInfectare,
            const vector<string> &registriiModificati, const vector<string> &importuri,
            const vector<string> &stringuriSemnificative);

    // metoda citire
    istream &read(istream &is) override;

    // metoda scriere
    ostream &write(ostream &os) const override;
};

void Rootkit::calculeaza() {
    if (find(stringuriSemnificative.begin(), stringuriSemnificative.end(), "System Service Descriptor Table") != stringuriSemnificative.end())
        ratingImpact += 100;
    if (find(stringuriSemnificative.begin(), stringuriSemnificative.end(), "SSDT") != stringuriSemnificative.end())
        ratingImpact += 100;
    if (find(stringuriSemnificative.begin(), stringuriSemnificative.end(), "NtCreateFile") != stringuriSemnificative.end())
        ratingImpact += 100;
    if (find(importuri.begin(), importuri.end(), "ntoskrnl.exe") != importuri.end())
        ratingImpact *= 2;

    Malware::calculeaza();
}

Rootkit::Rootkit() = default;

Rootkit::Rootkit(const Data &data, const string &nume, const string &metodaInfectare,
                 const vector<string> &registriiModificati, const vector<string> &importuri,
                 const vector<string> &stringuriSemnificative) : Malware(data, nume, metodaInfectare,
                                                                         registriiModificati), importuri(importuri),
                                                                 stringuriSemnificative(stringuriSemnificative) {}

istream &Rootkit::read(istream &is) {
    Malware::read(is);

    importuri.clear();
    cout << "Nr. Importuri:";
    int n; is >> n; is.get();

    for (int i = 1; i <= n; ++i){
        string import;
        cout << "Import " << i << ":";
        getline(is, import);
        importuri.push_back(import);
    }

    stringuriSemnificative.clear();
    cout << "Nr. stringuri semnificative:";
    is >> n; is.get();

    for (int i = 1; i <= n; ++i){
        string s;
        cout << "String " << i << ":";
        getline(is, s);
        stringuriSemnificative.push_back(s);
    }

    calculeaza();
    return is;
}

ostream &Rootkit::write(ostream &os) const {
    Malware::write(os);
    os << "Importuri: ";
    for (int i = 0; i < importuri.size()-1; ++i)
        os << importuri[i] << ", ";
    os << importuri[importuri.size()-1];

    os << "\nStringuri semnificative: ";
    for (int i = 0; i < stringuriSemnificative.size()-1; ++i)
        os << stringuriSemnificative[i] << ", ";
    os << stringuriSemnificative[stringuriSemnificative.size()-1];

    os << '\n';
    return os;
}





//Prin keylogger înțelegem un malware care înregistrează acțiunile de la tastatură și le
//trimite mai departe. Pentru un keylogger se reține o listă cu funcțiile folosite
//și o listă cu tastele speciale definite.

class Keylogger : virtual public Malware{
protected:
    vector <string> functii;
    vector <string> taste;
public:
    void calculeaza() override;

    Keylogger();

    Keylogger(const Data &data, const string &nume, const string &metodaInfectare,
              const vector<string> &registriiModificati, const vector<string> &functii, const vector<string> &taste);

    // metoda citire
    istream &read(istream &is) override;

    // metoda scriere
    ostream &write(ostream &os) const override;
};

void Keylogger::calculeaza() {
    if (find(taste.begin(), taste.end(), "[Up]") != taste.end())
        ratingImpact += 10;
    if (find(taste.begin(), taste.end(), "[Num Lock]") != taste.end())
        ratingImpact += 10;
    if (find(taste.begin(), taste.end(), "[Down]") != taste.end())
        ratingImpact += 10;
    if (find(taste.begin(), taste.end(), "[Right]") != taste.end())
        ratingImpact += 10;
    if (find(taste.begin(), taste.end(), "[UP]") != taste.end())
        ratingImpact += 10;
    if (find(taste.begin(), taste.end(), "[Left]") != taste.end())
        ratingImpact += 10;
    if (find(taste.begin(), taste.end(), "[PageDown]") != taste.end())
        ratingImpact += 10;

    if (find(functii.begin(), functii.end(), "CreateFileW") != functii.end())
        ratingImpact += 30;
    if (find(functii.begin(), functii.end(), "OpenProcess") != functii.end())
        ratingImpact += 30;
    if (find(functii.begin(), functii.end(), "ReadFile") != functii.end())
        ratingImpact += 30;
    if (find(functii.begin(), functii.end(), "WriteFile") != functii.end())
        ratingImpact += 30;
    if (find(functii.begin(), functii.end(), "RegisterHotKey") != functii.end())
        ratingImpact += 30;
    if (find(functii.begin(), functii.end(), "SetWindowsHookEx") != functii.end())
        ratingImpact += 30;

    Malware::calculeaza();
}


Keylogger::Keylogger() = default;

Keylogger::Keylogger(const Data &data, const string &nume, const string &metodaInfectare,
                     const vector<string> &registriiModificati, const vector<string> &functii,
                     const vector<string> &taste) : Malware(data, nume, metodaInfectare,
                                                            registriiModificati), functii(functii), taste(taste) {}


istream &Keylogger::read(istream &is) {
    Malware::read(is);
    cout << "Nr. functii:";
    functii.clear();

    int n;
    is >> n; is.get();
    for (int i = 1; i <= n; ++i){
        string fct;
        cout << "Functia " << i << ":";
        getline(is, fct);
        functii.push_back(fct);
    }

    cout << "Nr. taste:";
    taste.clear();

    is >> n; is.get();
    for (int i = 1; i <= n; ++i){
        string t;
        cout << "Tasta " << i << ":";
        getline(is, t);
        taste.push_back(t);
    }

    calculeaza();

    return is;
}

ostream &Keylogger::write(ostream &os) const {
    Malware::write(os);

    os << "Functii: ";
    for (int i = 0; i < functii.size()-1; ++i)
        os << functii[i] << ", ";
    os << functii[functii.size()-1];

    os << "\nTaste: ";
    for (int i = 0; i < taste.size()-1; ++i)
        os << taste[i] << ", ";
    os << taste[taste.size()-1];

    os << '\n';
    return os;
}





//Prin kernel-keylogger înțelegem un keylogger ce rulează în kernel-mode (de obicei
//prin intermediul unui rootkit). Prin urmare, putem considera că este are atât
//proprietățile unui rootkit cât și ale unui keylogger. În plus, dorim să memorăm dacă
//ascunde fișiere și registrii.

class KernelKeylogger : public Rootkit, public Keylogger{
private:
    bool ascundeFisiere, ascundeRegistrii;
public:
    void calculeaza() override;

    KernelKeylogger();

    KernelKeylogger(const Data &data, const string &nume, const string &metodaInfectare,
            const vector<string> &registriiModificati, const vector<string> &importuri,
            const vector<string> &stringuriSemnificative, vector <string> &functii,  vector <string> &taste,
                    bool ascundeFisiere, bool ascundeRegistrii);

    // metoda citire
    istream &read(istream &is) override;

    // metoda scriere
    ostream &write(ostream &os) const override;
};


void KernelKeylogger::calculeaza() {
    // calculeaza doar ceea ce tine de partea de Rootkit
    if (find(stringuriSemnificative.begin(), stringuriSemnificative.end(), "System Service Descriptor Table") != stringuriSemnificative.end())
        ratingImpact += 100;
    if (find(stringuriSemnificative.begin(), stringuriSemnificative.end(), "SSDT") != stringuriSemnificative.end())
        ratingImpact += 100;
    if (find(stringuriSemnificative.begin(), stringuriSemnificative.end(), "NtCreateFile") != stringuriSemnificative.end())
        ratingImpact += 100;
    if (find(importuri.begin(), importuri.end(), "ntoskrnl.exe") != importuri.end())
        ratingImpact *= 2;


    // calculeaza doar ceea ce tine de partea de Keylogger
    if (find(taste.begin(), taste.end(), "[Up]") != taste.end())
        ratingImpact += 10;
    if (find(taste.begin(), taste.end(), "[Num Lock]") != taste.end())
        ratingImpact += 10;
    if (find(taste.begin(), taste.end(), "[Down]") != taste.end())
        ratingImpact += 10;
    if (find(taste.begin(), taste.end(), "[Right]") != taste.end())
        ratingImpact += 10;
    if (find(taste.begin(), taste.end(), "[UP]") != taste.end())
        ratingImpact += 10;
    if (find(taste.begin(), taste.end(), "[Left]") != taste.end())
        ratingImpact += 10;
    if (find(taste.begin(), taste.end(), "[PageDown]") != taste.end())
        ratingImpact += 10;

    if (find(functii.begin(), functii.end(), "CreateFileW") != functii.end())
        ratingImpact += 30;
    if (find(functii.begin(), functii.end(), "OpenProcess") != functii.end())
        ratingImpact += 30;
    if (find(functii.begin(), functii.end(), "ReadFile") != functii.end())
        ratingImpact += 30;
    if (find(functii.begin(), functii.end(), "WriteFile") != functii.end())
        ratingImpact += 30;
    if (find(functii.begin(), functii.end(), "RegisterHotKey") != functii.end())
        ratingImpact += 30;
    if (find(functii.begin(), functii.end(), "SetWindowsHookEx") != functii.end())
        ratingImpact += 30;


    //calculeaza partea comuna de Malware
    Malware::calculeaza();

    //calculeaza ceea ce apartine strict de KernelKeylogger
    if (ascundeFisiere)
        ratingImpact += 20;
    if (ascundeRegistrii)
        ratingImpact += 30;
}


KernelKeylogger::KernelKeylogger() : ascundeFisiere(false), ascundeRegistrii(false) {}

KernelKeylogger::KernelKeylogger(const Data &data, const string &nume,
                                 const string &metodaInfectare, const vector<string> &registriiModificati,
                                 const vector<string> &importuri, const vector<string> &stringuriSemnificative,
                                 vector<string> &functii, vector<string> &taste, bool ascundeFisiere, bool ascundeRegistrii) : Rootkit(data, nume, metodaInfectare,
                                                                                           registriiModificati, importuri, stringuriSemnificative),
                                                                                   Keylogger(data, nume, metodaInfectare,
                                                                                           registriiModificati, functii, taste), ascundeFisiere(ascundeFisiere), ascundeRegistrii(ascundeRegistrii) {}


istream &KernelKeylogger::read(istream &is) {
    Malware::read(is);

    importuri.clear();
    cout << "Nr. Importuri:";
    int n; is >> n; is.get();

    for (int i = 1; i <= n; ++i){
        string import;
        cout << "Import " << i << ":";
        getline(is, import);
        importuri.push_back(import);
    }

    stringuriSemnificative.clear();
    cout << "Nr. stringuri semnificative:";
    is >> n; is.get();

    for (int i = 1; i <= n; ++i){
        string s;
        cout << "String " << i << ":";
        getline(is, s);
        stringuriSemnificative.push_back(s);
    }

    cout << "Nr. functii:";
    functii.clear();


    is >> n; is.get();
    for (int i = 1; i <= n; ++i){
        string fct;
        cout << "Functia " << i << ":";
        getline(is, fct);
        functii.push_back(fct);
    }

    cout << "Nr. taste:";
    taste.clear();

    is >> n; is.get();
    for (int i = 1; i <= n; ++i){
        string t;
        cout << "Tasta " << i << ":";
        getline(is, t);
        taste.push_back(t);
    }

    cout << "Ascunde fisiere? (1 - DA, 0 - NU):";
    is >> ascundeFisiere;
    cout << "Ascunde registrii? (1 - DA, 0 - NU):";
    is >> ascundeRegistrii;

    calculeaza();
    return is;
}

ostream &KernelKeylogger::write(ostream &os) const {
    Rootkit::write(os);

    os << "Functii: ";
    for (int i = 0; i < functii.size()-1; ++i)
        os << functii[i] << ", ";
    os << functii[functii.size()-1];

    os << "\nTaste: ";
    for (int i = 0; i < taste.size()-1; ++i)
        os << taste[i] << ", ";
    os << taste[taste.size()-1];

    os << '\n';

    if (ascundeFisiere)
        os << "Ascunde fisiere. ";
    else
        os << "Nu ascunde fisiere. ";

    if (ascundeRegistrii)
        os << "Ascunde registrii.\n";
    else
        os << "Nu ascunde registrii.\n";

    return os;
}





//Prin ransomware înțelegem un malware care criptează fișiere de pe disk. Pentru acesta
//se reține ratingul de criptare (un număr de la 1 la 10) și un rating de obfuscare
//(un număr real ce reprezintă procentul de obfuscare (obfuscare = metodă de a
//ascunde/îngreuna intenția inițială a codului)).

class Ransomware : public Malware{
private:
    unsigned int ratingCriptare;
    double ratingObfuscare;
public:
    void calculeaza() override;

    Ransomware();

    Ransomware(const Data &data, const string &nume, const string &metodaInfectare,
               const vector<string> &registriiModificati, unsigned int ratingCriptare, double ratingObfuscare);

    // metoda citire
    istream &read(istream &is) override;

    // metoda scriere
    ostream &write(ostream &os) const override;
};

void Ransomware::calculeaza() {
    ratingImpact += ratingObfuscare;
    ratingImpact += ratingCriptare;

    Malware::calculeaza();
}

Ransomware::Ransomware() : ratingCriptare(0), ratingObfuscare(0) {}

Ransomware::Ransomware(const Data &data, const string &nume, const string &metodaInfectare,
                       const vector<string> &registriiModificati, unsigned int ratingCriptare, double ratingObfuscare)
        : Malware(data, nume, metodaInfectare, registriiModificati), ratingCriptare(ratingCriptare),
          ratingObfuscare(ratingObfuscare) {
}

istream &Ransomware::read(istream &is) {
    Malware::read(is);

    cout << "Rating criptare:";
    is >> ratingCriptare;
    cout << "Rating obfuscare:";
    is >> ratingObfuscare;
    is.get();

    calculeaza();
    return is;
}

ostream &Ransomware::write(ostream &os) const {
    Malware::write(os);

    os << "Rating criptare: " << ratingCriptare;
    os << ", Rating obfuscare:" << ratingObfuscare;

    os << '\n';
    return os;
}





class Computer : public IoBase{
private:
    static unsigned int staticID;
    unsigned int id;
    vector <shared_ptr <Malware> > malwareList;
    double ratingTotal;
public:
    void calculeaza();

    Computer();

    explicit Computer(const vector<shared_ptr<Malware>> &malwareList);

    double getRatingTotal() const;

    // metoda citire
    istream &read(istream &is) override;

    // metoda scriere
    ostream &write(ostream &os) const override;

    friend bool operator<(Computer &a, Computer &b);
};

unsigned int Computer::staticID = 0;

Computer::Computer() : id(++staticID), ratingTotal(0){}

Computer::Computer(const vector<shared_ptr<Malware>> &malwareList) : id(++staticID), malwareList(malwareList), ratingTotal(0) {}

istream &Computer::read(istream &is) {
    IoBase::read(is);
    cout << "Nr. tipuri de malware:";
    int m; is >> m; is.get();

    for (int i = 1; i <= m; ++i){
        cout << "\nCitire malware " << i << ":\n";

        cout << "Tip malware (1 - Rootkit, 2 - Keylogger, 3 - KernelKeylogger, 4 - Ransomware):";
        int tip = 0; is >> tip;
        while (tip < 1 || tip > 4){
            cout << "Tip malware invalid, incearca din nou:";
            is >> tip;
        }
        is.get();

        shared_ptr <Malware> virus;
        if (tip == 1)
            virus = make_shared<Rootkit>();
        else if (tip == 2)
            virus = make_shared<Keylogger>();
        else if (tip == 3)
            virus = make_shared<KernelKeylogger>();
        else if (tip == 4)
            virus = make_shared<Ransomware>();

        is >> *virus;
        malwareList.push_back(virus);
    }

    calculeaza();
    return is;
}

ostream &Computer::write(ostream &os) const {
    os << "Computer ID: " << id << ", Rating total: " << ratingTotal << ", Malwares:\n";
    int cnt = 0;
    for (auto &malware : malwareList)
        os << "--------Malware " << ++cnt << "--------\n" << *malware;

    return os;
}

void Computer::calculeaza() {
    for (auto &malware : malwareList){
        ratingTotal += malware->getRatingImpact();
    }
}

bool operator<(Computer &a, Computer &b) {
    return a.ratingTotal < b.ratingTotal;
}

double Computer::getRatingTotal() const {
    return ratingTotal;
}





// --------------------------- MENIU INTERACTIV ---------------------------
class Menu {
private:
    vector <Computer> calculatoare;
public:
    Menu();

    explicit Menu(const vector<Computer> &calculatoare);

    static void listOptions();
    static int chooseOption(int first, int last);
    void mainLoop();

    void citireCalculatoare();
    void afisareCalculatoare();
    void afisareCalculatoareSortate();
    void afisarekCalculatoareSortate();
    void procentComputereInfectate();
};

Menu::Menu() = default;

Menu::Menu(const vector<Computer> &calculatoare) : calculatoare(calculatoare) {}

void Menu::listOptions() {
    cout << "1. Citeste calculatoare.\n";
    cout << "2. Afiseaza calculatoarele.\n";
    cout << "3. Afiseaza calculatoarele ordonate dupa ratingul final.\n";
    cout << "4. Afiseaza primele k calculatoare ordonate dupa ratingul final.\n";
    cout << "5. Afiseaza procentul de calculatoare infectate din firma.\n";
    cout << "6. Iesire.\n";
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
        int option = chooseOption(1, 6);
        if (option == 1) {
            citireCalculatoare();
        } else if (option == 2) {
            afisareCalculatoare();
        } else if (option == 3) {
            afisareCalculatoareSortate();
        } else if (option == 4) {
            afisarekCalculatoareSortate();
        } else if (option == 5) {
            procentComputereInfectate();
        } else if (option == 6) {
            break;
        }
    }
    cout << "\n---------------------------------\nProgramul s-a incheiat cu succes.";
}

void Menu::citireCalculatoare() {
    cout << "\nNumarul de calculatoare:";
    int n; cin >> n; cin.get();
    for (int i = 1; i <= n; ++i){
        cout << "\nCitire calculator " << i <<":\n";
        Computer c;
        cin >> c;
        calculatoare.push_back(c);
    }
}

void Menu::afisareCalculatoare() {
    if (calculatoare.empty())
        cout << "\nNu s-au introdus calculatoare momentan\n";
    else {
        for (auto &calculator: calculatoare)
            cout << '\n' << calculator;
    }
}

void Menu::afisareCalculatoareSortate() {
    if (calculatoare.empty())
        cout << "\nNu s-au introdus calculatoare momentan.\n";
    else {
        vector<Computer> computers = calculatoare;

        for (int i = 0; i < computers.size() - 1; ++i)
            for (int j = i + 1; j < computers.size(); ++j)
                if (computers[i] < computers[j])
                    swap(computers[i], computers[j]);
        for (auto &c : computers)
            cout << '\n' << c;
    }
}

void Menu::afisarekCalculatoareSortate() {
    if (calculatoare.empty())
        cout << "\nNu s-au introdus calculatoare momentan.\n";
    else {
        cout << "\nk=";
        int k;
        cin >> k;
        while (k <= 0 || k > calculatoare.size()) {
            cout << "k trebuie sa fie pozitiv si mai mic sau egal decat numarul de calculatoare(" << calculatoare.size() << ")\nk=";
            cin >> k;
        }
        vector<Computer> computers = calculatoare;

        for (int i = 0; i < computers.size() - 1; ++i)
            for (int j = i + 1; j < computers.size(); ++j)
                if (computers[i] < computers[j])
                    swap(computers[i], computers[j]);
        for (int i = 0; i < k; ++i)
            cout << '\n' << computers[i];
    }
}

void Menu::procentComputereInfectate() {
    if (calculatoare.empty())
        cout << "\nNu s-au introdus calculatoare momentan.\n";
    else {
        int computereInfectateCNT = 0;
        int totalComputere = calculatoare.size();

        for (int i = 0; i < totalComputere; ++i)
            if (calculatoare[i].getRatingTotal() != 0)
                computereInfectateCNT++;

        double procent = double(computereInfectateCNT) / totalComputere * 100;
        cout << fixed << setprecision(2) << procent << "% din calculatoarele firmei sunt infectate.\n";
    }
}



int main(){
    Menu meniu;
    meniu.mainLoop();
    return 0;
}