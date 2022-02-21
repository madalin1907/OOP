#include <iostream>
#include <cmath>
using namespace std;

struct data
{
    int an, luna, zi;
} v[2];

int main()
{
    cin>>v[0].an>>v[0].luna>>v[0].zi;
    cin>>v[1].an>>v[1].luna>>v[1].zi;
    int an = 2022;
    int luna = 2;
    int zi = 15;

    if (v[0].an == v[1].an)
    {
        if (v[0].luna == v[1].luna)
        {
            if (v[0].zi == v[1].zi)
            {
                cout<<"a) Cele doua date sunt identice."<<endl;
            }
            else if (v[0].zi > v[1].zi)
            {
                cout<<"a) Prima data este mai mare."<<endl;
            }
            else
            {
                cout<<"a) A doua data este mai mare."<<endl;
            }
        }
        else if (v[0].luna > v[1].luna)
        {
            cout<<"a) Prima data este mai mare."<<endl;
        }
        else
        {
            cout<<"a) A doua data este mai mare."<<endl;
        }
    }
    else if (v[0].an > v[1].an)
    {
        cout<<"a) Prima data este mai mare."<<endl;
    }
    else
    {
        cout<<"a) A doua data este mai mare."<<endl;
    }



    if (abs(an - v[0].an) == abs(an - v[1].an))
    {
        if (abs(luna - v[0].luna) == abs (luna - v[1].luna))
        {
            if (abs(zi - v[0].zi) == abs(zi - v[1].zi))
            {
                cout<<"b) Cele doua date sunt la fel de apropiate de data de azi."<<endl;
            }
            else if (abs(zi - v[0].zi) < abs(zi - v[1].zi))
            {
                cout<<"b) Prima data este mai apropiata de ziua de azi."<<endl;
            }
            else
            {
                cout<<"b) A doua data este mai apropiata de ziua de azi."<<endl;
            }
        }
        else if (abs(luna - v[0].luna) < abs (luna - v[1].luna))
        {
            cout<<"b) Prima data este mai apropiata de ziua de azi."<<endl;
        }
        else
        {
            cout<<"b) A doua data este mai apropiata de ziua de azi."<<endl;
        }
    }
    else if (abs(an - v[0].an) < abs(an - v[1].an))
    {
        cout<<"b) Prima data este mai apropiata de ziua de azi."<<endl;
    }
    else
    {
        cout<<"b) A doua data este mai apropiata de ziua de azi."<<endl;
    }

    return 0;
}
