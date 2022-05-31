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













// ------------------------------ MENIU INTERACTIV ------------------------------
class Menu {
private:
    vector < shared_ptr <RegioII> > bilete;
public:
    Menu();

    Menu(vector < shared_ptr <RegioII> > &bilete);

    static void listOptions();
    static int chooseOption(int first, int last);
    void mainLoop();


};

Menu::Menu() = default;

Menu::Menu(vector < shared_ptr <RegioII> > &bilete) : bilete(bilete) {}

void Menu::listOptions() {
    cout << "1. .\n";
    cout << "2. .\n";
    cout << "3. .\n";
    cout << "4. .\n";
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
            ();
        } else if (option == 2) {
            ();
        } else if (option == 3) {
            ();
        } else if (option == 4) {
            ();
        } else if (option == 5) {
            break;
        }
    }
    cout << "\n---------------------------------------------\nProgram incheiat cu succes.";
}