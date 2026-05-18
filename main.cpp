#include <iostream>
#include <string>
#include "IRenderable.h"
#include "IFilterable.h"
#include "IAuthenticable.h"
#include "IValuable.h"
#include "Account2.h"
#include "UserTypes.h"
#include "Automobile2.h"
#include "RegionChat2.h"
#include "AdPost2.h"
#include "Platform.h"

using namespace std;

void demonstrateAutoPolymorphism(Automobile* a) {

    cout << "  Category: " << a->getCategory() << endl;
    a->renderInfo();
    cout << "  Insurance Estimate: PKR " << a->calcInsurance() << endl;
}

void demonstrateAccountPolymorphism(Account* a) {

    a->renderInfo();
}

int main() {

    cout << "      AutoBazaar Platform System - Assignment 2            " << endl;
    cout << "============================================================\n" << endl;

    Customer cust1("Sara Khan",   "sara@gmail.com",   "0321-1111111", "pass1", "800000-1500000", "Karachi");
    Customer cust2("Zara Ahmed",  "zara@gmail.com",   "0311-2222222", "pass2", "500000-900000",  "Lahore");
    Dealer   dlr1("Ali Hassan",   "ali@gmail.com",    "0300-3333333", "pass3", "Ali Motors Karachi");
    Dealer   dlr2("Kamran Beg",   "kamran@gmail.com", "0333-4444444", "pass4", "Kamran Auto Lahore");
    Moderator mod1("Ahmed Raza",  "admin@pakwheels.pk","0311-0000000","adminpass","Head Moderator", true);

    cout << ">>> Polymorphic rendering via Account* pointers:\n" << endl;
    Account* accounts[5] = { &cust1, &cust2, &dlr1, &dlr2, &mod1 };
    for (int i = 0; i < 5; i++) {
        demonstrateAccountPolymorphism(accounts[i]);
        cout << endl;
    }

    MotorCar mc1("Toyota", "Corolla", 2021, 1800.0, "White", "Automatic", "Petrol",
                 4, "Sedan", true, false, 5);

    MotorCar mc2("Honda", "Civic", 2020, 1500.0, "Black", "Manual", "Petrol",
                 4, "Sedan", true, true, 5);

    MotorCar mc3("Suzuki", "Alto", 2023, 660.0, "Red", "Manual", "Petrol",
                 4, "Hatchback", true, false, 5);

    Motorcycle bike1("Yamaha", "YBR125", 2022, 125.0, "Blue", "Manual",
                     "Standard", false, 1);

    Motorcycle bike2("Honda", "CB150F", 2023, 150.0, "Black", "Manual",
                     "Standard", true, 1);

    Automobile* autos[5] = { &mc1, &mc2, &mc3, &bike1, &bike2 };
    for (int i = 0; i < 5; i++) {
        cout << "  --- Automobile " << (i+1) << " ---" << endl;
        demonstrateAutoPolymorphism(autos[i]);
        cout << endl;
    }

    cout << ">>> IAuthenticable - Authenticating Accounts:" << endl;
    cust1.confirmIdentity();
    dlr1.confirmIdentity();
    mod1.confirmIdentity();
    cout << "  Sara authenticated: " << (cust1.isAuthenticated() ? "Yes" : "No") << endl;
    cout << "  Ali authenticated : " << (dlr1.isAuthenticated() ? "Yes" : "No") << endl;

    cout << "\n>>> IFilterable - Keyword check on automobiles:" << endl;
    IFilterable* filterable = &mc1;
    cout << "  mc1 checks 'Toyota': " << (filterable->checkKeyword("Toyota") ? "Yes" : "No") << endl;
    cout << "  mc1 checks 'Honda' : " << (filterable->checkKeyword("Honda")  ? "Yes" : "No") << endl;

    MotorCar mcDuplicate("Toyota", "Corolla", 2021, 1800.0, "Silver", "Automatic", "Petrol",
                         4, "Sedan", true, false, 5);
    cout << "  mc1 == mcDuplicate (same make/variant/year): "
         << (mc1 == mcDuplicate ? "TRUE  Duplicate" : "FALSE  Different") << endl;
    cout << "  mc1 == mc2: "
         << (mc1 == mc2 ? "TRUE" : "FALSE - Different") << endl;

    cout << "\n>>> Automobile < > operators (year comparison):" << endl;
    cout << "  mc2(2020) < mc3(2023): " << (mc2 < mc3 ? "Yes (older)" : "No") << endl;
    cout << "  mc3(2023) > mc1(2021): " << (mc3 > mc1 ? "Yes (newer)" : "No") << endl;

    cout << "  " << mc1 << endl;
    cout << "  " << bike1 << endl;

    Account accA("Ali Hassan", "ali@gmail.com", "0000", "xxx");
    Account accB("Different Person", "ali@gmail.com", "1111", "yyy");
    cout << "  accA == accB (same email): "
         << (accA == accB ? "TRUE - Duplicate account detected!" : "FALSE") << endl;

    cout << "  " << cust1 << endl;
    cout << "  " << dlr1 << endl;

    Dealer mergedShop = dlr1 + dlr2;
    cout << "  Merged Dealership: " << mergedShop.getDealership() << endl;
    cout << "  Combined Ads: " << mergedShop.getPostedAds() << endl;

    Customer jointCustomers = cust1 + cust2;
    cout << "  Joint customer name: " << jointCustomers.getCompleteName() << endl;

    dlr1.setScore(4.2);
    dlr2.setScore(3.8);
    cout << "  dlr1(4.2) > dlr2(3.8): "
         << (dlr1 > dlr2 ? "Yes - Ali Motors is higher rated" : "No") << endl;

    Region reg1("Karachi", "Sindh", "Pakistan", "75000");
    Region reg2("Karachi", "Sindh", "Pakistan", "75200");
    Region reg3("Lahore",  "Punjab","Pakistan", "54000");
    cout << "  reg1 == reg2 (same city): " << (reg1 == reg2 ? "Same zone" : "Different") << endl;
    cout << "  reg1 == reg3 (diff city): " << (reg1 == reg3 ? "Same zone" : "Different") << endl;
    cout << "  reg1 << : " << reg1 << endl;

    ChatNote note1(cust1.getCustomerTag(), dlr1.getDealerTag(),
                   "Is the Corolla available?", "2026-04-21 10:00");
    ChatNote note2(cust1.getCustomerTag(), dlr1.getDealerTag(),
                   "What is your final price?", "2026-04-21 10:05");
    ChatNote merged = note1 + note2;
    cout << "  Merged: " << merged << endl;

    suggestUpgrade(cust1);
    suggestUpgrade(cust2);

    Dealer& best = topRatedDealer(dlr1, dlr2);
    cout << "  Top rated dealer: " << best.getDealership()
         << " (Score: " << best.getScore() << ")" << endl;

    cout << "  mc1 (1800CC, 5 seats) is premium: "
         << (isPremiumCar(mc1) ? "Yes" : "No") << endl;
    MotorCar premiumMC("Toyota","Land Cruiser",2024,4000.0,"White","Automatic","Petrol",
                       4,"SUV",true,true,7);
    cout << "  LandCruiser (4000CC, 7 seats) is premium: "
         << (isPremiumCar(premiumMC) ? "Yes" : "No") << endl;

    mod1.certifyDealer(dlr1);
    mod1.inspectDealer(dlr2);

    Platform bazaar("AutoBazaar v2");

    cout << ">>> Enrolling Accounts:" << endl;
    bazaar.enrollCustomer(&cust1);
    bazaar.enrollCustomer(&cust2);
    bazaar.enrollDealer(&dlr1);
    bazaar.enrollDealer(&dlr2);

    dlr1.incrementAds();
    dlr1.incrementAds();
    dlr1.incrementAds();
    dlr2.incrementAds();
    dlr2.incrementAds();

    AdPost ad1(&mc1, reg1, dlr1.getDealerTag(), 1250000, 45000,
               "Used", "Well-maintained Corolla. Single owner. Complete documentation.");
    AdPost ad2(&mc2, reg3, dlr1.getDealerTag(), 950000, 70000,
               "Used", "Honda Civic in excellent shape. Alloy wheels, factory paint.");
    AdPost ad3(&mc3, reg1, dlr2.getDealerTag(), 1850000, 5000,
               "New", "Brand new Alto. Barely driven. Under manufacturer warranty.");
    AdPost ad4(&bike1, reg1, dlr2.getDealerTag(), 275000, 8000,
               "Used", "Yamaha YBR125. Solid condition. Fresh tyres installed.");
    AdPost ad5(&bike2, reg3, dlr1.getDealerTag(), 350000, 3000,
               "New", "Honda CB150F. Minimal usage. All documents present.");

    bazaar.submitPost(ad1);
    bazaar.submitPost(ad2);
    bazaar.submitPost(ad3);
    bazaar.submitPost(ad4);
    bazaar.submitPost(ad5);

    for (int i = 0; i < bazaar.getCount(); i++) {
        bazaar.getPost(i).setConfirmed(true);
        cout << "  [MOD:MOD1] Confirmed ad: "
             << bazaar.getPost(i).getPostID() << endl;
    }

    bazaar.viewAllAds();

    cout << "\n>>> Filtering by Category:" << endl;
    bazaar.filterByCategory("MotorCar");
    bazaar.filterByCategory("Motorcycle");

    bazaar.filterByPriceRange(200000, 1000000);
    bazaar.findByKeyword("Honda");
    bazaar.findByKeyword("Karachi");
    bazaar.orderByPrice();
    bazaar.viewAllAds();

    cout << "\n>>> Customer Bookmarking Ads:" << endl;
    cust1.bookmarkAd(ad1.getPostID());
    cust1.bookmarkAd(ad3.getPostID());
    cust1.viewBookmarks();

    ad1.postChatNote(cust1.getCustomerTag(), dlr1.getDealerTag(),
                     "Is the Corolla still available for viewing this weekend?");
    ad1.postChatNote(cust2.getCustomerTag(), dlr1.getDealerTag(),
                     "Can you negotiate on the price?");
    ad1.viewChatNotes();

    compareDeal(ad1, ad2);

    cout << "  " << ad1 << endl;
    cout << "  " << ad4 << endl;

    cout << "\n>>> AdPost < operator (cost sort check):" << endl;
    cout << "  ad4(275000) < ad1(1250000): " << (ad4 < ad1 ? "Yes" : "No") << endl;

    cout << "\n>>> Moderator Pulling an Ad:" << endl;

    if (bazaar.getCount() > 1) {
        bazaar.getPost(1).setLive(false);
        cout << "  [MOD:MOD1] Pulled ad: "
             << bazaar.getPost(1).getPostID() << endl;
    }

    cout << "\n>>> Platform << operator:" << endl;
    cout << "  " << bazaar << endl;

    bazaar.viewAnalytics();

    cout << endl;
    mod1.viewSystemMetrics();
    mod1.renderInfo();

    return 0;
}
