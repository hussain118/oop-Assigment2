#ifndef REGION2_H
#define REGION2_H

#include "IRenderable.h"
#include <iostream>
#include <string>
using namespace std;

class Region : public IRenderable {
private:
    string cityName;
    string provinceName;
    string nationName;
    string zipCode;
    double lat;
    double lng;

public:
    Region() {
        cityName = "Karachi"; provinceName = "Sindh";
        nationName = "Pakistan"; zipCode = "75000";
        lat = 24.8607; lng = 67.0011;
    }

    Region(string city, string province, string nation, string zip) {
        this->cityName = city; this->provinceName = province;
        this->nationName = nation; this->zipCode = zip;
        lat = 0.0; lng = 0.0;
    }

    Region(const Region& src) {
        cityName = src.cityName; provinceName = src.provinceName;
        nationName = src.nationName; zipCode = src.zipCode;
        lat = src.lat; lng = src.lng;
    }

    virtual ~Region() {}

    void setCityName(string c)      { cityName = c; }
    void setProvinceName(string p)  { provinceName = p; }
    void setNationName(string co)   { nationName = co; }
    void setZipCode(string pc)      { zipCode = pc; }
    void setGeoCoords(double latitude, double longitude) { lat = latitude; lng = longitude; }

    string getCityName()     const { return cityName; }
    string getProvinceName() const { return provinceName; }
    string getNationName()   const { return nationName; }
    string getZipCode()      const { return zipCode; }
    double getLat()          const { return lat; }
    double getLng()          const { return lng; }

    virtual void renderInfo() const override {
        cout << "  Region: " << cityName << ", " << provinceName
             << ", " << nationName << " (" << zipCode << ")" << endl;
    }

    virtual void renderBrief() const override {
        cout << "  " << cityName << ", " << provinceName << endl;
    }

    string buildFullAddr() const {
        return cityName + ", " + provinceName + ", " + nationName;
    }

    bool isSameCityAs(const Region& other) const { return cityName == other.cityName; }

    bool operator==(const Region& other) const {
        return cityName == other.cityName && provinceName == other.provinceName;
    }

    bool operator!=(const Region& other) const {
        return !(*this == other);
    }

    friend ostream& operator<<(ostream& os, const Region& r);
};

ostream& operator<<(ostream& os, const Region& r) {
    os << r.cityName << ", " << r.provinceName << ", " << r.nationName;
    return os;
}

#endif

#ifndef CHATNOTE2_H
#define CHATNOTE2_H

#include "IRenderable.h"
#include <iostream>
#include <string>
using namespace std;

class ChatNote : public IRenderable {
private:
    string noteID;
    string fromID;
    string toID;
    string body;
    string sentAt;
    bool   opened;

    static int noteTotal;

public:
    ChatNote() {
        noteTotal++;
        noteID = "CHT" + to_string(noteTotal);
        fromID = ""; toID = "";
        body = ""; sentAt = "2026-01-01 00:00";
        opened = false;
    }

    ChatNote(string from, string to, string text, string time) {
        noteTotal++;
        noteID  = "CHT" + to_string(noteTotal);
        fromID  = from;
        toID    = to;
        body    = text;
        sentAt  = time;
        opened  = false;
    }

    ChatNote(const ChatNote& src) {
        noteTotal++;
        noteID  = "CHT" + to_string(noteTotal);
        fromID  = src.fromID;
        toID    = src.toID;
        body    = src.body;
        sentAt  = src.sentAt;
        opened  = src.opened;
    }

    virtual ~ChatNote() {}

    void setFromID(string s)  { fromID = s; }
    void setToID(string r)    { toID = r; }
    void setBody(string c)    { body = c; }
    void setSentAt(string t)  { sentAt = t; }
    void flagAsOpened()       { opened = true; }

    string getNoteID()   const { return noteID; }
    string getFromID()   const { return fromID; }
    string getToID()     const { return toID; }
    string getBody()     const { return body; }
    string getSentAt()   const { return sentAt; }
    bool   getOpened()   const { return opened; }

    static int getNoteTotal() { return noteTotal; }

    virtual void renderInfo() const override {
        cout << "  [" << sentAt << "] " << fromID
             << " -> " << toID << endl;
        cout << "  Body   : " << body << endl;
        cout << "  Status : " << (opened ? "Opened" : "Unread") << endl;
    }

    virtual void renderBrief() const override {
        cout << "  CHT[" << noteID << "]: " << body.substr(0, 40) << "..." << endl;
    }

    bool operator==(const ChatNote& other) const {
        return fromID == other.fromID && body == other.body;
    }

    ChatNote operator+(const ChatNote& other) const {
        ChatNote combined;
        combined.fromID = this->fromID;
        combined.toID   = this->toID;
        combined.body   = this->body + " | " + other.body;
        combined.sentAt = other.sentAt;
        return combined;
    }

    friend ostream& operator<<(ostream& os, const ChatNote& n);
};

int ChatNote::noteTotal = 0;

ostream& operator<<(ostream& os, const ChatNote& n) {
    os << "CHT[" << n.noteID << "] from " << n.fromID
       << ": " << n.body;
    return os;
}

#endif
