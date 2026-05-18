#ifndef REGION_H
#define REGION_H

#include <iostream>
#include <string>
using namespace std;

class Region {
private:
    string cityName;
    string provinceName;
    string nationName;
    string zipCode;
    double lat;
    double lng;

public:

    Region() {
        cityName = "Karachi";
        provinceName = "Sindh";
        nationName = "Pakistan";
        zipCode = "75000";
        lat = 24.8607;
        lng = 67.0011;
    }

    Region(string city, string province, string nation, string zip) {
        this->cityName = city;
        this->provinceName = province;
        this->nationName = nation;
        this->zipCode = zip;
        this->lat = 0.0;
        this->lng = 0.0;
    }

    Region(const Region& src) {
        cityName = src.cityName;
        provinceName = src.provinceName;
        nationName = src.nationName;
        zipCode = src.zipCode;
        lat = src.lat;
        lng = src.lng;
    }

    void setCityName(string c) { cityName = c; }
    void setProvinceName(string p) { provinceName = p; }
    void setNationName(string co) { nationName = co; }
    void setZipCode(string pc) { zipCode = pc; }
    void setGeoCoords(double latitude, double longitude) { lat = latitude; lng = longitude; }

    string getCityName() const { return cityName; }
    string getProvinceName() const { return provinceName; }
    string getNationName() const { return nationName; }
    string getZipCode() const { return zipCode; }
    double getLat() const { return lat; }
    double getLng() const { return lng; }

    void showRegion() const {
        cout << cityName << ", " << provinceName << ", " << nationName << " (" << zipCode << ")" << endl;
    }

    bool isSameCityAs(const Region& other) const {
        return cityName == other.cityName;
    }

    bool isSameProvinceAs(const Region& other) const {
        return provinceName == other.provinceName;
    }

    string buildFullAddr() const {
        return cityName + ", " + provinceName + ", " + nationName;
    }
};

#endif
