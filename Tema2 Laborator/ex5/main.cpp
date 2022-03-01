// 5. Banca si datele clientilor ei

#include <iostream>
#include <iomanip>
using namespace std;

class Client{
private:
    int id;
    float suma;
public:
    Client(){
        id = 0;
        suma = 0;
    }
    Client(int ID, float S){
        id = ID;
        suma = S;
    }

    float get_suma(){
        return suma;
    }
    void citeste(){
        cout<<"\nID-ul clientului:"; cin>>id;
        cout<<"Suma din cont:"; cin>>suma;
    }
};

class Banca{
private:
    int nr_clienti;
    Client clienti[30];
public:
    Banca(){
        nr_clienti = 0;
    }

    void citeste(){
        cout<<"Numarul de clienti:";
        cin>>nr_clienti;
        for (int i=0; i<nr_clienti; ++i)
            clienti[i].citeste();
    }

    float suma_totala(){
        float s = 0;
        for (int i=0; i<nr_clienti; ++i)
            s += clienti[i].get_suma();
        cout<<"Cantitatea totala de bani care se afla in banca este "<<s<<".\n";
    }

    void cel_putin_1000(){
        int k = 0;
        for (int i=0; i<nr_clienti; ++i)
            if (clienti[i].get_suma() >= 1000)
                ++k;
        cout<<k<<" clienti au cel putin 1000 RON in cont.\n";
    }

    void peste_100(){
        int k = 0;
        for (int i=0; i<nr_clienti; ++i)
            if (clienti[i].get_suma() >= 100)
                ++k;
        cout<<setprecision(2)<<fixed<<(float) k/nr_clienti * 100<<"% dintre clienti au peste 100 RON in cont.\n";
    }
};

int main(){
    Banca B;
    int n;

    B.citeste();

    cout<<endl;
    B.suma_totala();
    B.cel_putin_1000();
    B.peste_100();

    return 0;
}
//In cazul în care nu vrem să folosim clasa Client, clasa Banca ar trebui să rețină id-urile clienților și
//sumele din conturile acestora în doi vectori separați (int IDs[30] și float sume[30], spre exemplu).
