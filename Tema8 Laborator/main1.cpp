#include <iostream>
using namespace std;


class BaseMenu {
public:
    virtual void listOptions() {}
    virtual int chooseOption(int first, int last) { return 0; }
    virtual void mainLoop() {}
};


class SimpleMenu : public BaseMenu {
public:
    void listOptions() override;
    int chooseOption(int first, int last) override;
    void mainLoop() override;

    void option1();
    void option2();
    void option3();
};


void SimpleMenu::listOptions() {
    cout << "1. Adauga o noua cladire.\n";
    cout << "2. Sterge o cladire existenta.\n";
    cout << "3. Modifica o cladire.\n";
    cout << "4. Iesire.\n";
}

int SimpleMenu::chooseOption(int first, int last) {
    int option = -1;
    while (option < first || option > last) {
        cout << '\n';
        cout << "Pentru a rula comanda, alegeti un numar intre " << first << " si " << last << '\n';
        listOptions();
        cout << "Alegere:";
        cin >> option;
    }
    return option;
}

void SimpleMenu::mainLoop() {
    while (true) {
        int option = chooseOption(1, 4);
        if (option == 1) {
            option1();
        } else if (option == 2) {
            option2();
        } else if (option == 3) {
            option3();
        } else if (option == 4) {
            break;
        }
    }
    cout << '\n'
         << "---------------------------------"
         << '\n'
         << "Programul s-a incheiat cu succes.";
}


void SimpleMenu::option1() {
    cout << "Aici vom adauga o noua cladire.\n";
}

void SimpleMenu::option2() {
    cout << "Aici vom sterge una dintre cladirile existente.\n";
}

void SimpleMenu::option3() {
    cout << "Aici vom modifica datele uneia dintre cladirile existente.\n";
}


int main() {
    SimpleMenu menu;
    menu.mainLoop();
}