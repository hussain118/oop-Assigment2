#ifndef USER_TYPES_H
#define USER_TYPES_H

#include "Account2.h"
#include <iostream>
#include <string>
using namespace std;

class Customer : public Account {
private:
    string customerTag;
    string bookmarkedAds[10];
    int    bookmarkCount;
    string spendingLimit;
    string targetCity;
    bool   isGoldMember;

    static int customerTotal;

public:

    Customer() : Account() {
        customerTotal++;
        customerTag = "CST" + to_string(customerTotal);
        bookmarkCount = 0;
        spendingLimit = "Any";
        targetCity = "Any";
        isGoldMember = false;
    }

    Customer(string name, string mail, string num, string pwd,
             string limit = "Any", string city = "Any")
        : Account(name, mail, num, pwd) {
        customerTotal++;
        customerTag = "CST" + to_string(customerTotal);
        this->spendingLimit = limit;
        this->targetCity = city;
        bookmarkCount = 0;
        isGoldMember = false;
    }

    Customer(const Customer& src) : Account(src) {
        customerTotal++;
        customerTag = "CST" + to_string(customerTotal);
        spendingLimit = src.spendingLimit;
        targetCity = src.targetCity;
        bookmarkCount = src.bookmarkCount;
        isGoldMember = src.isGoldMember;
        for (int i = 0; i < bookmarkCount; i++)
            bookmarkedAds[i] = src.bookmarkedAds[i];
    }

    virtual ~Customer() {}

    void setSpendingLimit(string b)  { spendingLimit = b; }
    void setTargetCity(string c)     { targetCity = c; }
    void setGoldMember(bool p)       { isGoldMember = p; }
    string getCustomerTag()    const { return customerTag; }
    string getSpendingLimit()  const { return spendingLimit; }
    string getTargetCity()     const { return targetCity; }
    bool   getIsGoldMember()   const { return isGoldMember; }

    static int getCustomerTotal() { return customerTotal; }

    virtual void renderInfo() const override {
        cout << "=== [CUSTOMER] Profile ===" << endl;
        cout << "  Customer Tag: " << customerTag << endl;
        cout << "  Name        : " << completeName << endl;
        cout << "  Email       : " << emailAddr << endl;
        cout << "  Contact     : " << contactNum << endl;
        cout << "  Budget      : PKR " << spendingLimit << endl;
        cout << "  Target City : " << targetCity << endl;
        cout << "  Gold Member : " << (isGoldMember ? "Yes" : "No") << endl;
        cout << "  Authenticated: " << (authenticated ? "Yes" : "No") << endl;
    }

    virtual void renderBrief() const override {
        cout << "  Customer: " << completeName << " | Budget: PKR " << spendingLimit
             << " | City: " << targetCity << endl;
    }

    void bookmarkAd(string postID) {
        if (bookmarkCount < 10) {
            bookmarkedAds[bookmarkCount++] = postID;
            cout << "Ad [" << postID << "] bookmarked!" << endl;
        } else {
            cout << "Bookmarks full. Clear some to add more." << endl;
        }
    }

    void viewBookmarks() const {
        cout << "=== " << completeName << "'s Bookmarked Ads ===" << endl;
        if (bookmarkCount == 0) { cout << "  No bookmarks yet." << endl; return; }
        for (int i = 0; i < bookmarkCount; i++)
            cout << "  " << (i+1) << ". " << bookmarkedAds[i] << endl;
    }

    void removeBookmark(string postID) {
        for (int i = 0; i < bookmarkCount; i++) {
            if (bookmarkedAds[i] == postID) {
                for (int j = i; j < bookmarkCount - 1; j++)
                    bookmarkedAds[j] = bookmarkedAds[j+1];
                bookmarkCount--;
                cout << "Bookmark removed." << endl;
                return;
            }
        }
        cout << "Ad not found in bookmarks." << endl;
    }

