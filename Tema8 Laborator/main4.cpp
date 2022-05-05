#include <bits/stdc++.h>
#include "util/IoBase.h"
#include "util/functions.h"
using namespace std;



class BaseMenu {
protected:
    string label;
public:
    BaseMenu() = default;
    explicit BaseMenu(const string &label) : label(label) {}

    const string &getLabel() const {
        return label;
    }

    virtual void listOptions() {};
    virtual int chooseOption(int first, int last) {return 0;};
    virtual void mainLoop() {};
};



class SimpleMenu : public BaseMenu {
public:
    SimpleMenu() = default;

    explicit SimpleMenu(const string &label) : BaseMenu(label) {}

    void listOptions() override;
    int chooseOption(int first, int last) override;
    void mainLoop() override;
};


void SimpleMenu::listOptions() {
    if (label == "Create"){
        cout << "1. C++ Class\n2. Text File\n3. Back\n";
    }
    else if (label == "Open"){
        cout << "1. Browse\n2. Go back\n";
    }
}

int SimpleMenu::chooseOption(int first, int last) {
    int option = -1;
    while (option < first || option > last){
        cout << "\nAlegeti una din urmatoarele optiuni:\n";
        listOptions();
        cout << "Alegere:";
        cin >> option;
        if (option > last)
            cout << "Alegere invalida\n";
    }
    return option;
}

void SimpleMenu::mainLoop() {
    while (true) {
        if (label == "Create"){
            int option = chooseOption(1, 3);
            if (option == 1) {
                cout << "C++ Class created.\n";
            }
            else if (option == 2) {
                cout << "Text File created.\n";
            }
            else if (option == 3) {
                break;
            }
        }
        else if (label == "Open"){
            int option = chooseOption(1, 2);
            if (option == 1) {
                cout << "File opened for browsing.\n";
            }
            else if (option == 2) {
                break;
            }
        }
    }
}



class ComposedMenu : public BaseMenu{
private:
    vector <shared_ptr<BaseMenu>> subMenus;
public:
    ComposedMenu() = default;

    ComposedMenu(const string &label, const vector<shared_ptr<BaseMenu>> &subMenus) : BaseMenu(label),
                                                                                      subMenus(subMenus) {}

    void listOptions() override;
    int chooseOption(int first, int last) override;
    void mainLoop() override;
};

void ComposedMenu::listOptions(){
    int cnt = 0;
    for (auto &subMenu : subMenus){
        cout << ++cnt << ". " << subMenu->getLabel() << '\n';
    }
    cout << ++cnt << ". Delete File\n";
    cout << ++cnt << ". Exit\n";
}

int ComposedMenu::chooseOption(int first, int last) {
    int option = -1;
    while (option < first || option > last){
        cout << "\nAlegeti una din urmatoarele optiuni:\n";
        listOptions();
        cout << "Alegere:";
        cin >> option;
        if (option > last)
            cout << "Alegere invalida\n";
    }
    return option;
}

void ComposedMenu::mainLoop() {
    while (true) {
        int option = chooseOption(1, 5);
        if (option == 1) {
            subMenus[0]->mainLoop();
        }
        else if (option == 2) {
            subMenus[1]->mainLoop();
        }
        else if (option == 3) {
            cout << "File deleted\n";
        }
        else if (option == 4) {
            break;
        }
    }
    cout << "\n---------------------------------\nProgramul s-a incheiat cu succes.";
}

int main() {
    ComposedMenu File = ComposedMenu("File", {
            make_shared<SimpleMenu>(SimpleMenu("Create")),
            make_shared<SimpleMenu>(SimpleMenu("Open"))
    });
    File.mainLoop();
}