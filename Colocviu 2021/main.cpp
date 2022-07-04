// Florea Mădălin-Alexandru, grupa 143
// Compilator: Bundled MinGW, Version: w64 9.0
// Tutore de laborator: Eduard-Stefan Deaconu


#include <bits/stdc++.h>
using namespace std;


// Clasa de baza pentru citire si afisare
class InOutBase {
public:
    // citire
    virtual istream &read(istream &is) {
        return is;
    }

    friend istream &operator>>(istream &is, InOutBase &InOutBase) {
        return InOutBase.read(is);
    }


    // afisare
    virtual ostream &write(ostream &os) const {
        return os;
    }

    friend ostream &operator<<(ostream &os, const InOutBase &InOutBase) {
        return InOutBase.write(os);
    }
};





// clasa pentru a retine o data
class Data : public InOutBase {
private:
    int zi, luna, an;
public:
    Data();

    Data(int zi, int luna, int an);

    // citire
    istream &read(istream &is) override;

    // afisare
    ostream &write(ostream &os) const override;
};

Data::Data() : zi(0), luna(0), an(0) {}

Data::Data(int zi, int luna, int an) :
        zi(zi), luna(luna), an(an) {}

istream &Data::read(istream &is) {
    InOutBase::read(is);

    cout << "Zi:";
    while (true) {
        try {
            is >> zi;

            if (zi < 1 || zi > 31) {
                throw string("Zi invalida, incearca din nou:");
            } else
                break;
        }
        catch (string &error) {
            cout << error;
        }
    }

    cout << "Luna:";
    while (true) {
        try {
            is >> luna;

            if (luna < 1 || luna > 12) {
                throw string("Luna invalida, incearca din nou:");
            } else
                break;
        }
        catch (string &error) {
            cout << error;
        }
    }

    cout << "An:";
    while (true) {
        try {
            is >> an;

            if (an < 1 || an > 2022) {
                throw string("An invalid, incearca din nou:");
            } else
                break;
        }
        catch (string &error) {
            cout << error;
        }
    }

    return is;
}

ostream &Data::write(ostream &os) const {
    InOutBase::write(os);
    os << zi << "/" << luna << "/" << an;
    return os;
}





class Malware : public InOutBase {
protected:
    float ratingImpact;
    Data dataInfectare;
    string nume, metodaInfectare;
    vector <string> registriiModificati;
public:
    Malware();

    // citire
    istream &read(istream &is) override;

    // afisare
    ostream &write(ostream &os) const override;

    virtual void calculeazaRating();

    float getRatingImpact() const;
};

Malware::Malware() : ratingImpact(0), metodaInfectare("unknown") {}

istream &Malware::read(istream &is) {
    InOutBase::read(is);

    cout << "Data infectare:\n";
    is >> dataInfectare;
    is.get();

    cout << "Nume:";
    getline(is, nume);

    cout << "Se cunoaste metoda de infectare? (da / nu):";
    string ok;
    while (true) {
        try {
            getline(is, ok);
            if (ok == "da") {
                cout << "Metoda infectare:";
                getline(is, metodaInfectare);
                break;
            }
            else if (ok == "nu")
                break;
            else {
                cout << "Raspuns invalid, incearca din nou:";
            }
        }
        catch (string &error) {
            cout << error;
        }
    }

    cout << "Numar registrii modificati:";
    int n;
    is >> n; is.get();
    for (int i = 1; i <= n; ++i) {
        string registru;
        getline(is, registru);
        registriiModificati.push_back(registru);
    }

    return is;
}

ostream &Malware::write(ostream &os) const {
    InOutBase::write(os);

    os << "Nume: " << nume << ", ";
    os << "Rating impact: " << ratingImpact << ", ";
    os << "Data: " << dataInfectare << ", ";
    os << "Metoda infectare: " << metodaInfectare << "\n";

    os << "Registrii modificati: ";

    if (!registriiModificati.empty()) {
        os << registriiModificati[0];
        for (int i = 1; i < registriiModificati.size(); ++i)
            os << ", " << registriiModificati[i];
    }

    return os;
}

void Malware::calculeazaRating() {
    if (find(registriiModificati.begin(), registriiModificati.end(), "HKLM-run") != registriiModificati.end())
        ratingImpact += 20;

    if (find(registriiModificati.begin(), registriiModificati.end(), "HKCU-run") != registriiModificati.end())
        ratingImpact += 20;
}

float Malware::getRatingImpact() const {
    return ratingImpact;
}





class Rootkit : virtual public Malware {
protected:
    vector <string> importuri;
    vector <string> stringuriSemnificative;
public:
    Rootkit() = default;

    // citire
    istream &read(istream &is) override;

    // afisare
    ostream &write(ostream &os) const override;

