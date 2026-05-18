#ifndef AUTOMOBILE_H
#define AUTOMOBILE_H

#include <iostream>
#include <string>
using namespace std;

class Automobile {
private:
    string make;
    string variant;
    int manufactureYear;
    double displacement;
    string paintColor;
    string gearType;

    static int totalAutos;

public:

    static const int EARLIEST_YEAR = 1970;

    Automobile() {
        make = "Unknown";
        variant = "Unknown";
        manufactureYear = 2020;
        displacement = 1000.0;
        paintColor = "White";
        gearType = "Manual";
        totalAutos++;
    }

    Automobile(string make, string variant, int yr, double cc,
               string clr, string gear) {
        this->make = make;
        this->variant = variant;
        this->manufactureYear = (yr >= EARLIEST_YEAR) ? yr : EARLIEST_YEAR;
        this->displacement = cc;
        this->paintColor = clr;
        this->gearType = gear;
        totalAutos++;
    }

    Automobile(const Automobile& src) {
        make = src.make;
        variant = src.variant;
        manufactureYear = src.manufactureYear;
        displacement = src.displacement;
        paintColor = src.paintColor;
        gearType = src.gearType;
        totalAutos++;
    }

    void setMake(string b) { make = b; }
    void setVariant(string m) { variant = m; }
    void setManufactureYear(int y) { if (y >= EARLIEST_YEAR) manufactureYear = y; }
    void setDisplacement(double ec) { displacement = ec; }
    void setPaintColor(string c) { paintColor = c; }
    void setGearType(string t) { gearType = t; }

    string getMake() const { return make; }
    string getVariant() const { return variant; }
    int getManufactureYear() const { return manufactureYear; }
    double getDisplacement() const { return displacement; }
    string getPaintColor() const { return paintColor; }
    string getGearType() const { return gearType; }

    static int getTotalAutos() { return totalAutos; }
    static void clearAutoCount() { totalAutos = 0; }

    void showAutoInfo() const {
        cout << "  Make        : " << make << endl;
        cout << "  Variant     : " << variant << endl;
        cout << "  Year        : " << manufactureYear << endl;
        cout << "  Displacement: " << displacement << " CC" << endl;
        cout << "  Color       : " << paintColor << endl;
        cout << "  Gear Type   : " << gearType << endl;
    }

    bool checkMake(const string& b) const {
        return make == b;
    }

    bool checkVariant(const string& m) const {
        return variant == m;
    }

    int computeAge() const {
        return 2026 - manufactureYear;
    }
};

int Automobile::totalAutos = 0;

#endif
