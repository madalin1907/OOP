// 6. Trecutul se repeta

#include <iostream>
using namespace std;

class Data{
private:
    int zi, luna, an;
public:
    Data(){
        zi = luna = an = 0;
    }
    Data(int ZI, int LUNA, int AN){
        zi = ZI;
        luna = LUNA;
        an = AN;
    }

    void citeste(){
        cin>>zi>>luna>>an;
    }
    void afisare(){
        cout<<zi<<'.'<<luna<<'.'<<an;
    }

    int get_zi(){
        return zi;
    }
    int get_luna(){
        return luna;
    }
    int get_an(){
        return an;
    }
};

class Event{
private:
    Data start, end;
    string nume;
public:
    Event(){
        nume = "";
    }
    Event(string Nume, Data Start, Data End){
        nume = Nume;
        start = Start;
        end = End;
    }

    void citeste(){
        cout<<endl<<"Data de inceput:"; start.citeste();
        cout<<"Data de final:"; end.citeste();
        cin.get();
        cout<<"Numele evenimentului:"; getline(cin, nume);
    }
    void afisare(){
        cout<<nume<<": ";
        start.afisare();
        cout<<" - ";
        end.afisare();
        cout<<endl;
    }

    Data get_start(){
        return start;
    }
    Data get_end(){
        return end;
    }
};

int comparare(Data a, Data b){
    if (a.get_an() == b.get_an())
    {
        if (a.get_luna() == b.get_luna())
        {
            if (a.get_zi() > b.get_zi())
                return 1;
        }
        else if (a.get_luna() > b.get_luna())
        {
            return 1;
        }
    }
    else if (a.get_an() > b.get_an())
    {
        return 1;
    }
    return 0;
}//functia returneaza 1 daca data evenimentului a este mai mare decat data evenimentului b si 0 in caz contrar

void sortare(Event e[], int n){ //ordonez evenimentele in ordine crescatoare, dupa data de final
    for (int i=0; i<n-1; ++i)
        for (int j=i+1; j<n; ++j)
            if (comparare(e[i].get_end(), e[j].get_end()))
                swap(e[i], e[j]);
}

int main()
{
    Event e[30];
    int n;

    cout<<"Numarul de evenimente:"; cin>>n;
    for(int i=0; i<n; ++i)
       e[i].citeste();

    sortare(e, n);

    cout<<endl<<"Lista cu cele mai multe evenimente care nu se suprapun:"<<endl;
    e[0].afisare();
    int ult = 0;
    for(int i=1; i<n; ++i)
        if (comparare(e[ult].get_end(), e[i].get_start()) == 0) //daca data de inceput a evenimentului i este mai mare decat data de final a ultimului eveniment din lista
        {
            e[i].afisare();
            ult = i;
        }

    return 0;
}