    void calculeazaRating() override;
};


istream &Rootkit::read(istream &is){
    Malware::read(is);

    importuri.clear();
    cout << "Numar importuri:";
    int n; is >> n; is.get();
    for (int i = 1; i <= n; ++i) {
        string import;
        cout << "Importul " << i << ":";
        getline(is, import);
        importuri.push_back(import);
    }

    stringuriSemnificative.clear();
    cout << "Numar stringuri semnificative:";
    int m; is >> m; is.get();
    for (int i = 1; i <= m; ++i) {
        string s;
        cout << "Stringul " << i << ":";
        getline(is, s);
        stringuriSemnificative.push_back(s);
    }

    calculeazaRating();

    return is;
}


ostream &Rootkit::write(ostream &os) const {
    Malware::write(os);

    os << "\nImporturi: ";
    if (!importuri.empty()) {
        os << importuri[0];
        for (int i = 1; i < importuri.size(); ++i)
            os << ", " << importuri[i];
    }

    os << "\nStringuri semnificative: ";
    if (!stringuriSemnificative.empty()) {
        os << stringuriSemnificative[0];
        for (int i = 1; i < stringuriSemnificative.size(); ++i)
            os << ", " << stringuriSemnificative[i];
    }

    return os;
}

void Rootkit::calculeazaRating() {
    if (find(stringuriSemnificative.begin(), stringuriSemnificative.end(), "System Service Descriptor Table") != stringuriSemnificative.end())
        ratingImpact += 100;
    if (find(stringuriSemnificative.begin(), stringuriSemnificative.end(), "SSDT") != stringuriSemnificative.end())
        ratingImpact += 100;
    if (find(stringuriSemnificative.begin(), stringuriSemnificative.end(), "NtCreateFile") != stringuriSemnificative.end())
        ratingImpact += 100;

    if (find(importuri.begin(), importuri.end(), "ntoskrnl.exe") != importuri.end())
        ratingImpact *= 2;

    Malware::calculeazaRating();
}





class Keylogger : virtual public Malware{
protected:
    vector <string> functii;
    vector <string> taste;
public:
    Keylogger() = default;

    // citire
    istream &read(istream &is) override;

    // afisare
    ostream &write(ostream &os) const override;

    void calculeazaRating() override;
};

istream &Keylogger::read(istream &is){
    Malware::read(is);

    functii.clear();
    cout << "Numar functii:";
    int n; is >> n; is.get();
    for (int i = 1; i <= n; ++i) {
        string f;
        cout << "Functia " << i << ":";
        getline(is, f);
        functii.push_back(f);
    }

    taste.clear();
    cout << "Numar taste:";
    int m; is >> m; is.get();
    for (int i = 1; i <= m; ++i) {
        string t;
        cout << "Tasta " << i << ":";
        getline(is, t);
        taste.push_back(t);
    }

    calculeazaRating();

    return is;
}


ostream &Keylogger::write(ostream &os) const {
    Malware::write(os);

    os << "\nFunctii: ";
    if (!functii.empty()) {
        os << functii[0];
        for (int i = 1; i < functii.size(); ++i)
            os << ", " << functii[i];
    }

    os << "\nTaste: ";
    if (!taste.empty()) {
        os << taste[0];
        for (int i = 1; i < taste.size(); ++i)
            os << ", " << taste[i];
    }

    return os;
}


void Keylogger::calculeazaRating() {
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

    Malware::calculeazaRating();
}





class KernelKeylogger : public Rootkit, public Keylogger {
private:
    bool ascundeFisiere, ascundeRegistrii;
public:
    KernelKeylogger();

    // citire
    istream &read(istream &is) override;

    // afisare
    ostream &write(ostream &os) const override;

    void calculeazaRating() override;
};

KernelKeylogger::KernelKeylogger() : ascundeRegistrii(false), ascundeFisiere(false) {}

