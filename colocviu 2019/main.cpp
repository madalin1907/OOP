//Florea Mădălin-Alexandru, grupa 143
//Compilator: Bundled MinGW, Version: w64 9.0
//Tutore de laborator: Eduard-Stefan Deaconu

#include <bits/stdc++.h>
using namespace std;


class InOutBase{
public:
    // citire
    virtual istream &read(istream &is) {
        return is;
    }
    friend ostream &operator<<(ostream &os, const InOutBase &InOutBase) {
        return InOutBase.write(os);
    }

    // afisare
    virtual ostream &write(ostream &os) const {
        return os;
    }
    friend istream &operator>>(istream &is, InOutBase &InOutBase) {
        return InOutBase.read(is);
    }
};





// clasa pentru a retine data, ora si minutul plecarii
class Moment : public InOutBase{
private:
    int zi, luna, an, ora, minut;
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
    cout << "zi:"; is >> zi;
    cout << "luna:"; is >> luna;
    cout << "an:"; is >> an;
    cout << "ora:"; is >> ora;
    cout << "minut:"; is >> minut;
    return is;
}

ostream &Moment::write(ostream &os) const {
    InOutBase::write(os);
    os << zi << "/" << luna << "/" << an << ", ora " << ora << ":" << minut;
    return os;
}





class RegioII : public InOutBase{
protected:
    string statiePlecare, statieSosire;
    Moment plecare;
    string codTren;
    int durataCalatorie, distantaParcursa;

    string serieBilet;
    double pret;
    static int staticNrOrd;
    int nrOrd;
public:
    RegioII();

    RegioII(string &statiePlecare, string &statieSosire, Moment &plecare, string &codTren, int durataCalatorie, int distantaParcursa);

    string &getCodTren();

    int &getDistanta();

    string &getSerie();

    // citire
    istream &read(istream &is) override;

    // afisare
    ostream &write(ostream &os) const override;

    virtual void asociereSerie();

    virtual void calcularePret();
};

int RegioII::staticNrOrd = 0;


RegioII::RegioII() : nrOrd(++staticNrOrd), durataCalatorie(0), distantaParcursa(0), pret(0){}

RegioII::RegioII(string &statiePlecare, string &statieSosire, Moment &plecare, string &codTren, int durataCalatorie, int distantaParcursa) :
        statiePlecare(statiePlecare), statieSosire(statieSosire), plecare(plecare), codTren(codTren), durataCalatorie(durataCalatorie),
        distantaParcursa(distantaParcursa), pret(0), nrOrd(++staticNrOrd) {}


istream &RegioII::read(istream &is) {
    InOutBase::read(is);
    cout << "Statie plecare:";
    getline(is, statiePlecare);

    cout << "Statie sosire:";
    getline(is, statieSosire);

    cout << "Moment plecare:\n";
    is >> plecare;
    is.get();

    cout << "Cod tren:";
    getline(is, codTren);

    cout << "Durata calatoriei:";
    is >> durataCalatorie;

    cout << "Distanta parcursa:";
    is >> distantaParcursa;
    is.get();

    asociereSerie();
    calcularePret();

    return is;
}

ostream &RegioII::write(ostream &os) const {
    InOutBase::write(os);

    os << "Statie plecare: " << statiePlecare;
    os << ", Statie sosire: " << statieSosire;
    os << ", Moment plecare: " << plecare;
    os << ", Cod tren: " << codTren;
    os << ", Durata calatoriei: " << durataCalatorie;
    os << "min, Distanta parcursa: " << distantaParcursa << "km";
    os << ", Serie bilet: " << serieBilet;
    os << ", Pret: " << pret << "lei";

    return os;
}

void RegioII::asociereSerie() {
    serieBilet = "RII-" + to_string(nrOrd);
}

void RegioII::calcularePret() {
    pret = distantaParcursa * 0.39;
}

string &RegioII::getCodTren() {
    return codTren;
}

int &RegioII::getDistanta() {
    return distantaParcursa;
}

string &RegioII::getSerie(){
    return serieBilet;
}





class RegioI : virtual public RegioII{
protected:
    string meniuRestaurant;
public:
    RegioI();

    RegioI(string &statiePlecare, string &statieSosire, Moment &plecare, string &codTren, int durataCalatorie, int distantaParcursa, string &meniuRestaurant);


    // citire
    istream &read(istream &is) override;

