#include <iostream>
using namespace std;

int main(){
    int N;
    cin>>N;

    if (N == 1)
        cout<<1;
    else if (N == 2)
        cout<<2;
    else{
        int a = 1, b = 2;
        for (int i = 1; i <= N-2; ++i){
            swap(a, b);
            b += a;
        }
        cout<<b;
    }

    // 1 2 3 5 8 13 21 34 55 89
    return 0;
}
