#ifndef ADPOST2_H
#define ADPOST2_H

#include "Automobile2.h"
#include "RegionChat2.h"
#include "IValuable.h"
#include <iostream>
#include <string>
using namespace std;

class AdPost : public IRenderable, public IFilterable, public IValuable {
private:
    string   postID;
    Automobile* automobile;
    Region   region;
    ChatNote notes[20];
    int      noteCount;

    string dealerTag;
    double listedCost;
    int    odometerKm;
    string vehicleState;
    string summary;
    bool   isConfirmed;
    bool   isLive;

    static int totalPosts;
    static int livePosts;
    static const double FLOOR_PRICE;

public:

    AdPost() : region() {
        totalPosts++;
        postID       = "ADP" + to_string(totalPosts);
        automobile   = nullptr;
        dealerTag    = "";
        listedCost   = FLOOR_PRICE;
        odometerKm   = 0;
        vehicleState = "Used";
        summary      = "No summary.";
        isConfirmed  = false;
        isLive       = false;
        noteCount    = 0;
        livePosts++;
    }

    AdPost(Automobile* auto_, Region reg, string dTag, double cost,
           int km, string state, string desc)
        : region(reg) {
        totalPosts++;
        postID       = "ADP" + to_string(totalPosts);
        automobile   = auto_;
        dealerTag    = dTag;
        listedCost   = (cost >= FLOOR_PRICE) ? cost : FLOOR_PRICE;
        odometerKm   = km;
        vehicleState = state;
        summary      = desc;
        isConfirmed  = false;
        isLive       = true;
        noteCount    = 0;
        livePosts++;
    }

    AdPost(const AdPost& src) : region(src.region) {
        totalPosts++;
        postID       = "ADP" + to_string(totalPosts);
        automobile   = src.automobile;
        dealerTag    = src.dealerTag;
        listedCost   = src.listedCost;
        odometerKm   = src.odometerKm;
        vehicleState = src.vehicleState;
        summary      = src.summary;
        isConfirmed  = false;
        isLive       = src.isLive;
        noteCount    = 0;
        livePosts++;
    }

    ~AdPost() { if (isLive && livePosts > 0) livePosts--; }

    void setConfirmed(bool a)      { isConfirmed = a; }
    void setLive(bool a)           { isLive = a; }
    void setOdometerKm(int m)      { odometerKm = m; }
    void setVehicleState(string c) { vehicleState = c; }
    void setSummary(string d)      { summary = d; }

    string     getPostID()       const { return postID; }
    string     getDealerTag()    const { return dealerTag; }
    double     getListedCost()   const { return listedCost; }
    int        getOdometerKm()   const { return odometerKm; }
    string     getVehicleState() const { return vehicleState; }
    bool       getIsConfirmed()  const { return isConfirmed; }
    bool       getIsLive()       const { return isLive; }
    Region     getRegion()       const { return region; }
    Automobile* getAutomobile()  const { return automobile; }

    static int getTotalPosts()  { return totalPosts; }
    static int getLivePosts()   { return livePosts; }

    virtual double fetchCost() const override { return listedCost; }
    virtual void   assignCost(double p) override { if (p >= FLOOR_PRICE) listedCost = p; }
    virtual bool   fitsWithinBudget(double limit) const override { return listedCost <= limit; }

    virtual void renderInfo() const override {
        cout << "\n========================================" << endl;
        cout << "  Post ID    : " << postID << endl;
        cout << "  Dealer Tag : " << dealerTag << endl;
        cout << "  Cost       : PKR " << listedCost << endl;
        cout << "  Odometer   : " << odometerKm << " km" << endl;
        cout << "  State      : " << vehicleState << endl;
        cout << "  Status     : " << (isConfirmed ? "Confirmed" : "Pending") << endl;
        cout << "  Summary    : " << summary << endl;
        if (automobile) {
            cout << "--- " << automobile->getCategory() << " Info ---" << endl;
            automobile->renderInfo();
        }
        cout << "--- Region ---" << endl;
        region.renderInfo();
        cout << "========================================" << endl;
    }

    virtual void renderBrief() const override {
        cout << "  [" << postID << "] ";
        if (automobile) automobile->renderBrief();
        cout << "     PKR " << listedCost << " | " << odometerKm << " km | " << vehicleState << endl;
    }

    virtual bool checkKeyword(const string& kw) const override {
        if (automobile && automobile->checkKeyword(kw)) return true;
        return summary.find(kw) != string::npos ||
               region.getCityName().find(kw) != string::npos;
    }

    virtual string getIndexedContent() const override {
        string t = summary + " " + region.getCityName();
        if (automobile) t += " " + automobile->getIndexedContent();
        return t;
    }

    void postChatNote(string fromID, string toID, string text) {
        if (noteCount < 20) {
            notes[noteCount++] = ChatNote(fromID, toID, text, "2026-04-21");
            cout << "  Chat note posted!" << endl;
        } else {
            cout << "  Inbox full." << endl;
        }
    }

    void viewChatNotes() const {
        cout << "=== Chat Notes for [" << postID << "] ===" << endl;
        if (noteCount == 0) { cout << "  No notes yet." << endl; return; }
        for (int i = 0; i < noteCount; i++) notes[i].renderInfo();
    }

    bool checkMake(const string& b)               const { return automobile && automobile->checkMake(b); }
    bool withinCostRange(double lo, double hi)     const { return listedCost >= lo && listedCost <= hi; }
    bool checkCity(const string& city)             const { return region.getCityName() == city; }
    bool withinOdometer(int km)                    const { return odometerKm <= km; }
    bool checkYear(int yr)                         const { return automobile && automobile->getManufactureYear() == yr; }
    bool checkAutoCategory(const string& t)        const { return automobile && automobile->getCategory() == t; }

    bool operator==(const AdPost& other) const {
        return dealerTag == other.dealerTag && listedCost == other.listedCost;
    }

    bool operator<(const AdPost& other) const { return listedCost < other.listedCost; }

    bool operator>(const AdPost& other) const { return listedCost > other.listedCost; }

    friend ostream& operator<<(ostream& os, const AdPost& p);

    friend void compareDeal(const AdPost& p1, const AdPost& p2);
};

const double AdPost::FLOOR_PRICE  = 50000.0;
int          AdPost::totalPosts   = 0;
int          AdPost::livePosts    = 0;

ostream& operator<<(ostream& os, const AdPost& p) {
    os << "AdPost[" << p.postID << "] PKR " << p.listedCost
       << " | " << p.odometerKm << "km | " << p.vehicleState;
    if (p.automobile) os << " | " << p.automobile->getCategory();
    return os;
}

void compareDeal(const AdPost& p1, const AdPost& p2) {
    cout << "\n=== Smart Deal Comparison ===" << endl;
    cout << "  Option A: " << p1.postID << " | PKR " << p1.listedCost
         << " | " << p1.odometerKm << " km" << endl;
    cout << "  Option B: " << p2.postID << " | PKR " << p2.listedCost
         << " | " << p2.odometerKm << " km" << endl;
    double valA = p1.listedCost + (double)p1.odometerKm * 5.0;
    double valB = p2.listedCost + (double)p2.odometerKm * 5.0;
    if (valA < valB)
        cout << "  >>> Better Deal: Option A (" << p1.postID << ")" << endl;
    else if (valB < valA)
        cout << "  >>> Better Deal: Option B (" << p2.postID << ")" << endl;
    else
        cout << "  >>> Both options offer equal value." << endl;
}

#endif
