// Student: Florea Mădălin-Alexandru
// Tutore: Deaconu Eduard-Ștefan
// Compilator: Bundled MinGW, Version w64 9.0



#include <bits/stdc++.h>
using namespace std;





// Clasa folosita pentru citire si afisare
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


// Clasa pentru a retine data
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





// Clasa pentru un tratament
class Tratament : public InOutBase {
private:
    string specialitate, modAdministrare;
    int durataTratament;
    float pret;
    vector <string> medicamente;

    // campuri pentru plata tratamentului
    static int staticIdPlata;
    int idPlata;
    Data data;
    float sumaPlata;
public:
    Tratament();

    const string &getSpecialitate() const;

    const string &getModAdministrare() const;

    int getDurata() const;

    const vector<string> &getMedicamente() const;

    // citire
    istream &read(istream &is) override;

    // afisare
    ostream &write(ostream &os) const override;
};

int Tratament::staticIdPlata = 0;


Tratament::Tratament() : durataTratament(0), pret(0), idPlata(++staticIdPlata), sumaPlata(0){}


istream &Tratament::read(istream &is) {
    InOutBase::read(is);

    cout << "Specialitate (edontotie, general, aparat dentar):";
    while (true) {
        try {
            getline(is, specialitate);
            if (specialitate != "edontotie" && specialitate != "general" && specialitate != "aparat dentar")
                throw string("Specialitate invalida, incearca din nou:");
            else
                break;
        }
        catch (string &error) {
            cout << error;
        }
    }

    cout << "Durata tratamentului:";
    is >> durataTratament;
    is.get();

    cout << "Mod administrare:";
    getline(is, modAdministrare);

    cout << "Pret:";
    is >> pret;
    is.get();

    medicamente.clear();
    cout << "Nr. medicamente:";
    int n;
    is >> n;
    cout << "Alegeti din urmatoarele medicamente:\n";
    cout << "1. Antibiotic\n2. Pastile\n3. Anestezice\n4. Pasta de dinti speciala\n5. Injectii\n";
    cout << "Introduceti pe rand nr. corespunzatoare):\n";
    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        while (x < 1 || x > 5) {
            cout << "Invalid, incearca din nou:";
            cin >> x;
        }

        if (x == 1)
            medicamente.emplace_back("Antibiotic");
        else if (x == 2)
            medicamente.emplace_back("Pastile");
        else if (x == 3)
            medicamente.emplace_back("Anestezice");
        else if (x == 4)
            medicamente.emplace_back("Pasta de dinti speciala");
        else if (x == 5)
            medicamente.emplace_back("Injectii");
    }

    cout << "Data cand a fost efectuata plata:\n";
    is >> data; is.get();

    if (specialitate == "edontotie")
        sumaPlata = 1.15 * pret; // pret + 0.1 * pret + 0.05 * pret
    else if (specialitate == "general")
        sumaPlata = 1.08 * pret + 60; // pret + 0.08 * pret + 60
    else
        sumaPlata = pret + 3000 + 100 * durataTratament;

    return is;
}


ostream &Tratament::write(ostream &os) const {
    InOutBase::write(os);

    os << "Specialitate: " << specialitate << ", durata: " << durataTratament << " luni, ";
    os << "Pret: " << pret << " lei\nMod administrare: " << modAdministrare;
    os << "\nMedicamente: ";
    for (auto &medicament : medicamente)
        os << medicament << ", ";

    os << "ID Plata: " << idPlata << ", Data platii: " << data;
    os << ", Suma de plata: " << sumaPlata << " lei.";

    return os;
}

const string &Tratament::getSpecialitate() const {
    return specialitate;
}

const string &Tratament::getModAdministrare() const {
    return modAdministrare;
}

const vector<string> &Tratament::getMedicamente() const {
    return medicamente;
}

int Tratament::getDurata() const {
    return durataTratament;
}






// Clasa de baza folosita pentru retinerea informatiilor comune oricarui tip de persoana
class Persoana : public InOutBase{
protected:
    string nume, prenume;
    int varsta;
public:
    Persoana();

    // citire
    istream &read(istream &is) override;

    // afisare
    ostream &write(ostream &os) const override;
};


Persoana::Persoana() : varsta(0) {}


istream &Persoana::read(istream &is) {
    InOutBase::read(is);

    cout << "Nume:";
    getline(is, nume);

    cout << "Prenume:";
    getline(is, prenume);

    cout << "Varsta:";
    is >> varsta;
    is.get();

    return is;
}


