#include <bits/stdc++.h>
using namespace std;

class ConstructionProduct{
private:
    string name, unit;
    int quantity;
    float price;
public:
    ConstructionProduct(): quantity(0), price(0) {}

    ConstructionProduct(string name, string &unit, int quantity, float price):
    name(std::move(name)), unit(unit), quantity(quantity), price(price) {};

    friend istream &operator>>(istream &fin, ConstructionProduct &product);
    friend ostream &operator<<(ostream &fout, ConstructionProduct &product);

    ConstructionProduct operator++(){
        quantity++;
        return *this;
    }
    ConstructionProduct operator++(int){
        ConstructionProduct copy = *this;
        ++quantity;
        return copy;
    }
    ConstructionProduct operator+=(int crestere){
        quantity += crestere;
        return *this;
    }

    friend void chitanta(vector<ConstructionProduct>v);
};

istream &operator>>(istream &fin, ConstructionProduct &product) {
    cout<<"Numele materialului:";
    getline(fin, product.name);
    cout<<"Cantitate:";
    fin>>product.quantity;
    fin.get();
    cout<<"Unitate de masura:";
    getline(fin, product.unit);
    cout<<"Pret pe unitate:";
    fin>>product.price;
    fin.get();

    return fin;
}

ostream &operator<<(ostream &fout, ConstructionProduct &product) {
    fout<<"Numele materialului: "<<product.name<<"\n";
    fout<<"Cantitate: "<<product.quantity<<"\n";
    fout<<"Unitate de masura: "<<product.unit<<"\n";
    fout<<"Pret pe unitate: "<<product.price<<"\n";

    return fout;
}


void chitanta(vector<ConstructionProduct>v) {
    cout<<"Chitanta renovare:\n";
    float s = 0;
    for (int i = 0; i < v.size(); i++){
        cout<<i+1<<". "<<v[i].name<<" ("<<v[i].unit<<") x "<<v[i].quantity<<endl;
        float pret = (float) v[i].quantity * v[i].price;
        s += pret;
        cout<<"  "<<v[i].quantity<<" x "<<setprecision(2)<<fixed<<v[i].price<<" = "<<pret<<" RON\n";
    }
    cout<<"---\n  Total: "<<setprecision(2)<<fixed<<s<<" RON\n\n";
}



int main(){
    vector<ConstructionProduct>materiale;
    int n;
    cout<<"Numarul de materiale:";
    cin>>n; cin.get();

    for (int i=0; i<n; i++){
        ConstructionProduct p;
        cin>>p;
        materiale.push_back(p);
    }

    materiale[0] += 20;
    ++materiale[1];
    materiale[2]++;

    chitanta(materiale);

    return 0;
}