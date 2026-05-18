#ifndef AUTOMOBILE2_H
#define AUTOMOBILE2_H

#include "IRenderable.h"
#include "IFilterable.h"
#include "IValuable.h"
#include <iostream>
#include <string>
using namespace std;

class Automobile : public IRenderable, public IFilterable {
protected:
    string autoTag;
    string make;
    string variant;
    int    manufactureYear;
    double displacement;
    string paintColor;
    string gearType;
    string powerSource;

    static int totalAutos;
    static const int EARLIEST_YEAR = 1970;

public:

    Automobile() {
        totalAutos++;
        autoTag       = "AUT" + to_string(totalAutos);
        make          = "Unknown";
        variant       = "Unknown";
        manufactureYear = 2020;
        displacement  = 1000.0;
        paintColor    = "White";
        gearType      = "Manual";
        powerSource   = "Petrol";
    }

    Automobile(string make, string variant, int yr, double cc,
               string clr, string gear, string fuel = "Petrol") {
        totalAutos++;
        autoTag            = "AUT" + to_string(totalAutos);
        this->make         = make;
        this->variant      = variant;
        this->manufactureYear = (yr >= EARLIEST_YEAR) ? yr : EARLIEST_YEAR;
        displacement       = cc;
        this->paintColor   = clr;
        this->gearType     = gear;
        powerSource        = fuel;
    }

    Automobile(const Automobile& src) {
        totalAutos++;
        autoTag         = "AUT" + to_string(totalAutos);
        make            = src.make;
        variant         = src.variant;
        manufactureYear = src.manufactureYear;
        displacement    = src.displacement;
        paintColor      = src.paintColor;
        gearType        = src.gearType;
        powerSource     = src.powerSource;
    }

    virtual ~Automobile() {}

    void setMake(string b)          { make = b; }
    void setVariant(string m)       { variant = m; }
    void setManufactureYear(int y)  { if (y >= EARLIEST_YEAR) manufactureYear = y; }
    void setDisplacement(double e)  { displacement = e; }
    void setPaintColor(string c)    { paintColor = c; }
    void setGearType(string t)      { gearType = t; }
    void setPowerSource(string f)   { powerSource = f; }

    string getAutoTag()        const { return autoTag; }
    string getMake()           const { return make; }
    string getVariant()        const { return variant; }
    int    getManufactureYear()const { return manufactureYear; }
    double getDisplacement()   const { return displacement; }
    string getPaintColor()     const { return paintColor; }
    string getGearType()       const { return gearType; }
    string getPowerSource()    const { return powerSource; }

    static int getTotalAutos() { return totalAutos; }

    virtual void renderInfo() const override {
        cout << "  [Automobile] " << make << " " << variant
             << " (" << manufactureYear << ") | " << displacement << "CC | " << paintColor << endl;
    }

    virtual void renderBrief() const override {
        cout << "  " << make << " " << variant << " " << manufactureYear << endl;
    }

    virtual bool checkKeyword(const string& term) const override {
        return make.find(term) != string::npos ||
               variant.find(term) != string::npos ||
               paintColor.find(term) != string::npos;
    }

    virtual string getIndexedContent() const override {
        return make + " " + variant + " " + to_string(manufactureYear) + " " + paintColor;
    }

    virtual string getCategory() const { return "Automobile"; }

    virtual double calcInsurance() const { return displacement * 0.5; }

    bool checkMake(const string& b)    const { return make == b; }
    bool checkVariant(const string& m) const { return variant == m; }
    int  computeAge()                  const { return 2026 - manufactureYear; }

    bool operator==(const Automobile& other) const {
        return make == other.make && variant == other.variant && manufactureYear == other.manufactureYear;
    }

    bool operator<(const Automobile& other) const {
        return manufactureYear < other.manufactureYear;
    }

    bool operator>(const Automobile& other) const {
        return manufactureYear > other.manufactureYear;
    }

    friend ostream& operator<<(ostream& os, const Automobile& a);
};

int Automobile::totalAutos = 0;

ostream& operator<<(ostream& os, const Automobile& a) {
    os << a.make << " " << a.variant << " " << a.manufactureYear
       << " | " << a.displacement << "CC | " << a.paintColor
       << " | " << a.gearType << " | " << a.powerSource;
    return os;
}

class MotorCar : public Automobile {
private:
    int    doorCount;
    string chassis;
    bool   hasClimateCtrl;
    bool   hasMoonroof;
    int    seatCapacity;

public:

    MotorCar() : Automobile() {
        doorCount      = 4;
        chassis        = "Sedan";
        hasClimateCtrl = true;
        hasMoonroof    = false;
        seatCapacity   = 5;
    }

    MotorCar(string make, string variant, int yr, double cc,
             string clr, string gear, string fuel,
             int doors, string chassis, bool ac, bool moonroof, int seats)
        : Automobile(make, variant, yr, cc, clr, gear, fuel) {
        this->doorCount      = doors;
        this->chassis        = chassis;
        this->hasClimateCtrl = ac;
        this->hasMoonroof    = moonroof;
        this->seatCapacity   = seats;
    }

    MotorCar(const MotorCar& src) : Automobile(src) {
        doorCount      = src.doorCount;
        chassis        = src.chassis;
        hasClimateCtrl = src.hasClimateCtrl;
        hasMoonroof    = src.hasMoonroof;
        seatCapacity   = src.seatCapacity;
    }

