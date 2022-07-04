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





// clasa pentru a retine un moment (data si ora)
class Moment : public InOutBase {
private:
    int zi, luna, an;
    int ora, minut;
public:
    Moment();

    Moment(int zi, int luna, int an, int ora, int minut);

    // citire
    istream &read(istream &is) override;

    // afisare
    ostream &write(ostream &os) const override;
};

Moment::Moment() : zi(0), luna(0), an(0), ora(0), minut(0) {}

Moment::Moment(int zi, int luna, int an, int ora, int minut) :
        zi(zi), luna(luna), an(an), ora(ora), minut(minut) {}

istream &Moment::read(istream &is) {
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

    cout << "Ora:";
    while (true) {
        try {
            is >> ora;

            if (ora < 0 || ora > 23) {
                throw string("Ora invalida, incearca din nou:");
            } else
                break;
        }
        catch (string &error) {
            cout << error;
        }
    }

    cout << "Minut:";
    while (true) {
        try {
            is >> minut;

            if (minut < 0 || minut > 59) {
                throw string("Minut invalid, incearca din nou:");
            } else
                break;
        }
        catch (string &error) {
            cout << error;
        }
    }

    return is;
}

ostream &Moment::write(ostream &os) const {
    InOutBase::write(os);
    os << zi << "/" << luna << "/" << an;
    os << ", ora " << ora << ":" << minut;
    return os;
}





class RegioII : public InOutBase {
protected:
    string statiePlecare, statieSosire;
    Moment momentPlecare;
    string codTren, serie;
    static int staticNrCrt;
    int nrCrt, durata;
    float distanta, pret;
public:
    RegioII();

    // citire
    istream &read(istream &is) override;

    // afisare
    ostream &write(ostream &os) const override;

    const string &getCodTren() const;

    const string &getSerie() const;

    float getDistanta() const;

    virtual void asociereSerie();
    virtual void calcularePret();
};

int RegioII::staticNrCrt = 0;

RegioII::RegioII() : nrCrt(++staticNrCrt), durata(0), distanta(0), pret(0) {}

istream &RegioII::read(istream &is) {
    InOutBase::read(is);

    cout << "Statie plecare:";
    getline(is, statiePlecare);

    cout << "Statie sosire:";
    getline(is, statieSosire);

    cout << "Data si ora plecarii:\n";
    is >> momentPlecare; is.get();

    cout << "Cod tren:";
    getline (is, codTren);

    cout << "Durata calatoriei:";
    is >> durata;

    cout << "Distanta parcursa:";
    is >> distanta; is.get();

    asociereSerie();
    calcularePret();

    return is;
}


ostream &RegioII::write(ostream &os) const {
    InOutBase::write(os);

    os << "Biletul " << serie;
    os << "\nStatie plecare: " << statiePlecare << ", Statie sosire: " << statieSosire;
    os << ", Moment plecare: " << momentPlecare << "\nCod tren: " << codTren;
    os << ", Durata: " << durata << ", Distanta: " << distanta << " km , Pret: " << pret << " lei";

    return os;
}


void RegioII::asociereSerie() {
    serie = "RII" + to_string(nrCrt);
}

void RegioII::calcularePret() {
    pret = 0.39 * distanta;
}

const string &RegioII::getCodTren() const {
    return codTren;
}

const string &RegioII::getSerie() const {
    return serie;
}

float RegioII::getDistanta() const {
    return distanta;
}





class RegioI : virtual public RegioII {
protected:
    string meniu;
public:
    RegioI() = default;

    // citire
    istream &read(istream &is) override;

    // afisare
    ostream &write(ostream &os) const override;

    void asociereSerie() override;
    void calcularePret() override;
};


istream &RegioI::read(istream &is) {
    RegioII::read(is);

    cout << "Meniu restaurant:";
    getline (is, meniu);

    asociereSerie();
    calcularePret();

    return is;
}


ostream &RegioI::write(ostream &os) const {
    RegioII::write(os);

    os << "\nMeniu restaurant: " << meniu;

    return os;
}


void RegioI::asociereSerie() {
    serie = "RI" + to_string(nrCrt);
}

void RegioI::calcularePret() {
    pret = 1.2 * 0.39 * distanta;
}





class InterRegioII : virtual public RegioII {
protected:
    int nrRezervat;
public:
    InterRegioII();

    // citire
    istream &read(istream &is) override;

    // afisare
    ostream &write(ostream &os) const override;

    void asociereSerie() override;
    void calcularePret() override;
};


InterRegioII::InterRegioII() : nrRezervat(0) {}


istream &InterRegioII::read(istream &is) {
    RegioII::read(is);

    cout << "Nr. loc rezervat:";
    is >> nrRezervat; is.get();

    asociereSerie();
    calcularePret();

    return is;
}


ostream &InterRegioII::write(ostream &os) const {
    RegioII::write(os);

    os << "\nNr. loc rezervat: " << nrRezervat;

    return os;
}


void InterRegioII::asociereSerie() {
    serie = "IRII" + to_string(nrCrt);
}

void InterRegioII::calcularePret() {
    pret = 0.7 * distanta;
}





class InterRegioI : public RegioI, public InterRegioII {
public:
    InterRegioI() = default;

    // citire
    istream &read(istream &is) override;

    // afisare
    ostream &write(ostream &os) const override;

