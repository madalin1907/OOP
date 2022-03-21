#include <bits/stdc++.h>
using namespace std;


class InterestPoint{
private:
    int nr_visitors, x, y;
public:
    InterestPoint(): nr_visitors(0), x(0), y(0) {}
    InterestPoint(int nrVisitors, int x, int y) : nr_visitors(nrVisitors), x(x), y(y) {}

    int get_visitors() const {
        return nr_visitors;
    }

    friend double distanta(InterestPoint a, InterestPoint b);

    friend istream &operator>>(istream &fin, InterestPoint &punct);
    friend ostream &operator<<(ostream &fout, InterestPoint &punct);
};


istream &operator>>(istream &fin, InterestPoint &punct){
    fin>>punct.nr_visitors>>punct.x>>punct.y;
    return fin;
}

ostream &operator<<(ostream &fout, InterestPoint &punct){
    fout<<punct.nr_visitors<<' '<<punct.x<<' '<<punct.y<<endl;
    return fout;
}





class BikeTrail{
private:
    string name, city;
    int nr;
    vector<InterestPoint>points;
public:
    BikeTrail(): nr(0) {}
    BikeTrail(string name, string city, int nr, const vector<InterestPoint> &points) :
            name(std::move(name)), city(std::move(city)), nr(nr), points(points) {}

    friend istream &operator>>(istream &fin, BikeTrail &pista);
    friend ostream &operator<<(ostream &fout, BikeTrail &pista);

    void TraseuMaxim();
    void PunctePopulare();
};


istream &operator>>(istream &fin, BikeTrail &pista){
    getline(fin, pista.name);
    getline(fin, pista.city);
    fin>>pista.nr;
    for (int i = 0; i < pista.nr; ++i){
        InterestPoint p;
        fin>>p;
        pista.points.push_back(p);
    }
    fin.get();
    return fin;
}

ostream &operator<<(ostream &fout, BikeTrail &pista){
    fout<<"Denumirea pistei: "<<pista.name<<endl;
    fout<<"Orasul: "<<pista.city<<endl;
    fout<<"Punctele de interes: \n";
    for (int i=0; i < pista.points.size(); ++i)
        fout<<i<<". "<<pista.points[i];

    return fout;
}


double distanta(InterestPoint a, InterestPoint b){
    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}


void BikeTrail::TraseuMaxim() {
    double maxim = -1;
    int i1, i2, i3;
    for (int i = 0; i < points.size()-2; ++i)
        for (int j = i+1; j < points.size()-1; ++j)
            for (int k = j+1; k < points.size(); ++k){
                double ij = distanta(points[i], points[j]);
                double ik = distanta(points[i], points[k]);
                double jk = distanta(points[j], points[k]);
                double dif = min(ij, min(ik, jk));
                double lung_traseu = ij + ik + jk - dif;
                if (lung_traseu > maxim){
                    maxim = lung_traseu;
                    if (dif == ij){
                        i1 = i;
                        i2 = k;
                        i3 = j;
                    }
                    else if (dif == ik){
                        i1 = i;
                        i2 = j;
                        i3 = k;
                    }
                    else{
                        i1 = j;
                        i2 = i;
                        i3 = k;
                    }
                }
            }
    cout<<"Lungimea maxima a unui traseu: "<<setprecision(2)<<fixed<<maxim<<endl;
    cout<<"Punctele traseului: "<<i1<<' '<<i2<<' '<<i3<<endl;
    cout<<"Suma vizitatorilor: "<<points[i1].get_visitors() + points[i2].get_visitors() + points[i3].get_visitors()<<"\n\n";
}


bool cmp(InterestPoint a, InterestPoint b){
    return (a.get_visitors() > b.get_visitors());
}

void BikeTrail::PunctePopulare() {
    vector<InterestPoint>p = points;
    sort(p.begin(), p.end(), cmp);
    double d01 = distanta(p[0], p[1]);
    double d02 = distanta(p[0], p[2]);
    double d12 = distanta(p[1], p[2]);
    double dif = max(d01, max(d02, d12));
    double lung_traseu = d01 + d02 + d12 - dif;

    cout<<"Cele mai populare trei puncte de interes (in ordinea din traseul minim): \n";
    if (dif == d01)
        cout<<p[0]<<p[2]<<p[1];
    else if (dif == d02)
        cout<<p[0]<<p[1]<<p[2];
    else
        cout<<p[1]<<p[0]<<p[2];
    cout<<"Lungimea traseului minim intre ele: "<<lung_traseu<<endl;
}


int main(){
    BikeTrail B;
    cin>>B; cout<<"\n"<<B<<"\n";

    B.TraseuMaxim();
    B.PunctePopulare();

    return 0;
}


/* input

Traseu#1
Constanta
5
102 0 0
3 1 1
22 3 2
404 1 7
1001 5 0

*/