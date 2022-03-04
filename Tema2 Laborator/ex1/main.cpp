// 1. Bilete de avion

#include <iostream>
using namespace std;

class Bilet{
private:
    string nume;
    bool clasa1;
public:
    Bilet(){
        nume = "";
        clasa1 = false;
    }
    Bilet(string _nume, bool _clasa1){
        nume = _nume;
        clasa1 = _clasa1;
    }

    void setnume(string _nume){
        nume = _nume;
    }
    void setclasa1(bool _clasa1){
        clasa1 = _clasa1;
    }

    string getnume(){
        return nume;
    }
    bool getclasa1(){
        return clasa1;
    }

    void citeste(){
        cin.get();
        cout<<endl<<"Nume & Prenume:";
        getline(cin, nume);
        cout<<"Clasa 1 (1-da / 0-nu):";
        cin>>clasa1;
    }
};

void statisticaZboruri(int n, Bilet bilete[]){
    int da=0, nu=0;
    for (int i=0; i<n; i++)
    {
        if (bilete[i].getclasa1() == 0)
            nu++;
        else
            da++;
    }
    cout<<endl<<da<<" bilete sunt la clasa 1 si "<<nu<<" nu.";
}

int main()
{
    int n;
    cout<<"Numarul de bilete:"; cin>>n;
    Bilet b[n];
    for(int i=0; i<n; i++)
        b[i].citeste();

    statisticaZboruri(n, b);

    return 0;
}