    void asociereSerie() override;
    void calcularePret() override;
};


istream &InterRegioI::read(istream &is) {
    InOutBase::read(is);

    cout << "Statie plecare:";
    getline(is, statiePlecare);

    cout << "Statie sosire:";
    getline(is, statieSosire);

    cout << "Data si ora plecarii:\n";
    is >> momentPlecare; is.get();

    cout << "Cod tren:";
    getline (is, codTren);

    cout << "Durata calatoriei:";
    is >> durata;

    cout << "Distanta parcursa:";
    is >> distanta; is.get();


    cout << "Meniu restaurant:";
    getline (is, meniu);

    cout << "Nr. loc rezervat:";
    is >> nrRezervat; is.get();


    asociereSerie();
    calcularePret();

    return is;
}


ostream &InterRegioI::write(ostream &os) const {
    InOutBase::write(os);

    os << "Biletul " << serie;
    os << "\nStatie plecare: " << statiePlecare << ", Statie sosire: " << statieSosire;
    os << ", Moment plecare: " << momentPlecare << "\nCod tren: " << codTren;
    os << ", Durata: " << durata << ", Distanta: " << distanta << " km , Pret: " << pret << " lei";

    os << "\nMeniu restaurant: " << meniu << ", Nr. loc rezervat: " << nrRezervat;

    return os;
}


void InterRegioI::asociereSerie() {
    serie = "IRI" + to_string(nrCrt);
}

void InterRegioI::calcularePret() {
    pret = 1.2 * 0.7 * distanta;
}


// ------------------------------ MENIU INTERACTIV ------------------------------
class Menu {
private:
    vector <shared_ptr <RegioII> > bilete;
public:
    Menu();

    static void listOptions();

    static int chooseOption(int first, int last);

    void mainLoop();

    void elibereazaBilet();
    void listeazaBileteTren();
    void listeazaBileteDistanta();
    void anuleazaBilet();
};

Menu::Menu() = default;

void Menu::listOptions() {
    cout << "1. Eliberarea unui nou bilet.\n";
    cout << "2. Listarea biletelor pentru un anumit tren.\n";
    cout << "3. Listarea biletelor pentru calatorii mai lungi decat o anumita distanta.\n";
    cout << "4. Anularea unui bilet folosind seria acestuia.\n";
    cout << "5. Iesire.\n";

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
        int option = chooseOption(1, 5);
        if (option == 1) {
            elibereazaBilet();
        } else if (option == 2) {
            listeazaBileteTren();
        } else if (option == 3) {
            listeazaBileteDistanta();
        } else if (option == 4) {
            anuleazaBilet();
        } else if (option == 5) {
            break;
        }
    }
    cout << "\n---------------------------------------------\nProgram incheiat cu succes.";
}


void Menu::elibereazaBilet() {
    shared_ptr <RegioII> bilet;

    string tip;
    int clasa;

    cout << "\nAlegeti tipul biletului (IR sau R):";
    getline(cin, tip);
    while (tip != "IR" && tip != "R"){
        cout << "Tip invalid, incearca din nou:";
        getline(cin, tip);
    }

    cout << "Alegeti clasa biletului (1 sau 2):";
    cin >> clasa;
    while (clasa != 1 && clasa != 2) {
        cout << "Clasa invalida, incearca din nou:";
        cin >> clasa;
    }
    cin.get();

    if (tip == "R" && clasa == 1)
        bilet = make_shared <RegioI>();
    else if (tip == "R" && clasa == 2)
        bilet = make_shared <RegioII>();
    else if (tip == "IR" && clasa == 1)
        bilet = make_shared <InterRegioI>();
    else if (tip == "IR" && clasa == 2)
        bilet = make_shared <InterRegioII>();

    cin >> *bilet;
    bilete.push_back(bilet);
}


void Menu::listeazaBileteTren() {
    cout << "Cod tren:";
    string cod;
    getline(cin, cod);

    int cnt = 0;
    for (auto &bilet : bilete){
        if (cod == bilet->getCodTren()) {
            cnt++;
            cout << '\n' << *bilet << '\n';
        }
    }

    if (cnt == 0) {
        cout << "\nNu exista bilete emise pentru acest tren.\n";
    }
}


void Menu::listeazaBileteDistanta() {
    cout << "Distanta minima:";
    int d;
    cin >> d;
    while (d < 0) {
        cout << "Distanta invalida, incearca din nou:";
        cin >> d;
    }
    cin.get();

    int cnt = 0;
    for (auto &bilet : bilete) {
        if (bilet->getDistanta() > d) {
            cnt ++;
            cout << '\n' << *bilet << '\n';
        }
    }

    if (cnt == 0)
        cout << "\nNu exista trenuri cu distanta mai mare ca cea data.\n";
}


void Menu::anuleazaBilet() {
    cout << "Serie bilet:";
    string serie;
    getline(cin, serie);

    int cnt = 0;
    for (int i = 0; i < bilete.size(); ++i) {
        if (bilete[i]->getSerie() == serie) {
            cnt ++;
            bilete.erase(bilete.begin() + i);
            cout << "\nBilet sters.\n";
            break;
        }
    }

    if (cnt == 0)
        cout << "\nNu exista biletul cu aceasta serie.\n";
}



int main() {
    Menu meniu;
    meniu.mainLoop();

    return 0;
}