// 7. Caminele si cantatul

#include <bits/stdc++.h>
#include <ostream>

using namespace std;

class IntervalOrar{
private:
    int ora_inceput, minut_inceput;
    int ora_final, minut_final;
public:
    IntervalOrar() : ora_inceput(0), minut_inceput(0), ora_final(0), minut_final(0) {}
    IntervalOrar(int oraInceput, int minutInceput, int oraFinal, int minutFinal) : ora_inceput(oraInceput),
                                                                                   minut_inceput(minutInceput),
                                                                                   ora_final(oraFinal),
                                                                                   minut_final(minutFinal) {}

    int getOraInceput() const {
        return ora_inceput;
    }

    int getMinutInceput() const {
        return minut_inceput;
    }

    int getOraFinal() const {
        return ora_final;
    }

    int getMinutFinal() const {
        return minut_final;
    }

    friend ostream &operator<<(ostream &os, const IntervalOrar &orar);
};

ostream &operator<<(ostream &os, const IntervalOrar &orar) {
    os << setfill('0') << setw(2) << orar.ora_inceput << ":" << setw(2) << orar.minut_inceput << " - "
       << setw(2) << orar.ora_final << ":" << setw(2) << orar.minut_final;

    return os;
}



class Camin{
private:
    string nume;
    int nr_camere, nr_intervale;
    vector <IntervalOrar> intervale;
public:
    Camin() : nr_camere(0), nr_intervale(0) {}

    Camin(const string &nume, int nrCamere, int nrIntervale, const vector<IntervalOrar> &intervale) : nume(nume),
                                                                                                      nr_camere(nrCamere),
                                                                                                      nr_intervale(nrIntervale),
                                                                                                      intervale(intervale) {}

    const vector<IntervalOrar> &getIntervale() const {
        return intervale;
    }

    const string &getNume() const {
        return nume;
    }

    friend ostream &operator<<(ostream &os, const Camin &camin);
};

ostream &operator<<(ostream &os, const Camin &camin) {
    os << camin.nume << ":\n";
    for (auto &x : camin.intervale)
        cout<<x<<"\n";

    return os;
}



int main(){
    vector <Camin> v;
    v.push_back({"Camin1", 10, 4, {
        {10, 15, 11, 15},
        {14, 20, 15, 30},
        {20, 20, 21, 00},
        {22, 00, 23, 00}}});
    v.push_back({"Camin2", 20, 3, {
            {9, 15, 10, 00},
            {12, 20, 13, 30},
            {20, 20, 21, 00}}});
    v.push_back({"Camin3", 20, 1, {
            {15, 00, 17, 0}}});
    v.push_back({"Camin4", 20, 2, {
            {17, 30, 18, 00},
            {20, 00, 21, 00}}});
    v.push_back({"Camin5", 30, 3, {
            {9, 45, 10, 45},
            {12, 00, 13, 30},
            {21, 00, 22, 00}}});


    vector <int> maxim(1440, 1);
    vector <string> max_camine(3);

    for (int i = 0; i < v.size()-2; i++)
        for (int j = i+1; j < v.size()-1; j++)
            for (int k = j+1; k < v.size(); k++){
                vector <int> fr(1440, 0);

                vector <IntervalOrar> interv1 = v[i].getIntervale();
                for (auto &a : interv1){
                    for (int r = a.getOraInceput()*60 + a.getMinutInceput(); r <= a.getOraFinal()*60 + a.getMinutFinal(); r++)
                        fr[r] = 1;
                }

                vector <IntervalOrar> interv2 = v[j].getIntervale();
                for (auto &a : interv2){
                    for (int r = a.getOraInceput()*60 + a.getMinutInceput(); r <= a.getOraFinal()*60 + a.getMinutFinal(); r++)
                        fr[r] = 1;
                }

                vector <IntervalOrar> interv3 = v[k].getIntervale();
                for (auto &a : interv3){
                    for (int r = a.getOraInceput()*60 + a.getMinutInceput(); r <= a.getOraFinal()*60 + a.getMinutFinal(); r++)
                        fr[r] = 1;
                }
                long long nr_minute_liniste = count(fr.begin(), fr.end(), 0);
                if (nr_minute_liniste > count(maxim.begin(), maxim.end(), 0)){
                    maxim = fr;
                    max_camine[0] = v[i].getNume();
                    max_camine[1] = v[j].getNume();
                    max_camine[2] = v[k].getNume();
                }
            }
    for (auto &i : max_camine)
        cout<<i<<" ";
    cout<<"\n";

    int i = 0, j;
    while (i < 1440){
        if (maxim[i] == 0){
            j = i;
            while (maxim[i]==0 && i<1440)
                ++i;
            cout << setfill('0') << setw(2) << j/60 << ":" << setw(2) << j%60 <<
                              " - " << setw(2) << (i-1)/60 << ":" << setw(2) << (i-1)%60 <<"\n";
        }
        i++;
    }

    return 0;
}