    virtual ~MotorCar() {}

    void setDoorCount(int d)      { doorCount = d; }
    void setChassis(string b)     { chassis = b; }
    void setClimateCtrl(bool a)   { hasClimateCtrl = a; }
    void setMoonroof(bool s)      { hasMoonroof = s; }
    void setSeatCapacity(int s)   { seatCapacity = s; }
    int    getDoorCount()    const { return doorCount; }
    string getChassis()      const { return chassis; }
    bool   getClimateCtrl()  const { return hasClimateCtrl; }
    bool   getMoonroof()     const { return hasMoonroof; }
    int    getSeatCapacity() const { return seatCapacity; }

    virtual void renderInfo() const override {
        cout << "  [MOTORCAR] " << make << " " << variant << " (" << manufactureYear << ")" << endl;
        cout << "    Engine    : " << displacement << " CC | " << powerSource << endl;
        cout << "    Color     : " << paintColor << " | " << gearType << endl;
        cout << "    Chassis   : " << chassis << " | Doors: " << doorCount
             << " | Seats: " << seatCapacity << endl;
        cout << "    Climate   : " << (hasClimateCtrl ? "Yes" : "No")
             << " | Moonroof: " << (hasMoonroof ? "Yes" : "No") << endl;
    }

    virtual void renderBrief() const override {
        cout << "  MOTORCAR: " << make << " " << variant << " " << manufactureYear
             << " | " << chassis << " | " << seatCapacity << " seats" << endl;
    }

    virtual string getCategory() const override { return "MotorCar"; }

    virtual double calcInsurance() const override {
        double base = displacement * 0.8;
        return hasMoonroof ? base * 1.1 : base;
    }

    bool operator==(const MotorCar& other) const {
        return make == other.make && variant == other.variant
            && manufactureYear == other.manufactureYear && chassis == other.chassis;
    }

    string operator+(const MotorCar& other) const {
        return "Comparison Report: " + make + " " + variant
               + " vs " + other.make + " " + other.variant;
    }

    friend bool isPremiumCar(const MotorCar& c);
};

bool isPremiumCar(const MotorCar& c) {

    return c.displacement >= 2000 && c.seatCapacity >= 5;
}

class Motorcycle : public Automobile {
private:
    string rideStyle;
    bool   hasWindshield;
    string secondaryMake;
    int    cylinderCount;
    bool   electricPowered;

public:

    Motorcycle() : Automobile() {
        rideStyle      = "Standard";
        hasWindshield  = false;
        secondaryMake  = "None";
        cylinderCount  = 1;
        electricPowered = false;
    }

    Motorcycle(string make, string variant, int yr, double cc,
               string clr, string gear,
               string rStyle, bool windshield, int cylinders)
        : Automobile(make, variant, yr, cc, clr, gear, "Petrol") {
        this->rideStyle      = rStyle;
        this->hasWindshield  = windshield;
        this->cylinderCount  = cylinders;
        this->secondaryMake  = "None";
        this->electricPowered = (cc == 0);
    }

    Motorcycle(const Motorcycle& src) : Automobile(src) {
        rideStyle       = src.rideStyle;
        hasWindshield   = src.hasWindshield;
        secondaryMake   = src.secondaryMake;
        cylinderCount   = src.cylinderCount;
        electricPowered = src.electricPowered;
    }

    virtual ~Motorcycle() {}

    void setRideStyle(string t)     { rideStyle = t; }
    void setWindshield(bool f)      { hasWindshield = f; }
    void setCylinderCount(int c)    { cylinderCount = c; }
    void setElectricPowered(bool e) { electricPowered = e; }
    string getRideStyle()      const { return rideStyle; }
    bool   getWindshield()     const { return hasWindshield; }
    int    getCylinderCount()  const { return cylinderCount; }
    bool   getElectricPowered()const { return electricPowered; }

    virtual void renderInfo() const override {
        cout << "  [MOTORCYCLE] " << make << " " << variant << " (" << manufactureYear << ")" << endl;
        cout << "    Engine     : " << displacement << " CC | " << powerSource << endl;
        cout << "    Color      : " << paintColor << " | " << gearType << endl;
        cout << "    Ride Style : " << rideStyle << " | Cylinders: " << cylinderCount << endl;
        cout << "    Windshield : " << (hasWindshield ? "Yes" : "No")
             << " | Electric: " << (electricPowered ? "Yes" : "No") << endl;
    }

    virtual void renderBrief() const override {
        cout << "  MOTORCYCLE: " << make << " " << variant << " " << manufactureYear
             << " | " << rideStyle << " | " << displacement << "CC" << endl;
    }

    virtual string getCategory() const override { return "Motorcycle"; }

    virtual double calcInsurance() const override {
        return displacement * 0.3;
    }

    bool operator==(const Motorcycle& other) const {
        return make == other.make && variant == other.variant && manufactureYear == other.manufactureYear;
    }

    friend ostream& operator<<(ostream& os, const Motorcycle& m);
};

ostream& operator<<(ostream& os, const Motorcycle& m) {
    os << "Motorcycle: " << m.make << " " << m.variant << " " << m.manufactureYear
       << " | " << m.rideStyle << " | " << m.displacement << "CC";
    return os;
}

#endif