ostream &Persoana::write(ostream &os) const {
    InOutBase::write(os);

    cout << "Nume: " << nume << ", Prenume: " << prenume << ", Varsta: " << varsta << " ani";

    return os;
}





// Clasa pentru pacienti

class Pacient : public Persoana {
private:
    vector <Tratament> istoricTratamente;
public:
    Pacient() = default;

    // citire
    istream &read(istream &is) override;

    // afisare
    ostream &write(ostream &os) const override;
};

istream &Pacient::read(istream &is) {
    Persoana::read(is);

    int nrTratamente;
    cout << "Nr. tratamente:";
    is >> nrTratamente; is.get();
    for (int i = 1; i <= nrTratamente; ++i) {
        cout << "Citire tratament " << i << '\n';
        Tratament t;
        is >> t;
        istoricTratamente.push_back(t);
    }

    return is;
}


ostream &Pacient::write(ostream &os) const {
    Persoana::write(os);

    os << "\n\nTratamente:";
    int cnt = 0;
    for (auto &tratament : istoricTratamente) {
        os << "\n\nTratamentul " << ++cnt <<":\n" << tratament << "\n";
        os << "Modul de administrare: " << tratament.getModAdministrare();

        string specialitate = tratament.getSpecialitate();

        if (specialitate == "edontotie") {
            os << " pe o durata de ";

            if (varsta < 18)
                os << tratament.getDurata() * 2; // se dubleaza durata
            else
                os << tratament.getDurata();
            os << " luni.";
        }

        else if (specialitate == "general") {
            os << ", medicamentatia fiind urmatoarea: ";
            for (auto &medicament : tratament.getMedicamente())
                os << medicament << ", ";
        }

        else {
            os << ", (!) Se recomanda folosirea periutelor de dinti interdentare";
        }
    }

    return os;
}





// Clasa pentru dentisti
class Dentist : public Persoana {
private:
    int vechime;
    string specializare;
public:
    Dentist();

    // citire
    istream &read(istream &is) override;

    // afisare
    ostream &write(ostream &os) const override;
};


Dentist::Dentist() : vechime(0) {}


istream &Dentist::read(istream &is) {
    Persoana::read(is);

    cout << "Vechime:";
    is >> vechime; is.get();

    cout << "Specializare (ortodont, tehnician, stomatolog):";
    while (true) {
        try {
            getline(is, specializare);
            if (specializare != "ortodont" && specializare != "tehnician" && specializare != "stomatolog")
                throw string("Specializare invalida, incearca din nou:");
            else
                break;
        }
        catch (string &error) {
            cout << error;
        }
    }

    return is;
}


ostream &Dentist::write(ostream &os) const {
    Persoana::write(os);

    cout << "\nVechime: " << vechime << " ani, Specializare: " << specializare;

    return os;
}





// Clasa pentru Receptioneri
class Receptioner : public Persoana {
private:
    int grad;
    bool studiiSuperioare;
public:
    Receptioner() : grad(0), studiiSuperioare(false) {}

    // citire
    istream &read(istream &is) override;

    // afisare
    ostream &write(ostream &os) const override;
};


istream &Receptioner::read(istream &is) {
    Persoana::read(is);

    cout << "Grad (1/2/3):";
    is >> grad;
    while (grad < 1 || grad > 3) {
        cout << "Grad invalid, incearca din nou:";
        is >> grad;
    }
    is.get();

    cout << "Are studii superioare? (da sau nu):";
    string studii;
    getline(is, studii);
    while (studii != "da" && studii != "nu") {
        cout << "raspuns invalid, incearca din nou:";
        getline(is, studii);
    }

    if (studii == "da")
        studiiSuperioare = true;
    else
        studiiSuperioare = false;

    return is;
}


ostream &Receptioner::write(ostream &os) const {
    Persoana::write(os);

    cout << "\nGrad: " << grad << ", ";

    if (!studiiSuperioare)
        cout << "nu ";
    cout << "are studii superioare.";

    return os;
}











int main(){
    Pacient p;
    cin >> p ;
    cout << p << "\n\n";

    Dentist d;
    cin >> d;
    cout << d << "\n\n";

    Receptioner r;
    cin >> r;
    cout << r << "\n\n";

    return 0;
}
