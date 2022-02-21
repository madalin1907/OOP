#include <iostream>
using namespace std;

struct fractie{
    int a, b;
    float rez;
}sol[101];

int main()
{
    int n, v[101], k = 0;
    cin>>n;
    for (int i=1; i<=n; i++)
        cin>>v[i];

    for (int i=1; i<n; i++)
        for (int j=i+1; j<=n; j++)
            if (v[i] < v[j])
                swap(v[i], v[j]);

    cout<<"a) ";
    for (int i=1; i<n; i++)
        for (int j=i+1; j<=n; j++)
        {
            int ok = 1;
            for (int c=1; c<=k; c++)
                if (sol[c].rez == (float)v[i]/v[j])
                {
                    ok = 0;
                    break;
                }
            if (ok == 1)
            {
                cout<<v[i]<<"/"<<v[j]<<"  ";
                k++;
                sol[k].a = v[i];
                sol[k].b = v[j];
                sol[k].rez = (float)v[i] / v[j];
            }
        }


    for(int i=1; i<k; i++)
        for(int j=i+1; j<=k; j++)
            if (sol[i].rez > sol[j].rez)
                swap(sol[i], sol[j]);

    cout<<endl<<"b) ";
    for (int i=1; i<=k; i++)
        cout<<sol[i].a<<"/"<<sol[i].b<<"  ";

    return 0;
}
