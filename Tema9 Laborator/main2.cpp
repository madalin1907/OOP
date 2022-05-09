#include <bits/stdc++.h>
using namespace std;



class BasePainting{
protected:
    double width, height, ratio;
public:
    BasePainting();

    BasePainting(double width, double ratio);

    double oilQuantity();

    virtual double paintingArea() = 0;
};

BasePainting::BasePainting() : width(0), height(0), ratio(0) {}

BasePainting::BasePainting(double width, double ratio) : width(width), ratio(ratio), height(width/ratio){}

double BasePainting::oilQuantity() {
    return paintingArea() * 0.1;
}



class Miniature : public BasePainting{
public:
    Miniature() = default;

    Miniature(double width, double ratio);

    double paintingArea() override;
};

Miniature::Miniature(double _width, double _ratio){
    try{
        if (_width > 10)
            throw 1;
        if (_ratio < 1 || _ratio > 3)
            throw 2;
        width = _width;
        ratio = _ratio;
        height = _width / _ratio;
    }
    catch(int errorCode){
        if (errorCode == 1)
            cout << "Width can't be greater than 10cm for a Miniature.\n";
        else if (errorCode == 2)
            cout << "Ratio must be between 1 and 3 for a Miniature.\n";
    }
}

double Miniature::paintingArea() {
    return width * height;
}



class Painting : public BasePainting{
public:
    Painting() = default;

    Painting(double width, double ratio);

    double paintingArea() override;
};

Painting::Painting(double _width, double _ratio){
    try{
        if (_width < 19 || _width > 57)
            throw 1;
        if (_ratio < 0.618 || _ratio > 1.618)
            throw 2;
        width = _width;
        ratio = _ratio;
        height = _width / _ratio;
    }
    catch(int errorCode){
        if (errorCode == 1)
            cout << "Width must be between 19cm and 57cm for a Painting.\n";
        else if (errorCode == 2)
            cout << "Ratio must be between 0.618 and 1.618 for a Painting.\n";
    }
}

double Painting::paintingArea() {
    return width * height;
}



class WallPainting : public BasePainting{
public:
    WallPainting() = default;

    WallPainting(double width, double ratio);

    double paintingArea() override;
};

WallPainting::WallPainting(double _width, double _ratio){
    try{
        if (_width < 100 || _width > 1000)
            throw 1;
        if (_ratio < 1 || _ratio > 10)
            throw 2;
        width = _width;
        ratio = _ratio;
        height = _width / _ratio;
    }
    catch(int errorCode){
        if (errorCode == 1)
            cout << "Width must be between 100cm (1m) and 1000cm (10m) for a Wall Painting.\n";
        else if (errorCode == 2)
            cout << "Ratio must be between 1 and 10 for a Wall Painting.\n";
    }
}

double WallPainting::paintingArea() {
    return width * height;
}

int main() {
    Miniature miniature(10, 2);
    cout << miniature.oilQuantity() << " mL/cm3\n";

    Painting painting(30, 1.5);
    cout << painting.oilQuantity() << " mL/cm3\n";

    WallPainting wallPainting(200, 2);
    cout << wallPainting.oilQuantity() << " mL/cm3\n";

    return 0;
}