    // afisare
    ostream &write(ostream &os) const override;


    void asociereSerie() override;

    void calcularePret() override;
};

RegioI::RegioI(string &statiePlecare, string &statieSosire, Moment &plecare, string &codTren, int durataCalatorie, int distantaParcursa, string &meniuRestaurant) :
        RegioII(statiePlecare, statieSosire, plecare, codTren, durataCalatorie, distantaParcursa), meniuRestaurant(meniuRestaurant) {}

RegioI::RegioI() = default;


istream &RegioI::read(istream &is) {
    cout << "Statie plecare:";
    getline(is, statiePlecare);

    cout << "Statie sosire:";
    getline(is, statieSosire);

    cout << "Moment plecare:\n";
    is >> plecare;
    is.get();

    cout << "Cod tren:";
    getline(is, codTren);

    cout << "Durata calatoriei:";
    is >> durataCalatorie;

    cout << "Distanta parcursa:";
    is >> distantaParcursa;
    is.get();

    cout << "Meniu restaurant:";
    getline(is, meniuRestaurant);


    asociereSerie();
    calcularePret();

    return is;
}

ostream &RegioI::write(ostream &os) const {
    RegioII::write(os);

    os << ", Meniu restaurant: " << meniuRestaurant;

    return os;
}


void RegioI::asociereSerie() {
    serieBilet = "RI-" + to_string(nrOrd);
}

void RegioI::calcularePret() {
    pret = distantaParcursa * 0.39 * 1.2;
}





class InterRegioII : virtual public RegioII{
protected:
    int nrLocRezervat;
public:
    InterRegioII();

    InterRegioII(string &statiePlecare, string &statieSosire, Moment &plecare, string &codTren, int durataCalatorie, int distantaParcursa, int nrLocRezervat);


    // citire
    istream &read(istream &is) override;

    // afisare
    ostream &write(ostream &os) const override;


    void asociereSerie() override;

    void calcularePret() override;
};


InterRegioII::InterRegioII() : nrLocRezervat(0) {}

InterRegioII::InterRegioII(string &statiePlecare, string &statieSosire, Moment &plecare, string &codTren, int durataCalatorie, int distantaParcursa, int nrLocRezervat) :
        RegioII(statiePlecare, statieSosire, plecare, codTren, durataCalatorie, distantaParcursa), nrLocRezervat(nrLocRezervat) {}


istream &InterRegioII::read(istream &is) {
    cout << "Statie plecare:";
    getline(is, statiePlecare);

    cout << "Statie sosire:";
    getline(is, statieSosire);

    cout << "Moment plecare:\n";
    is >> plecare;
    is.get();

    cout << "Cod tren:";
    getline(is, codTren);

    cout << "Durata calatoriei:";
    is >> durataCalatorie;

    cout << "Distanta parcursa:";
    is >> distantaParcursa;
    is.get();

    cout << "Nr. loc rezervat:";
    is >> nrLocRezervat;
    is.get();


    asociereSerie();
    calcularePret();

    return is;
}

ostream &InterRegioII::write(ostream &os) const {
    RegioII::write(os);

    os << ", Nr. loc rezervat: " << nrLocRezervat;

    return os;
}

void InterRegioII::asociereSerie() {
    serieBilet = "IRII-" + to_string(nrOrd);
}

void InterRegioII::calcularePret() {
    pret = distantaParcursa * 0.7;
}





class InterRegioI : public RegioI, public InterRegioII{
public:
    InterRegioI();

    InterRegioI(string &statiePlecare, string &statieSosire, Moment &plecare, string &codTren, int durataCalatorie, int distantaParcursa, string &meniuRestaurant, int nrLocRezervat);

    // citire
    istream &read(istream &is) override;

    // afisare
    ostream &write(ostream &os) const override;

    void asociereSerie() override;

    void calcularePret() override;
};

InterRegioI::InterRegioI(string &statiePlecare, string &statieSosire, Moment &plecare, string &codTren, int durataCalatorie, int distantaParcursa, string &meniuRestaurant, int nrLocRezervat) :
        RegioI(statiePlecare, statieSosire, plecare, codTren, durataCalatorie, distantaParcursa, meniuRestaurant),
        InterRegioII(statiePlecare, statieSosire, plecare, codTren, durataCalatorie, distantaParcursa, nrLocRezervat) {}

InterRegioI::InterRegioI() = default;

