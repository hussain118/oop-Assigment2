#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <string>
using namespace std;

class Account {
private:
    string accountID;
    string completeName;
    string emailAddr;
    string contactNum;
    string encryptedPass;
    bool accountActive;

    static int accountTotal;

public:

    static const string SITE_DOMAIN;

    Account() {
        accountTotal++;
        accountID = "ACC" + to_string(accountTotal);
        completeName = "Guest Account";
        emailAddr = "";
        contactNum = "";
        encryptedPass = "";
        accountActive = false;
    }

    Account(string name, string mail, string num, string pwd) {
        accountTotal++;
        accountID = "ACC" + to_string(accountTotal);
        this->completeName = name;
        this->emailAddr = mail;
        this->contactNum = num;
        this->encryptedPass = pwd;
        this->accountActive = true;
    }

    Account(const Account& src) {
        accountID = src.accountID + "_dup";
        completeName = src.completeName;
        emailAddr = src.emailAddr;
        contactNum = src.contactNum;
        encryptedPass = src.encryptedPass;
        accountActive = src.accountActive;
        accountTotal++;
    }

    void setCompleteName(string name) { completeName = name; }
    void setEmailAddr(string e) { emailAddr = e; }
    void setContactNum(string p) { contactNum = p; }
    void setEncryptedPass(string pass) { encryptedPass = pass; }
    void setAccountActive(bool status) { accountActive = status; }

    string getAccountID() const { return accountID; }
    string getCompleteName() const { return completeName; }
    string getEmailAddr() const { return emailAddr; }
    string getContactNum() const { return contactNum; }
    bool getAccountActive() const { return accountActive; }

    static int getAccountTotal() { return accountTotal; }

    void showProfile() const {
        cout << "  Account ID : " << accountID << endl;
        cout << "  Name       : " << completeName << endl;
        cout << "  Email      : " << emailAddr << endl;
        cout << "  Contact    : " << contactNum << endl;
        cout << "  Status     : " << (accountActive ? "Active" : "Inactive") << endl;
    }

    bool authenticate(string mail, string pwd) const {
        return (this->emailAddr == mail && this->encryptedPass == pwd);
    }

    void disableAccount() {
        accountActive = false;
        cout << completeName << "'s account has been disabled." << endl;
    }

    bool checkEmailValid() const {
        return emailAddr.find('@') != string::npos;
    }
};

const string Account::SITE_DOMAIN = "pakwheels.pk";
int Account::accountTotal = 0;

#endif
