#ifndef DEALER_H
#define DEALER_H

#include "Account.h"
#include <string>
#include <iostream>
using namespace std;

class Dealer {
private:
    Account* account;
    string dealerTag;
    int postedAds;
    double score;
    bool isCertified;
    string dealership;

    static int dealerTotal;

public:

    Dealer(Account* acc, string shop = "Independent Dealer") {
        dealerTotal++;
        dealerTag = "DLR" + to_string(dealerTotal);
        this->account = acc;
        this->dealership = shop;
        this->postedAds = 0;
        this->score = 0.0;
        this->isCertified = false;
    }

    Dealer(const Dealer& src) {
        dealerTotal++;
        dealerTag = "DLR" + to_string(dealerTotal);
        account = src.account;
        dealership = src.dealership;
        postedAds = src.postedAds;
        score = src.score;
        isCertified = src.isCertified;
    }

    void setDealership(string name) { dealership = name; }
    void setScore(double r) { if (r >= 0 && r <= 5) score = r; }
    void setCertified(bool v) { isCertified = v; }

    string getDealerTag() const { return dealerTag; }
    string getDealership() const { return dealership; }
    double getScore() const { return score; }
    bool getIsCertified() const { return isCertified; }
    int getPostedAds() const { return postedAds; }
    Account* getAccount() const { return account; }

    static int getDealerTotal() { return dealerTotal; }

    void incrementAds() {
        postedAds++;
        cout << "Ad posted. Total ads by " << dealership << ": " << postedAds << endl;
    }

    void decrementAds() {
        if (postedAds > 0) postedAds--;
        cout << "Ad removed. Remaining: " << postedAds << endl;
    }

    void showDealerProfile() const {
        cout << "=== Dealer Profile ===" << endl;
        cout << "  Dealer Tag : " << dealerTag << endl;
        cout << "  Dealership : " << dealership << endl;
        cout << "  Score      : " << score << "/5" << endl;
        cout << "  Certified  : " << (isCertified ? "Yes" : "No") << endl;
        cout << "  Ads Posted : " << postedAds << endl;
        if (account) account->showProfile();
    }

    void recalcScore(double fresh) {
        score = (score + fresh) / 2.0;
        cout << "Score recalculated to: " << score << endl;
    }
};

int Dealer::dealerTotal = 0;

#endif

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Account.h"
#include <string>
#include <iostream>
using namespace std;

class Customer {
private:
    Account* account;
    string customerTag;
    string bookmarkedAds[10];
    int bookmarkCount;
    string spendingLimit;
    string targetCity;
    bool isGoldMember;

    static int customerTotal;

public:

    Customer(Account* acc, string limit = "Any", string city = "Any") {
        customerTotal++;
        customerTag = "CST" + to_string(customerTotal);
        this->account = acc;
        this->spendingLimit = limit;
        this->targetCity = city;
        this->bookmarkCount = 0;
        this->isGoldMember = false;
    }

    Customer(const Customer& src) {
        customerTotal++;
        customerTag = "CST" + to_string(customerTotal);
        account = src.account;
        spendingLimit = src.spendingLimit;
        targetCity = src.targetCity;
        bookmarkCount = src.bookmarkCount;
        isGoldMember = src.isGoldMember;
        for (int i = 0; i < bookmarkCount; i++)
            bookmarkedAds[i] = src.bookmarkedAds[i];
    }

    void setSpendingLimit(string b) { spendingLimit = b; }
    void setTargetCity(string c) { targetCity = c; }
    void setGoldMember(bool p) { isGoldMember = p; }

    string getCustomerTag() const { return customerTag; }
    string getSpendingLimit() const { return spendingLimit; }
    string getTargetCity() const { return targetCity; }
    bool getIsGoldMember() const { return isGoldMember; }
    Account* getAccount() const { return account; }

    static int getCustomerTotal() { return customerTotal; }

    void bookmarkAd(string postID) {
        if (bookmarkCount < 10) {
            bookmarkedAds[bookmarkCount++] = postID;
            cout << "Ad " << postID << " bookmarked!" << endl;
        } else {
            cout << "Bookmarks full. Clear some to add more." << endl;
        }
    }

    void viewBookmarks() const {
        cout << "=== Bookmarked Ads ===" << endl;
        if (bookmarkCount == 0) {
            cout << "  No bookmarked ads yet." << endl;
            return;
        }
        for (int i = 0; i < bookmarkCount; i++) {
            cout << "  " << (i+1) << ". " << bookmarkedAds[i] << endl;
        }
    }

    void showCustomerProfile() const {
        cout << "=== Customer Profile ===" << endl;
        cout << "  Customer Tag  : " << customerTag << endl;
        cout << "  Budget        : PKR " << spendingLimit << endl;
        cout << "  Target City   : " << targetCity << endl;
        cout << "  Gold Member   : " << (isGoldMember ? "Yes" : "No") << endl;
        if (account) account->showProfile();
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
};

int Customer::customerTotal = 0;

#endif
