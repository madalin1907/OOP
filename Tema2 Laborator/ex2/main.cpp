// 2. Filme

#include <iostream>
using namespace std;

class Film{
private:
    string titlu;
    int likes;
public:
    void citeste(){
        cin.get();
        cout<<endl<<"Titlul:";
        getline(cin, titlu);
        cout<<"Numarul de like-uri:";
        cin>>likes;
    }
    int getlikes(){
        return likes;
    }
    void afisare(){
        cout<<titlu<<endl;
    }
};

void afisarePopulare(int n, Film filme[], int k)
{
    for (int i=0; i<n-1; i++)
        for (int j=i+1; j<n; j++)
            if (filme[i].getlikes() < filme[j].getlikes())
                swap(filme[i], filme[j]);

    for (int i=0; i<k; i++)
        filme[i].afisare();
}

int main()
{
    int n, k;
    Film filme[30];
    cout<<"Numarul de filme:"; cin>>n;
    for (int i=0; i<n; i++)
        filme[i].citeste();
    cout<<endl<<"k=";
    cin>>k;
    afisarePopulare(n, filme, k);
    return 0;
}
