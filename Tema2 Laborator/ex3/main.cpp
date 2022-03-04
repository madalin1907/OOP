// 3. Tablouri decorative

#include <iostream>
using namespace std;

class Tablou{
private:
    int inaltime, latime, pret;
    string mesaj;
public:
    Tablou(){
        inaltime = latime = pret = 0;
        mesaj = "";
    }
    Tablou(int Inaltime, int Latime, int Pret, string Mesaj){
        inaltime = Inaltime;
        latime = Latime;
        pret = Pret;
        mesaj = Mesaj;
    }


    string getmesaj(){
        return mesaj;
    }

    void citeste(){
        cout<<endl<<"Inaltime:"; cin>>inaltime;
        cout<<"Latime:"; cin>>latime;
        cout<<"Pret:"; cin>>pret;
        cin.get();
        cout<<"Mesaj motivational:"; getline(cin, mesaj);
    }
};

int nrcuv(string sir){
    int cnt = 1, ok = 0;
    for (int i=0; i<sir.length(); ++i)
        if (sir[i] == ' ')
        {
            if (ok == 0){
                cnt++;
            }
            ok = 1;
        }
        else{
            ok = 0;
        }
    return cnt;
}

int main()
{
    int n, maxim = 0, indice;
    cout<<"Numarul de tablouri:"; cin>>n;
    Tablou t[n];
    for (int i=0; i<n; i++){
        t[i].citeste();
        int nr = nrcuv(t[i].getmesaj());
        if (nr > maxim){
            maxim = nr;
            indice = i;
        }
    }

    cout<<"Mesajul motivational cu numar maxim de cuvinte ("<<maxim<<") este \""<<t[indice].getmesaj()<<"\".";

    return 0;
}
