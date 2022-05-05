#include <bits/stdc++.h>
#include "util/IoBase.h"
#include "util/functions.h"
using namespace std;



class Building : public IoBase{
protected:
    string color, ownerName;
public:
    Building() = default;

    Building(const string &color, const string &ownerName) : color(color),
                                                             ownerName(ownerName) {}

    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;
};

istream &Building::read(istream &is) {
    IoBase::read(is);

    cout << "color:";
    getline(is, color);
    cout << "ownerName:";
    getline(is, ownerName);

    return is;
}

ostream &Building::write(ostream &os) const{
    IoBase::write(os);
    cout << "color: " << color << ", owner name: " << ownerName;
    return os;
}



class House : public Building{
private:
    int cntFloors;
public:
    House() : cntFloors(0) {}

    House(const string &color, const string &ownerName, int cntFloors) : Building(color, ownerName),
                                                                         cntFloors(cntFloors) {}

    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;
};

istream &House::read(istream &is) {
    Building::read(is);

    cout << "cntFloors:";
    is >> cntFloors; is.get();

    return is;
}

ostream & House::write(ostream &os) const {
    Building::write(os);
    os << ", nr. of floors: " << cntFloors;
    return os;
}



class Apartment : public Building{
private:
    int floor;
public:
    Apartment() : floor(0) {}

    Apartment(const string &color, const string &ownerName, int floor) : Building(color, ownerName), floor(floor) {}

    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;
};

istream &Apartment::read(istream &is) {
    Building::read(is);

    cout << "Floor:";
    is >> floor; is.get();

    return is;
}

ostream &Apartment::write(ostream &os) const {
    Building::write(os);
    os << ", floor: " << floor;
    return os;
}


shared_ptr <Building> readBuilding(){
    shared_ptr<Building> newBuilding;
    int option = -1;
    while (option < 1 || option > 2) {
        cout << "Alege un tip de cladire (1 - House, 2 - Apartment):";
        cin >> option;
        cin.get();

        if (option == 1)
            newBuilding = make_shared<House>();
        else if (option == 2)
            newBuilding = make_shared<Apartment>();
    }

    cin>>*newBuilding;
    return newBuilding;
}


class BaseMenu {
public:
    virtual void listOptions() {}
    virtual int chooseOption(int first, int last) { return 0; }
    virtual void mainLoop() {}
};


class SimpleMenu : public BaseMenu {
private:
    vector < shared_ptr < Building > > buildings;
public:
    SimpleMenu() = default;
    explicit SimpleMenu(const vector<shared_ptr<Building>> &buildings) : buildings(buildings) {}

    void listOptions() override;
    int chooseOption(int first, int last) override;
    void mainLoop() override;

    void addBuilding();
    void showBuildings();
    void deleteBuilding();
    void modifyBuilding();
};

void SimpleMenu::listOptions() {
    cout << "1. Adauga o noua cladire.\n";
    cout << "2. Afiseaza toate cladirile.\n";
    cout << "3. Sterge o cladire existenta.\n";
    cout << "4. Modifica o cladire.\n";
    cout << "5. Iesire.\n";
}

int SimpleMenu::chooseOption(int first, int last) {
    int option = -1;
    while (option < first || option > last) {
        cout << "\nPentru a rula comanda, alegeti un numar intre " << first << " si " << last << '\n';
        listOptions();
        cout << "Alegere:";
        cin >> option;
    }
    return option;
}

void SimpleMenu::mainLoop() {
    while (true) {
        int option = chooseOption(1, 5);
        if (option == 1) {
            addBuilding();
        } else if (option == 2) {
            showBuildings();
        } else if (option == 3) {
            deleteBuilding();
        } else if (option == 4) {
            modifyBuilding();
        } else if (option == 5) {
            break;
        }
    }
    cout << "\n---------------------------------\nProgramul s-a incheiat cu succes.";
}

void SimpleMenu::addBuilding() {
    shared_ptr <Building> newBuilding = readBuilding();
    buildings.push_back(newBuilding);
    cout << "Cladire adaugata.\n";
}

void SimpleMenu::showBuildings() {
    if (buildings.empty())
        cout << "\nNu exista nicio cladire in acest moment.\n";
    else {
        cout << "\nCladirile in acest moment:\n";
        for (int i = 0; i < buildings.size(); ++i)
            cout << i + 1 << ". " << *buildings[i] << "\n";
    }
}

void SimpleMenu::deleteBuilding() {
    if (buildings.empty())
        cout << "\nNu exista nicio cladire in acest moment.\n";
    else {
        showBuildings();
        int option = -1;
        while (option < 1 || option > buildings.size()) {
            cout << "Alege cladirea care sa fie stearsa:";
            cin >> option;
            cin.get();
        }
        buildings.erase(buildings.begin() + option - 1);
        cout << "Cladirea " << option << " a fost stearsa.\n";
    }
}

void SimpleMenu::modifyBuilding() {
    if (buildings.empty())
        cout << "\nNu exista nicio cladire in acest moment.\n";
    else {
        showBuildings();
        int option = -1;
        while (option < 1 || option > buildings.size()) {
            cout << "Alege cladirea care sa fie modificata:";
            cin >> option;
            cin.get();
        }
        cin >> *buildings[option - 1];
        cout << "Cladirea " << option << " a fost modificata.\n";
    }
}



int main() {
    SimpleMenu menu = SimpleMenu({
                             make_shared < House > (House("rosu", "Popescu Ion", 5)),
                             make_shared < House > (House("galben", "Gigel Gigel", 7)),
                             make_shared < Apartment > (Apartment("albastru", "Andrei", 4)),
                             make_shared < Apartment > (Apartment("verde", "Ionut", 10))
                     });
    menu.mainLoop();
}