#include <iostream>
using namespace std;

int comparare(int a, int b, int d)
{
    int num = a*d - b;
    if (num < 0)
        return -1;
    else if (num == 0)
        return 0;
    else
        return 1;

}

int main()
{
    int a, b, k=2;
    cin>>a>>b;
    cout<<a<<"/"<<b<<" = ";
    while(a != 0)
    {
        if (comparare(a, b, k) == 1)
        {
            a -= b/k;
            cout<<"1/"<<k<<" + ";
        }
        else if (comparare(a, b, k) == 0)
        {
            a -= b/k;
            cout<<"1/"<<k;
        }
        k++;
    }

    return 0;
}
