#ifndef ACCOUNT2_H
#define ACCOUNT2_H

#include "IRenderable.h"
#include "IAuthenticable.h"
#include <iostream>
#include <string>
using namespace std;

class Account : public IRenderable, public IAuthenticable {
protected:

    string accountID;
    string completeName;
    string emailAddr;
    string contactNum;
    string encryptedPass;
    bool   accountActive;
    bool   authenticated;

    static int accountTotal;
    static const string SITE_DOMAIN;

public:

    Account() {
        accountTotal++;
        accountID = "ACC" + to_string(accountTotal);
        completeName = "Guest";
        emailAddr = "";
        contactNum = "";
        encryptedPass = "";
        accountActive = false;
        authenticated = false;
    }

    Account(string name, string mail, string num, string pwd) {
        accountTotal++;
        accountID = "ACC" + to_string(accountTotal);
        this->completeName = name;
        this->emailAddr = mail;
        this->contactNum = num;
        this->encryptedPass = pwd;
        accountActive = true;
        authenticated = false;
    }

    Account(const Account& src) {
        accountTotal++;
        accountID = src.accountID + "_c";
        completeName = src.completeName;
        emailAddr = src.emailAddr;
        contactNum = src.contactNum;
        encryptedPass = src.encryptedPass;
        accountActive = src.accountActive;
        authenticated = src.authenticated;
    }

    virtual ~Account() {}

    void setCompleteName(string n) { completeName = n; }
    void setEmailAddr(string e)    { emailAddr = e; }
    void setContactNum(string p)   { contactNum = p; }
    void setEncryptedPass(string p) { encryptedPass = p; }
    void setAccountActive(bool a)  { accountActive = a; }

    string getAccountID()    const { return accountID; }
    string getCompleteName() const { return completeName; }
    string getEmailAddr()    const { return emailAddr; }
    string getContactNum()   const { return contactNum; }
    bool   getAccountActive()const { return accountActive; }

    static int getAccountTotal() { return accountTotal; }

    virtual void renderInfo() const override {
        cout << "  [Account] ID: " << accountID << " | Name: " << completeName
             << " | Email: " << emailAddr << " | Active: " << (accountActive?"Yes":"No") << endl;
    }

    virtual void renderBrief() const override {
        cout << "  Account: " << completeName << " (" << accountID << ")" << endl;
    }

    virtual bool confirmIdentity() override {
        authenticated = true;
        cout << completeName << " has been authenticated." << endl;
        return true;
    }
    virtual bool isAuthenticated() const override { return authenticated; }
    virtual void withdrawAuth() override {
        authenticated = false;
        cout << completeName << "'s authentication withdrawn." << endl;
    }

    bool logIn(string em, string pwd) const {
        return (emailAddr == em && encryptedPass == pwd);
    }

    bool logIn(string uid) const {
        return (accountID == uid && accountActive);
    }

    void disableAccount() {
        accountActive = false;
        cout << completeName << "'s account disabled." << endl;
    }

    bool checkEmailValid() const {
        return emailAddr.find('@') != string::npos;
    }

    bool operator==(const Account& other) const {
        return emailAddr == other.emailAddr;
    }

    friend ostream& operator<<(ostream& os, const Account& a);

    friend istream& operator>>(istream& is, Account& a);
};

int Account::accountTotal = 0;
const string Account::SITE_DOMAIN = "pakwheels.pk";

ostream& operator<<(ostream& os, const Account& a) {
    os << "Account[" << a.accountID << ": " << a.completeName << " <" << a.emailAddr << ">]";
    return os;
}

istream& operator>>(istream& is, Account& a) {
    cout << "Enter name: "; is >> a.completeName;
    cout << "Enter email: "; is >> a.emailAddr;
    cout << "Enter contact: "; is >> a.contactNum;
    return is;
}

#endif
