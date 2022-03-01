// 4. Carti
#include <iostream>
using namespace std;

class Carte{
private:
    string titlu;
    int nr_pagini, pg_crt;
public:
    Carte(){
        titlu = "";
        nr_pagini = pg_crt = 0;
    }
    Carte(string Titlu, int nr, int pg){
        titlu = Titlu;
        nr_pagini = nr;
        pg_crt = pg;
    }

    void citeste(){
        cout<<"Titlul:";
        getline(cin, titlu);
        cout<<"Numarul de pagini:";
        cin>>nr_pagini;
        cout<<"Pagina curenta:";
        cin>>pg_crt;
        cin.get();
    }

    void afiseaza(){
        cout<<"Cartea cu titlul \""<<titlu<<"\" sta deschisa la pagina "<<pg_crt<<" din "<<nr_pagini<<"."<<endl;
    }

    void setPaginaCurenta(int pagina){
        if (pagina <= nr_pagini)
            pg_crt = pagina;
        else
            cout<<"Nu poti sari la pagina "<<pagina<<" din "<<nr_pagini<<" deoarece nu exista!"<<endl;
    }

    int getPaginaMaxima(){
        return nr_pagini;
    }
};

int main(){
    Carte c;
    c.citeste();
    c.afiseaza();
    c.setPaginaCurenta(30);
    c.afiseaza();
    c.setPaginaCurenta(c.getPaginaMaxima()+1);

    return 0;
}
