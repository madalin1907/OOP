#include <bits/stdc++.h>
using namespace std;

template <typename T>
T add (T a, T b){
    return a + b;
}


template <typename T>
istream& operator >>(istream &is, vector<T> &v){
    v.clear();
    int n; is>>n;
    for (int i=0; i<n; i++){
        T x;
        is >> x;
        v.push_back(x);
    }
    return is;
}

template <typename T>
ostream& operator <<(ostream &os, vector<T> &v){
    for (auto i : v){
        os << i << " ";
    }
    os << "\n";
    return os;
}


int main(){
    cout<<add(2, 3)<<"\n";
    cout<<add(2.3, 3.1)<<"\n";
    cout<<add(string("123"), string("45")) <<"\n";

    vector<int>v;
    cin>>v;
    cout<<v;

    return 0;
}
