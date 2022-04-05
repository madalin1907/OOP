#include <iostream>
#include <cmath>
using namespace std;

int piese(int arie){
    if (arie == 4){
        return 1;
    }

    int a = piese(arie / 4);
    int b = piese(arie / 4);
    int c = piese(arie / 4);
    int d = piese(arie / 4);

    return a + b + c + d + 1;
}

int main(){
    int n;
    cin >> n;

    if (n == 1)
        cout<<1;
    else {
        int l = pow(4, n);
        cout << "Suprafata ramasa se acopera cu " << piese(l) << " piese.";
    }

    return 0;
}