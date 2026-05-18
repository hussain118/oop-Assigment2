#ifndef PLATFORM_H
#define PLATFORM_H

#include "UserTypes.h"
#include "AdPost2.h"
#include <iostream>
#include <string>
using namespace std;

class Platform {
private:
    string     siteName;
    AdPost     posts[50];
    int        postCount;

    Customer*  customers[20];
    int        customerCount;

    Dealer*    dealers[20];
    int        dealerCount;

    static const string BUILD_VERSION;
    static int  totalQueries;

public:

    Platform() {
        siteName      = "AutoBazaar";
        postCount     = 0;
        customerCount = 0;
        dealerCount   = 0;
    }

    Platform(string name) {
        siteName      = name;
        postCount     = 0;
        customerCount = 0;
        dealerCount   = 0;
    }

    void setSiteName(string n)    { siteName = n; }
    string getSiteName()    const { return siteName; }
    int    getPostCount()   const { return postCount; }
    static int getTotalQueries()  { return totalQueries; }

    void enrollCustomer(Customer* c) {
        if (customerCount < 20) {
            customers[customerCount++] = c;
            cout << "  Customer [" << c->getCompleteName() << "] enrolled successfully." << endl;
        }
    }

    void enrollDealer(Dealer* d) {
        if (dealerCount < 20) {
            dealers[dealerCount++] = d;
            cout << "  Dealer [" << d->getDealership() << "] enrolled successfully." << endl;
        }
    }

    void submitPost(AdPost post) {
        if (postCount < 50) {
            posts[postCount++] = post;
            cout << "  Ad [" << post.getPostID() << "] submitted to platform." << endl;
        } else {
            cout << "  Platform ad capacity reached." << endl;
        }
    }

    void confirmPost(string postID, Moderator& mod) {
        for (int i = 0; i < postCount; i++) {
            if (posts[i].getPostID() == postID) {
                posts[i].setConfirmed(true);
                cout << "  [MOD:" << mod.getModTag() << "] Confirmed ad: "
                     << postID << endl;
                return;
            }
        }
        cout << "  Ad not found: " << postID << endl;
    }

    void pullPost(string postID, Moderator& mod) {
        for (int i = 0; i < postCount; i++) {
            if (posts[i].getPostID() == postID) {
                posts[i].setLive(false);
                cout << "  [MOD:" << mod.getModTag() << "] Pulled ad: "
                     << postID << endl;
                return;
            }
        }
        cout << "  Ad not found: " << postID << endl;
    }

    void viewAllAds() const {
        cout << "\n=== All Live Ads on " << siteName << " ===" << endl;
        int shown = 0;
        for (int i = 0; i < postCount; i++) {
            if (posts[i].getIsLive() && posts[i].getIsConfirmed()) {
                posts[i].renderBrief();
                shown++;
            }
        }
        if (shown == 0) cout << "  No confirmed ads at the moment." << endl;
        else cout << "  Total: " << shown << " ad(s)" << endl;
    }

    void findByKeyword(const string& keyword) const {
        totalQueries++;
        cout << "\n=== Search Results for \"" << keyword << "\" ===" << endl;
        int hits = 0;
        for (int i = 0; i < postCount; i++) {
            if (posts[i].getIsLive() && posts[i].getIsConfirmed()
                && posts[i].checkKeyword(keyword)) {
                posts[i].renderBrief();
                hits++;
            }
        }
        cout << "  Found: " << hits << " result(s)" << endl;
    }

    void filterByCategory(const string& category) const {
        cout << "\n=== Ads for Category: " << category << " ===" << endl;
        int hits = 0;
        for (int i = 0; i < postCount; i++) {
            if (posts[i].getIsLive() && posts[i].getIsConfirmed()
                && posts[i].checkAutoCategory(category)) {
                posts[i].renderBrief();
                hits++;
            }
        }
        cout << "  Found: " << hits << " result(s)" << endl;
    }

    void filterByPriceRange(double minP, double maxP) const {
        cout << "\n=== Ads in Budget PKR " << minP << " - " << maxP << " ===" << endl;
        int hits = 0;
        for (int i = 0; i < postCount; i++) {
            if (posts[i].getIsLive() && posts[i].getIsConfirmed()
                && posts[i].withinCostRange(minP, maxP)) {
                posts[i].renderBrief();
                hits++;
            }
        }
        cout << "  Found: " << hits << " result(s)" << endl;
    }

    void orderByPrice() {
        for (int i = 0; i < postCount - 1; i++) {
            for (int j = 0; j < postCount - i - 1; j++) {
                if (posts[j] > posts[j+1]) {
                    AdPost temp = posts[j];
                    posts[j]    = posts[j+1];
                    posts[j+1]  = temp;
                }
            }
        }
        cout << "  Ads ordered by cost (low to high)." << endl;
    }

    AdPost& getPost(int index) { return posts[index]; }
    int getCount() const { return postCount; }

    void viewAnalytics() const {
        cout << "\n=== " << siteName << " Analytics ===" << endl;
        cout << "  Build Version     : " << BUILD_VERSION << endl;
        cout << "  Total Ads         : " << AdPost::getTotalPosts() << endl;
        cout << "  Live Ads          : " << AdPost::getLivePosts() << endl;
        cout << "  Enrolled Customers: " << customerCount << endl;
        cout << "  Enrolled Dealers  : " << dealerCount << endl;
        cout << "  Total Queries     : " << totalQueries << endl;
        cout << "  Total Automobiles : " << Automobile::getTotalAutos() << endl;
        cout << "  Total Accounts    : " << Account::getAccountTotal() << endl;
    }

    void confirmAllAds() {
        for (int i = 0; i < postCount; i++)
            posts[i].setConfirmed(true);
        cout << "  [MOD] All " << postCount << " ads confirmed." << endl;
    }

    friend ostream& operator<<(ostream& os, const Platform& pl);
};

const string Platform::BUILD_VERSION = "2.0";
int          Platform::totalQueries  = 0;

ostream& operator<<(ostream& os, const Platform& pl) {
    os << "Platform: " << pl.siteName
       << " | Ads: " << pl.postCount
       << " | Customers: " << pl.customerCount
       << " | Dealers: " << pl.dealerCount;
    return os;
}

#endif