    Customer operator+(const Customer& other) const {
        Customer joint;
        joint.completeName = this->completeName + " & " + other.completeName;
        joint.spendingLimit = "Joint";
        joint.targetCity = this->targetCity;
        return joint;
    }

    bool operator==(const Customer& other) const {
        return emailAddr == other.emailAddr;
    }

    friend void suggestUpgrade(const Customer& c);
};

int Customer::customerTotal = 0;

void suggestUpgrade(const Customer& c) {
    cout << "  [Suggestion for " << c.completeName << "] ";
    if (!c.isGoldMember)
        cout << "Upgrade to Gold for priority search & featured ads!" << endl;
    else
        cout << "You are already a Gold member. Enjoy your perks!" << endl;
}

class Dealer : public Account {
private:
    string dealerTag;
    int    postedAds;
    double score;
    bool   isCertifiedDealer;
    string dealership;
    string dealerAddress;

    static int dealerTotal;

public:

    Dealer() : Account() {
        dealerTotal++;
        dealerTag = "DLR" + to_string(dealerTotal);
        postedAds = 0;
        score = 0.0;
        isCertifiedDealer = false;
        dealership = "Independent Dealer";
        dealerAddress = "Not specified";
    }

    Dealer(string name, string mail, string num, string pwd,
           string shop = "Independent Dealer", string addr = "")
        : Account(name, mail, num, pwd) {
        dealerTotal++;
        dealerTag = "DLR" + to_string(dealerTotal);
        this->dealership = shop;
        this->dealerAddress = addr;
        postedAds = 0;
        score = 0.0;
        isCertifiedDealer = false;
    }

    Dealer(const Dealer& src) : Account(src) {
        dealerTotal++;
        dealerTag = "DLR" + to_string(dealerTotal);
        dealership = src.dealership;
        dealerAddress = src.dealerAddress;
        postedAds = src.postedAds;
        score = src.score;
        isCertifiedDealer = src.isCertifiedDealer;
    }

    virtual ~Dealer() {}

    void setDealership(string s)       { dealership = s; }
    void setDealerAddress(string a)    { dealerAddress = a; }
    void setScore(double r)            { if (r >= 0 && r <= 5) score = r; }
    void setCertifiedDealer(bool v)    { isCertifiedDealer = v; }
    string getDealerTag()         const { return dealerTag; }
    string getDealership()        const { return dealership; }
    double getScore()             const { return score; }
    bool   getIsCertifiedDealer() const { return isCertifiedDealer; }
    int    getPostedAds()         const { return postedAds; }

    static int getDealerTotal() { return dealerTotal; }

    virtual void renderInfo() const override {
        cout << "=== [DEALER] Profile ===" << endl;
        cout << "  Dealer Tag : " << dealerTag << endl;
        cout << "  Name       : " << completeName << endl;
        cout << "  Email      : " << emailAddr << endl;
        cout << "  Contact    : " << contactNum << endl;
        cout << "  Dealership : " << dealership << endl;
        cout << "  Score      : " << score << "/5" << endl;
        cout << "  Ads Posted : " << postedAds << endl;
        cout << "  Certified  : " << (isCertifiedDealer ? "Yes" : "No") << endl;
    }

    virtual void renderBrief() const override {
        cout << "  Dealer: " << dealership << " (" << dealerTag
             << ") | Score: " << score << "/5" << endl;
    }

    void incrementAds() {
        postedAds++;
        cout << "Ad posted by " << dealership << ". Total: " << postedAds << endl;
    }

    void decrementAds() {
        if (postedAds > 0) postedAds--;
    }

    void recalcScore(double fresh) {
        if (postedAds > 0)
            score = (score + fresh) / 2.0;
        else
            score = fresh;
    }

    Dealer operator+(const Dealer& other) const {
        Dealer merged;
        merged.completeName = this->completeName + " & " + other.completeName;
        merged.dealership   = this->dealership + " + " + other.dealership;
        merged.postedAds    = this->postedAds + other.postedAds;
        merged.score        = (this->score + other.score) / 2.0;
        return merged;
    }

