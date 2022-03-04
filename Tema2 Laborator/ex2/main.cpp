// 2. Filme

#include <iostream>
using namespace std;

class Film{
private:
    string titlu;
    int likes;
public:
    Film(){
        titlu = "";
        likes = 0;
    }
    Film(string _titlu, int _likes){
        titlu = _titlu;
        likes = _likes;
    }

    int getlikes(){
        return likes;
    }

    void citire(){
        cin.get();
        cout<<endl<<"Titlul:";
        getline(cin, titlu);
        cout<<"Numarul de like-uri:";
        cin>>likes;
    }
    void afisare(){
        cout<<titlu<<endl;
    }
};

void afisarePopulare(int n, Film filme[], int k)
{
    cout<<"Cele mai populare "<<k<<" filme sunt:"<<endl;
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
    cout<<"Numarul de filme:"; cin>>n;
    Film filme[n];
    for (int i=0; i<n; i++)
        filme[i].citire();
    cout<<endl<<"k=";
    cin>>k;
    afisarePopulare(n, filme, k);
    return 0;
}
