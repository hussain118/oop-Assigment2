#ifndef ADPOST_H
#define ADPOST_H

#include "Automobile.h"
#include "Region.h"
#include "ChatFeedback.h"
#include <iostream>
#include <string>
using namespace std;

class AdPost {
private:
    string postID;
    Automobile automobile;
    Region region;
    ChatNote notes[20];
    int noteCount;

    string dealerID;
    double listedCost;
    int odometerKm;
    string vehicleState;
    string summary;
    bool isConfirmed;
    bool isLive;

    static const double FLOOR_PRICE;

    static int totalPosts;
    static int livePosts;

public:

    AdPost() : automobile(), region() {
        totalPosts++;
        postID = "ADP" + to_string(totalPosts);
        dealerID = "";
        listedCost = FLOOR_PRICE;
        odometerKm = 0;
        vehicleState = "Used";
        summary = "No summary provided.";
        isConfirmed = false;
        isLive = false;
        noteCount = 0;
        livePosts++;
    }

    AdPost(Automobile auto_, Region reg, string dID, double cost,
           int km, string state, string desc)
        : automobile(auto_), region(reg) {
        totalPosts++;
        postID = "ADP" + to_string(totalPosts);
        dealerID = dID;
        listedCost = (cost >= FLOOR_PRICE) ? cost : FLOOR_PRICE;
        odometerKm = km;
        vehicleState = state;
        summary = desc;
        isConfirmed = false;
        isLive = true;
        noteCount = 0;
        livePosts++;
    }

    AdPost(const AdPost& src) : automobile(src.automobile), region(src.region) {
        totalPosts++;
        postID = "ADP" + to_string(totalPosts);
        dealerID = src.dealerID;
        listedCost = src.listedCost;
        odometerKm = src.odometerKm;
        vehicleState = src.vehicleState;
        summary = src.summary;
        isConfirmed = false;
        isLive = src.isLive;
        noteCount = 0;
        livePosts++;
    }

    ~AdPost() {
        if (isLive) livePosts--;
    }

    void setListedCost(double p) { if (p >= FLOOR_PRICE) listedCost = p; }
    void setOdometerKm(int m) { odometerKm = m; }
    void setVehicleState(string c) { vehicleState = c; }
    void setSummary(string d) { summary = d; }
    void setConfirmed(bool a) { isConfirmed = a; }
    void setLive(bool a) { isLive = a; }

    string getPostID() const { return postID; }
    double getListedCost() const { return listedCost; }
    int getOdometerKm() const { return odometerKm; }
    string getVehicleState() const { return vehicleState; }
    string getDealerID() const { return dealerID; }
    bool getIsConfirmed() const { return isConfirmed; }
    bool getIsLive() const { return isLive; }
    Automobile getAutomobile() const { return automobile; }
    Region getRegion() const { return region; }

    static int getTotalPosts() { return totalPosts; }
    static int getLivePosts() { return livePosts; }

    void showAdPost() const {
        cout << "\n========================================" << endl;
        cout << "  Post ID     : " << postID << endl;
        cout << "  Dealer ID   : " << dealerID << endl;
        cout << "  Cost        : PKR " << listedCost << endl;
        cout << "  Odometer    : " << odometerKm << " km" << endl;
        cout << "  State       : " << vehicleState << endl;
        cout << "  Status      : " << (isConfirmed ? "Confirmed" : "Pending") << endl;
        cout << "  Summary     : " << summary << endl;
        cout << "--- Automobile Info ---" << endl;
        automobile.showAutoInfo();
        cout << "--- Region ---" << endl;
        region.showRegion();
        cout << "========================================" << endl;
    }

    void postChatNote(string fromID, string toID, string text) {
        if (noteCount < 20) {
            notes[noteCount++] = ChatNote(fromID, toID, text, "2026-04-21");
            cout << "Chat note sent successfully!" << endl;
        } else {
            cout << "Chat inbox full for this ad post." << endl;
        }
    }

    void viewChatNotes() const {
        cout << "=== Chat Notes for Post " << postID << " ===" << endl;
        if (noteCount == 0) {
            cout << "  No chat notes yet." << endl;
            return;
        }
        for (int i = 0; i < noteCount; i++) {
            notes[i].showNote();
        }
    }

    bool checkMake(const string& make) const {
        return automobile.checkMake(make);
    }

    bool withinCostRange(double minP, double maxP) const {
        return listedCost >= minP && listedCost <= maxP;
    }

    bool checkCity(const string& city) const {
        return region.getCityName() == city;
    }

    bool withinOdometer(int maxKm) const {
        return odometerKm <= maxKm;
    }

    bool checkYear(int yr) const {
        return automobile.getManufactureYear() == yr;
    }
};

const double AdPost::FLOOR_PRICE = 50000.0;
int AdPost::totalPosts = 0;
int AdPost::livePosts = 0;

#endif