    bool operator==(const Dealer& other) const {
        return dealership == other.dealership;
    }

    bool operator>(const Dealer& other) const {
        return score > other.score;
    }

    friend class Moderator;

    friend Dealer& topRatedDealer(Dealer& d1, Dealer& d2);
};

int Dealer::dealerTotal = 0;

Dealer& topRatedDealer(Dealer& d1, Dealer& d2) {
    return (d1.score >= d2.score) ? d1 : d2;
}

class Moderator : public Account {
private:
    string modTag;
    string designation;
    int    confirmedCount;
    int    pulledCount;
    bool   hasRootAccess;

    static int modTotal;

public:

    Moderator() : Account() {
        modTotal++;
        modTag = "MOD" + to_string(modTotal);
        designation = "Reviewer";
        confirmedCount = 0;
        pulledCount = 0;
        hasRootAccess = false;
    }

    Moderator(string name, string mail, string num, string pwd,
              string desig = "Reviewer", bool root = false)
        : Account(name, mail, num, pwd) {
        modTotal++;
        modTag = "MOD" + to_string(modTotal);
        this->designation = desig;
        this->hasRootAccess = root;
        confirmedCount = 0;
        pulledCount = 0;
    }

    Moderator(const Moderator& src) : Account(src) {
        modTotal++;
        modTag = "MOD" + to_string(modTotal);
        designation = src.designation;
        confirmedCount = src.confirmedCount;
        pulledCount = src.pulledCount;
        hasRootAccess = src.hasRootAccess;
    }

    virtual ~Moderator() {}

    void setDesignation(string r)  { designation = r; }
    void setRootAccess(bool fa)    { hasRootAccess = fa; }
    string getModTag()         const { return modTag; }
    string getDesignation()    const { return designation; }
    bool   getHasRootAccess()  const { return hasRootAccess; }
    int    getConfirmedCount() const { return confirmedCount; }
    int    getPulledCount()    const { return pulledCount; }

    static int getModTotal() { return modTotal; }

    virtual void renderInfo() const override {
        cout << "=== [MODERATOR] Profile ===" << endl;
        cout << "  Mod Tag    : " << modTag << endl;
        cout << "  Name       : " << completeName << endl;
        cout << "  Email      : " << emailAddr << endl;
        cout << "  Designation: " << designation << endl;
        cout << "  Confirmed  : " << confirmedCount << " ads" << endl;
        cout << "  Pulled     : " << pulledCount << " ads" << endl;
        cout << "  Root Access: " << (hasRootAccess ? "Yes" : "No") << endl;
    }

    virtual void renderBrief() const override {
        cout << "  Moderator: " << completeName << " | Role: " << designation << endl;
    }

    void inspectDealer(const Dealer& d) const {
        cout << "=== [MOD INSPECTION] Dealer: " << d.dealership << " ===" << endl;

        cout << "  Raw Score (private access): " << d.score << endl;
        cout << "  Certified Status: " << (d.isCertifiedDealer ? "Yes" : "No") << endl;
        cout << "  Total Ads Posted : " << d.postedAds << endl;
    }

    void certifyDealer(Dealer& d) {
        d.setCertifiedDealer(true);
        confirmedCount++;
        cout << "[MOD] " << d.getDealership() << " is now a Certified Dealer." << endl;
    }

    void suspendAccount(Account& a) {
        a.disableAccount();
        cout << "[MOD] " << modTag << " suspended: " << a.getAccountID() << endl;
    }

    void viewSystemMetrics() const {
        cout << "\n=== System Metrics ===" << endl;
        cout << "  Total Accounts  : " << Account::getAccountTotal() << endl;
        cout << "  Total Dealers   : " << Dealer::getDealerTotal() << endl;
        cout << "  Total Customers : " << Customer::getCustomerTotal() << endl;
        cout << "  Total Moderators: " << Moderator::getModTotal() << endl;
    }

    bool operator==(const Moderator& other) const {
        return designation == other.designation;
    }
};

int Moderator::modTotal = 0;

#endif
