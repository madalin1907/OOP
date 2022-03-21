#include <bits/stdc++.h>
using namespace std;


class Coords{
private:
    int x, y;
public:
    Coords() : x(0), y(0) {}
    Coords(int x, int y) : x(x), y(y) {}

    friend istream &operator>>(istream &fin, Coords &c){
        fin>>c.x>>c.y;
        return fin;
    }
    friend ostream &operator<<(ostream &fout, Coords &c){
        fout<<c.x<<" "<<c.y;
        return fout;
    }

};


class Queue{
private:
    int lungime_coada;
    vector<Coords>Coordonate;
public:
    Queue(): lungime_coada(0) {}

    Queue(int lungimeCoada, const vector<Coords> &coordonate):
        lungime_coada(lungimeCoada), Coordonate(coordonate) {}

    friend istream &operator>>(istream &fin, Queue &q){
        fin>>q.lungime_coada;
        for (int i = 0; i < q.lungime_coada; i++){
            Coords c;
            fin>>c;
            q.Coordonate.push_back(c);
        }
        return fin;
    }

    friend ostream &operator<<(ostream &fout, Queue &q){
        for (auto i : q.Coordonate)
            fout<<i;
        return fout;
    }
};


class Maze{
private:
    vector < vector<int> >matrix{100, vector < int > (100, 0)};
    Coords start, end;
    int n;
    Queue q;

public:
    Maze(): n(0) {}

    Maze(const vector<vector<int>> &matrix, const Coords &start, const Coords &anEnd, int n, const Queue &q) :
        matrix(matrix), start(start), end(anEnd), n(n), q(q) {}
};


int main(){

    return 0;
}

/*
5
0 0
4 0
5
1 0
1 2
2 2
3 2
4 1
*/