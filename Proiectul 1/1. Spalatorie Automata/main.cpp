#include <iostream>
#include <iomanip>
using namespace std;



class Durata{
private:
    int minute, secunde;
public:
    Durata(){
        minute = secunde = 0;
    }
    Durata(int a, int b){
        minute = a;
        secunde = b;
    }

    int get_minute() const{
        return minute;
    };
    int get_secunde() const{
        return secunde;
    };

    void afiseaza() const{
        cout<<setfill('0')<<setw(2)<<minute<<":"<<setw(2)<<secunde;
    }
};



class MasinaSpalat{
private:
    bool liber;
    Durata timp;
    int capsule;
public:
    MasinaSpalat(){
        liber = true;
        capsule = 0;
    }
    MasinaSpalat(bool a, Durata d, int nr){
        liber = a;
        capsule = nr;
        timp = d;
    }

    bool get_liber() const{
        return liber;
    }
    Durata get_durata() const{
        return timp;
    }
    int getCapsule() const{
        return capsule;
    }

    void set_liber(bool a){
        liber = a;
    }
    void set_durata(Durata t){
        timp = t;
    }
    void decr_capsule(){
        --capsule;
    }
};



class Spalatorie{
private:
    int nr_masini;
    MasinaSpalat masini[5];
public:
    Spalatorie(){
        nr_masini = 0;
    }
    Spalatorie(int nr, MasinaSpalat m[]){
        nr_masini = nr;
        for(int i=0; i<nr; i++)
            masini[i] = m[i];
    }

    int get_nr_masini() const{
        return nr_masini;
    };

    MasinaSpalat get_masina(int i){
        return masini[i];
    }

    void listeazaMasini();
    void adaugaJob(int i, Durata t);
    void actualizeazaTimp(Durata t);
};



void Spalatorie::listeazaMasini(){
    cout<<"Spalatoria in prezent:\n";
    for (int i=0; i<nr_masini; i++){
        int nrCapsule = masini[i].getCapsule();
        if (masini[i].get_liber()){
            if (nrCapsule)
                cout<<"Masina "<<i<<" este libera si poate fi utilizata ("<<nrCapsule<<" capsule de detergent ramase).\n";
            else
                cout<<"Masina "<<i<<" este libera, dar neutilizabila, deoarece a ramas fara capsule de detergent.\n";
        }
        else{
            cout<<"Masina "<<i<<" este ocupata pentru inca ";
            masini[i].get_durata().afiseaza();
            if (nrCapsule)
                cout<<", apoi va putea fi utilizata ("<<nrCapsule<<" capsule de detergent ramase).\n";
            else
                cout<<", apoi va deveni inutilizabila, deoarece va ramane fara capsule de detergent.\n";
        }
    }
    cout<<endl;
}



void Spalatorie::adaugaJob(int i, Durata t){
    if (masini[i].get_liber()) {
        if (masini[i].getCapsule() == 0)
            cout<<"Nu se poate adauga spalarea deoarece masina "<<i<<" a ramas fara capsule de detergent.\n";
        else {
            masini[i].decr_capsule();
            masini[i].set_liber(false);
            masini[i].set_durata(t);
            cout<<"Spalare adaugata! Masina "<<i<<" este acum ocupata pentru ";
            t.afiseaza();
            cout<<".\n";
        }
    }
    else{
        cout<<"Nu se poate adauga spalarea deoarece masina "<<i<<" este ocupata pentru inca ";
        masini[i].get_durata().afiseaza();
        cout<<".\n";
    }
    cout<<endl;
}



void Spalatorie::actualizeazaTimp(Durata t){
    cout<<"Timpul a fost actualizat cu ";
    t.afiseaza(); cout<<".\n\n";

    for (int i=0; i<nr_masini; ++i){
        if (!masini[i].get_liber()){
            int timp_actual = masini[i].get_durata().get_minute() * 60 + masini[i].get_durata().get_secunde();
            int timp_adaugat = t.get_minute() * 60 + t.get_secunde();

            if (timp_adaugat >= timp_actual){
                masini[i].set_liber(true);
                masini[i].set_durata(Durata(0, 0));
            }
            else{
                timp_actual -= timp_adaugat;
                masini[i].set_durata(Durata(timp_actual / 60, timp_actual % 60));
            }
        }
    }
}



void listeazaMasiniLibere(Spalatorie s){
    cout<<"Urmatoarele masini sunt libere si utilizabile:";
    for (int i=0; i<s.get_nr_masini(); ++i){
        MasinaSpalat m = s.get_masina(i);
        if (m.get_liber() && m.getCapsule())
            cout<<" "<<i;
    }
    cout<<".\n\n";
}



int main(){
    MasinaSpalat masini[5] = {
            MasinaSpalat(false, Durata(1, 0), 1),
            MasinaSpalat(false, Durata(1, 20), 2),
            MasinaSpalat(true, Durata(0, 0), 3),
            MasinaSpalat(true, Durata(0, 0), 1),
            MasinaSpalat(false, Durata(5, 15), 3),
    };
    Spalatorie spalatorie(5, masini);

    spalatorie.listeazaMasini();
    listeazaMasiniLibere(spalatorie);

    spalatorie.adaugaJob(1, Durata(1, 30));
    spalatorie.adaugaJob(3, Durata(1, 30));
    spalatorie.listeazaMasini();

    listeazaMasiniLibere(spalatorie);

    spalatorie.actualizeazaTimp(Durata(1, 7));
    spalatorie.listeazaMasini();

    spalatorie.adaugaJob(0, Durata(1, 30));
    spalatorie.listeazaMasini();

    spalatorie.actualizeazaTimp(Durata(2, 45));
    spalatorie.listeazaMasini();

    return 0;
}