istream &KernelKeylogger::read(istream &is){
    Malware::read(is);

    importuri.clear();
    cout << "Numar importuri:";
    int n; is >> n; is.get();
    for (int i = 1; i <= n; ++i) {
        string import;
        cout << "Importul " << i << ":";
        getline(is, import);
        importuri.push_back(import);
    }

    stringuriSemnificative.clear();
    cout << "Numar stringuri semnificative:";
    int m; is >> m; is.get();
    for (int i = 1; i <= m; ++i) {
        string s;
        cout << "Stringul " << i << ":";
        getline(is, s);
        stringuriSemnificative.push_back(s);
    }

    functii.clear();
    cout << "Numar functii:";
    int p; is >> p; is.get();
    for (int i = 1; i <= p; ++i) {
        string f;
        cout << "Functia " << i << ":";
        getline(is, f);
        functii.push_back(f);
    }

    taste.clear();
    cout << "Numar taste:";
    int q; is >> q; is.get();
    for (int i = 1; i <= q; ++i) {
        string t;
        cout << "Tasta " << i << ":";
        getline(is, t);
        taste.push_back(t);
    }

    int ok;

    cout << "Ascunde fisiere? (1 - da / 0 - nu):";
    is >> ok;
    while (ok < 0 || ok > 1) {
        cout << "invalid, incearca din nou:";
        is >> ok;
    }
    if (ok == 0)
        ascundeFisiere = false;
    else
        ascundeFisiere = true;


    cout << "Ascunde registrii? (1 - da / 0 - nu):";
    is >> ok;
    while (ok < 0 || ok > 1) {
        cout << "invalid, incearca din nou:";
        is >> ok;
    }
    if (ok == 0)
        ascundeRegistrii = false;
    else
        ascundeRegistrii = true;

    is.get();

    calculeazaRating();

    return is;
}


ostream &KernelKeylogger::write(ostream &os) const {
    Malware::write(os);

    os << "\nImporturi: ";
    if (!importuri.empty()) {
        os << importuri[0];
        for (int i = 1; i < importuri.size(); ++i)
            os << ", " << importuri[i];
    }

    os << "\nStringuri semnificative: ";
    if (!stringuriSemnificative.empty()) {
        os << stringuriSemnificative[0];
        for (int i = 1; i < stringuriSemnificative.size(); ++i)
            os << ", " << stringuriSemnificative[i];
    }

    os << "\nFunctii: ";
    if (!functii.empty()) {
        os << functii[0];
        for (int i = 1; i < functii.size(); ++i)
            os << ", " << functii[i];
    }

    os << "\nTaste: ";
    if (!taste.empty()) {
        os << taste[0];
        for (int i = 1; i < taste.size(); ++i)
            os << ", " << taste[i];
    }

    if (ascundeRegistrii)
        os << "\nAscunde registrii, ";
    else
        os << "\nNu ascunde registrii, ";

    if (ascundeFisiere)
        os << "ascunde fisiere, ";
    else
        os << "nu ascunde fisiere, ";

    return os;
}


void KernelKeylogger::calculeazaRating() {
    if (find(stringuriSemnificative.begin(), stringuriSemnificative.end(), "System Service Descriptor Table") != stringuriSemnificative.end())
        ratingImpact += 100;
    if (find(stringuriSemnificative.begin(), stringuriSemnificative.end(), "SSDT") != stringuriSemnificative.end())
        ratingImpact += 100;
    if (find(stringuriSemnificative.begin(), stringuriSemnificative.end(), "NtCreateFile") != stringuriSemnificative.end())
        ratingImpact += 100;

    if (find(importuri.begin(), importuri.end(), "ntoskrnl.exe") != importuri.end())
        ratingImpact *= 2;


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

    Malware::calculeazaRating();
}





class Ransomware : public Malware{
private:
    float ratingCriptare, ratingObfscare;
public:
    Ransomware();

    // citire
    istream &read(istream &is) override;

    // afisare
    ostream &write(ostream &os) const override;

    void calculeazaRating() override;
};

Ransomware::Ransomware() : ratingCriptare(0), ratingObfscare(0) {}


istream &Ransomware::read(istream &is){
    Malware::read(is);

    cout << "Rating criptare (numar intre 1 si 10):";
    is >> ratingCriptare;

    cout << "Rating obfuscare (numar intre 0 si 100):";
    is >> ratingObfscare;

    is.get();

    calculeazaRating();

    return is;
}


ostream &Ransomware::write(ostream &os) const {
    Malware::write(os);

    os << "\nRating criptare: " << ratingCriptare
       << ", rating obfuscare: " << ratingObfscare;

    return os;
}

void Ransomware::calculeazaRating() {
    ratingImpact += ratingCriptare + ratingObfscare;

    Malware::calculeazaRating();
}






class Computer : public InOutBase {
private:
    static int staticID;
    int id;
    vector <shared_ptr <Malware> > listaMalwares;
    float ratingFinal;
public:
    Computer();

    float getRatingFinal() const;

    // citire
    istream &read(istream &is) override;

    // afisare
    ostream &write(ostream &os) const override;

    friend bool operator<(Computer &a, Computer &b);
};


bool operator<(Computer &a, Computer &b){
    return a.ratingFinal < b.ratingFinal;
}


int Computer::staticID = 0;


Computer::Computer() : id(++staticID), ratingFinal(0) {}


