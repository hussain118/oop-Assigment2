#ifndef MODERATOR_H
#define MODERATOR_H

#include "Account.h"
#include "AdPost.h"
#include <iostream>
#include <string>
using namespace std;

class Moderator {
private:
    Account* account;
    string modTag;
    string designation;
    int confirmedCount;
    int pulledCount;
    bool hasRootAccess;

    static int modTotal;

public:

    Moderator(Account* acc, string desig = "Reviewer", bool root = false) {
        modTotal++;
        modTag = "MOD" + to_string(modTotal);
        this->account = acc;
        this->designation = desig;
        this->confirmedCount = 0;
        this->pulledCount = 0;
        this->hasRootAccess = root;
    }

    Moderator(const Moderator& src) {
        modTotal++;
        modTag = "MOD" + to_string(modTotal);
        account = src.account;
        designation = src.designation;
        confirmedCount = src.confirmedCount;
        pulledCount = src.pulledCount;
        hasRootAccess = src.hasRootAccess;
    }

    void setDesignation(string r) { designation = r; }
    void setRootAccess(bool fa) { hasRootAccess = fa; }
    string getModTag() const { return modTag; }
    string getDesignation() const { return designation; }
    bool getHasRootAccess() const { return hasRootAccess; }
    int getConfirmedCount() const { return confirmedCount; }
    Account* getAccount() const { return account; }

    static int getModTotal() { return modTotal; }

    void confirmAdPost(AdPost& post) {
        post.setConfirmed(true);
        confirmedCount++;
        cout << "[MOD] Ad " << post.getPostID() << " confirmed by " << modTag << endl;
    }

    void pullAdPost(AdPost& post) {
        post.setLive(false);
        pulledCount++;
        cout << "[MOD] Ad " << post.getPostID() << " pulled by " << modTag << endl;
    }

    void showModProfile() const {
        cout << "=== Moderator Profile ===" << endl;
        cout << "  Mod Tag      : " << modTag << endl;
        cout << "  Designation  : " << designation << endl;
        cout << "  Confirmed    : " << confirmedCount << " ads" << endl;
        cout << "  Pulled       : " << pulledCount << " ads" << endl;
        cout << "  Root Access  : " << (hasRootAccess ? "Yes" : "No") << endl;
        if (account) account->showProfile();
    }

    void viewSystemMetrics() const {
        cout << "\n=== System Metrics ===" << endl;
        cout << "  Total Ads Ever     : " << AdPost::getTotalPosts() << endl;
        cout << "  Currently Live     : " << AdPost::getLivePosts() << endl;
        cout << "  Registered Accounts: " << Account::getAccountTotal() << endl;
        cout << "  Total Automobiles  : " << Automobile::getTotalAutos() << endl;
    }

    void suspendAccount(Account& acc) {
        acc.disableAccount();
        cout << "[MOD] " << modTag << " suspended account: " << acc.getAccountID() << endl;
    }
};

int Moderator::modTotal = 0;

#endif

#ifndef QUERYFILTER_H
#define QUERYFILTER_H

#include "AdPost.h"
#include <iostream>
#include <string>
using namespace std;

class QueryFilter {
private:
    string filterTag;
    string makeFilter;
    string variantFilter;
    string cityFilter;
    double floorCost;
    double ceilingCost;
    int maxOdometer;
    int yearFilter;

public:

    QueryFilter() {
        filterTag = "QRY001";
        makeFilter = "";
        variantFilter = "";
        cityFilter = "";
        floorCost = 0;
        ceilingCost = 999999999;
        maxOdometer = 9999999;
        yearFilter = 0;
    }

    QueryFilter(string make, string city, double minP, double maxP) {
        filterTag = "QRY_CUSTOM";
        makeFilter = make;
        variantFilter = "";
        cityFilter = city;
        floorCost = minP;
        ceilingCost = maxP;
        maxOdometer = 9999999;
        yearFilter = 0;
    }

    void setMakeFilter(string b) { makeFilter = b; }
    void setVariantFilter(string m) { variantFilter = m; }
    void setCityFilter(string c) { cityFilter = c; }
    void setCostRange(double minP, double maxP) { floorCost = minP; ceilingCost = maxP; }
    void setMaxOdometer(int km) { maxOdometer = km; }
    void setYearFilter(int y) { yearFilter = y; }

    string getMakeFilter() const { return makeFilter; }
    string getCityFilter() const { return cityFilter; }
    double getFloorCost() const { return floorCost; }
    double getCeilingCost() const { return ceilingCost; }

    void showActiveFilters() const {
        cout << "=== Active Query Filters ===" << endl;
        cout << "  Make     : " << (makeFilter.empty() ? "Any" : makeFilter) << endl;
        cout << "  Variant  : " << (variantFilter.empty() ? "Any" : variantFilter) << endl;
        cout << "  City     : " << (cityFilter.empty() ? "Any" : cityFilter) << endl;
        cout << "  Cost     : PKR " << floorCost << " - " << ceilingCost << endl;
        cout << "  Odometer : Up to " << maxOdometer << " km" << endl;
        cout << "  Year     : " << (yearFilter == 0 ? "Any" : to_string(yearFilter)) << endl;
    }

    void findAds(AdPost posts[], int count) const {
        cout << "\n=== Query Results ===" << endl;
        int hits = 0;
        for (int i = 0; i < count; i++) {
            if (!posts[i].getIsLive() || !posts[i].getIsConfirmed()) continue;

            bool matched = true;

            if (!makeFilter.empty() && !posts[i].checkMake(makeFilter))
                matched = false;
            if (!cityFilter.empty() && !posts[i].checkCity(cityFilter))
                matched = false;
            if (!posts[i].withinCostRange(floorCost, ceilingCost))
                matched = false;
            if (!posts[i].withinOdometer(maxOdometer))
                matched = false;
            if (yearFilter != 0 && !posts[i].checkYear(yearFilter))
                matched = false;

            if (matched) {
                posts[i].showAdPost();
                hits++;
            }
        }
        if (hits == 0)
            cout << "  No ads matched your query." << endl;
        else
            cout << "\n  Total hits: " << hits << endl;
    }

    void resetFilters() {
        makeFilter = "";
        variantFilter = "";
        cityFilter = "";
        floorCost = 0;
        ceilingCost = 999999999;
        maxOdometer = 9999999;
        yearFilter = 0;
        cout << "All query filters reset." << endl;
    }
};

#endif