istream &InterRegioI::read(istream &is) {
    cout << "Statie plecare:";
    getline(is, statiePlecare);

    cout << "Statie sosire:";
    getline(is, statieSosire);

    cout << "Moment plecare:\n";
    is >> plecare;
    is.get();

    cout << "Cod tren:";
    getline(is, codTren);

    cout << "Durata calatoriei:";
    is >> durataCalatorie;

    cout << "Distanta parcursa:";
    is >> distantaParcursa;
    is.get();

    cout << "Meniu restaurant:";
    getline(is, meniuRestaurant);

    cout << "Nr. loc rezervat:";
    is >> nrLocRezervat;
    is.get();


    asociereSerie();
    calcularePret();

    return is;
}

ostream &InterRegioI::write(ostream &os) const {
    RegioI::write(os);

    os << ", Nr. loc rezervat: " << nrLocRezervat;

    return os;
}


void InterRegioI::asociereSerie() {
    serieBilet = "IRI-" + to_string(nrOrd);
}

void InterRegioI::calcularePret() {
    pret = distantaParcursa * 0.7 * 1.2;
}





// --------------------------- MENIU INTERACTIV ---------------------------
class Menu {
private:
    vector < shared_ptr <RegioII> > bilete;
public:
    Menu();

    Menu(vector < shared_ptr <RegioII> > &bilete);

    static void listOptions();
    static int chooseOption(int first, int last);
    void mainLoop();

    void elibereazaBilet();
    void listeazaBileteTren();
    void listeazaBileteDistanta();
    void anulareBilet();
};

Menu::Menu() = default;

Menu::Menu(vector < shared_ptr <RegioII> > &bilete) : bilete(bilete) {}

void Menu::listOptions() {
    cout << "1. Elibereaza un bilet.\n";
    cout << "2. Listeaza biletele pentru un anumit tren.\n";
    cout << "3. Listeaza biletele pentru calatorii pe o distanta mai mare ca o valoare data.\n";
    cout << "4. Anuleaza un bilet.\n";
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
        int option = chooseOption(1, 6);
        if (option == 1) {
            elibereazaBilet();
        } else if (option == 2) {
            listeazaBileteTren();
        } else if (option == 3) {
            listeazaBileteDistanta();
        } else if (option == 4) {
            anulareBilet();
        } else if (option == 5) {
            break;
        }
    }
    cout << "\n---------------------------------------------\nProgram incheiat cu succes.";
}

void Menu::elibereazaBilet() {
    cout << "Tip tren (1 - Regio / 2 - InterRegio):";
    int tip = 0; cin >> tip;
    while (tip < 1 || tip > 2){
        cout << "Tip invalid, incearca din nou:";
        cin >> tip;
    }

    cout << "Clasa de confort: (1 - Clasa I, 2 - Clasa II):";
    int clasa = 0; cin >> clasa;
    while (clasa < 1 || tip > 2){
        cout << "Clasa invalida, incearca din nou:";
        cin >> clasa;
    }
    cin.get();

    shared_ptr <RegioII> bilet;
    if (tip == 1 && clasa == 1)
        bilet = make_shared<RegioI>();
    else if (tip == 1 && clasa == 2)
        bilet = make_shared<RegioII>();
    else if (tip == 2 && clasa == 1)
        bilet = make_shared<InterRegioI>();
    else if (tip == 2 && clasa == 2)
        bilet = make_shared<InterRegioII>();

    cin >> *bilet;

    bilete.push_back(bilet);
}

void Menu::listeazaBileteTren() {
    string cod;
    cout << "Codul trenului:";
    cin >> cod;
    for (auto &bilet : bilete){
        if (cod == bilet->getCodTren())
            cout << *bilet << "\n\n";
    }
}

void Menu::listeazaBileteDistanta() {
    int valoare;
    cout << "Valoare distanta:";
    cin >> valoare;
    for (auto &bilet : bilete){
        if (bilet->getDistanta() > valoare)
            cout << *bilet << "\n\n";
    }
}

void Menu::anulareBilet() {
    string serie;
    cout << "Seria biletului:";
    cin >> serie;

    for (int i = 0; i < bilete.size(); ++i){
        if (bilete[i]->getSerie() == serie){
            bilete.erase(bilete.begin() + i);
            break;
        }
    }
}


int main(){
    Menu meniu;
    meniu.mainLoop();

    return 0;
}