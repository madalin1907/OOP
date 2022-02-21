#include <iostream>
using namespace std;

int main()
{
    int n, v1[100], v2[100];
    cin>>n;
    for (int i=1; i<=n; i++)
        cin>>v1[i];
    for (int i=1; i<=n; i++)
        cin>>v2[i];

    for (int i=1; i<n; i++)
        for (int j=i+1; j<=n; j++)
        {
            if (v1[i]>v1[j])
                swap(v1[i], v1[j]);
            if (v2[i]>v2[j])
                swap(v2[i], v2[j]);
        }

    for (int i=1; i<=n; i++)
        cout<<v1[i]<<' ';
    cout<<endl;
    for (int i=1; i<=n; i++)
        cout<<v2[i]<<' ';

}
