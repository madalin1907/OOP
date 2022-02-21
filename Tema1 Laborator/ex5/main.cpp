#include <iostream>
using namespace std;

struct evenimente{
    int ani, lunai, zii;
    int anf, lunaf, zif;
    char nume[100];
    int ora;
}v[101];
int n;

void citire(int i)
{
    cin>>v[i].zii>>v[i].lunai>>v[i].ani;
    cin>>v[i].zif>>v[i].lunaf>>v[i].anf;
    cin>>v[i].nume;
}

int comparare (int azi, int aluna, int aan, int bzi, int bluna, int ban)
{
    if (aan == ban)
    {
        if (aluna == bluna)
        {
            if (azi > bzi)
                return 1;
        }
        else if (aluna > bluna)
        {
            return 1;
        }
    }
    else if (aan > ban)
    {
        return 1;
    }
    return 0;
}//functia returneaza 1 daca data evenimentului a este mai mare decat data evenimentului b si 0 in caz contrar

void sortare() //ordonez evenimentele in ordine crescatoare, dupa data de final
{
    for (int i=1; i<n; i++)
        for (int j=i+1; j<=n; j++)
            if (comparare(v[i].zif, v[i].lunaf, v[i].anf, v[j].zif, v[j].lunaf, v[j].anf) == 1)
                swap(v[i], v[j]);
}

void afisare(int i)
{
    cout<<v[i].nume<<": ";
    cout<<v[i].zii<<"."<<v[i].lunai<<"."<<v[i].ani<<" - ";
    cout<<v[i].zif<<"."<<v[i].lunaf<<"."<<v[i].anf<<endl;
}

int main()
{
    cin>>n;
    for (int i=1; i<=n; i++)
        citire(i);
    sortare();

    cout<<"Lista cu cele mai multe evenimente care nu se suprapun:"<<endl;
    afisare(1);
    int ult = 1;
    for (int i=2; i<=n; i++)
        if (comparare(v[ult].zif, v[ult].lunaf, v[ult].anf, v[i].zii, v[i].lunai, v[i].ani) == 0) //daca data de inceput a evenimentului i este mai mare decat data de final a ultimului eveniment din lista
        {
            afisare(i);
            ult=i;
        }

    return 0;
}