istream &Computer::read(istream &is){
    InOutBase::read(is);

    int n;
    cout << "\nNumarul de malwares:";
    is >> n;

    shared_ptr <Malware> malware;

    for (int i = 1; i <= n; ++i) {
        cout << "\n--- CITIRE MALWARE " << i << " ---\n";
        cout << "Tip malware (1 - Rootkit, 2 - Keylogger, 3 - KernelKeylogger, 4 - Ransomware):";
        int tip;
        is >> tip;
        while (tip < 1 || tip > 4)
            cout << "Invalid, alege un tip de la 1 la 4:";

        if (tip == 1)
            malware = make_shared<Rootkit>();
        else if (tip == 2)
            malware = make_shared<Keylogger>();
        else if (tip == 3)
            malware = make_shared<KernelKeylogger>();
        else
            malware = make_shared<Ransomware>();

        is >> *malware;

        ratingFinal += malware->getRatingImpact();

        listaMalwares.push_back(malware);
    }

    return is;
}


ostream &Computer::write(ostream &os) const {
    InOutBase::write(os);

    os << "\n\nCOMPUTER ID: " << id << ", Rating final: " << ratingFinal << ", Malwares:\n";
    int cnt = 0;
    for (auto & virus : listaMalwares) {
        os << "\n-- malware " << ++cnt << " --\n";
        os << *virus << "\n";
    }

    return os;
}

float Computer::getRatingFinal() const {
    return ratingFinal;
}


// ------------------------------ MENIU INTERACTIV ------------------------------
class Menu {
private:
    vector <Computer> computers;
public:
    Menu();

    static void listOptions();

    static int chooseOption(int first, int last);

    void mainLoop();


    void adaugaComputer();
    void afiseazaComputere();
    void afiseazaComputereOrdonate();
    void afiseazaKComputereOrdonate();
    void afiseazaProcent();
};

Menu::Menu() = default;

void Menu::listOptions() {
    cout << "1. Adauga computer.\n";
    cout << "2. Afiseaza computerele.\n";
    cout << "3. Afiseaza computerele ordonate dupa ratingul final.\n";
    cout << "4. Afiseaza primele k computere ordonate dupa ratingul final.\n";
    cout << "5. Afiseaza procentul de computere infectate.\n";
    cout << "6. Iesire.\n";

}

int Menu::chooseOption(int first, int last) {
    int option = -1;
    while (option < first || option > last) {
        cout << '\n';
        listOptions();
        cout << "Alegeti un numar intre " << first << " si " << last << " pentru a efectua o actiune:";
        cin >> option;
        cin.get();
    }
    return option;
}

void Menu::mainLoop() {
    while (true) {
        int option = chooseOption(1, 6);
        if (option == 1) {
            adaugaComputer();
        } else if (option == 2) {
            afiseazaComputere();
        } else if (option == 3) {
            afiseazaComputereOrdonate();
        } else if (option == 4) {
            afiseazaKComputereOrdonate();
        } else if (option == 5) {
            afiseazaProcent();
        } else if (option == 6) {
            break;
        }
    }
    cout << "\n---------------------------------------------\nProgram incheiat cu succes.";
}


void Menu::adaugaComputer() {
    Computer C;
    cin >> C;
    computers.push_back(C);
}


void Menu::afiseazaComputere() {
    if (computers.empty())
        cout << "\nMomentan nu exista computere adaugate.\n";
    else {
        for (auto &c : computers)
            cout << c;
    }
}


void Menu::afiseazaComputereOrdonate() {
    if (computers.empty())
        cout << "\nMomentan nu exista computere adaugate.\n";
    else {
        vector <Computer> calculatoare = computers;
        for (int i = 0; i < calculatoare.size() - 1; ++i)
            for (int j = i; j < calculatoare.size(); ++j)
                if (calculatoare[i] < calculatoare[j])
                    swap(calculatoare[i], calculatoare[j]);
        for (auto &c : calculatoare)
            cout << c;
    }
}


void Menu::afiseazaKComputereOrdonate() {
    int k;
    cout << "k=";
    cin >> k; cin.get();

    if (k > computers.size())
        cout << "\nMomentan nu exista suficiente computere adaugate.\n";
    else {
        vector <Computer> calculatoare = computers;
        for (int i = 0; i < calculatoare.size() - 1; ++i)
            for (int j = i; j < calculatoare.size(); ++j)
                if (calculatoare[i] < calculatoare[j])
                    swap(calculatoare[i], calculatoare[j]);

        for (int i = 0; i < k; ++i)
            cout << calculatoare[i];
    }
}


void Menu::afiseazaProcent() {
    float infectate = 0;
    for (auto &c : computers) {
        if (c.getRatingFinal())
            infectate++;
    }

    cout << '\n' << infectate / float(computers.size()) * 100 << "% din computere sunt infectate.\n";
}


int main() {
    Menu meniu;
    meniu.mainLoop();

    return 0;
}