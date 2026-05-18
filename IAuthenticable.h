#ifndef IAUTHENTICABLE_H
#define IAUTHENTICABLE_H

class IAuthenticable {
public:
    virtual bool confirmIdentity() = 0;
    virtual bool isAuthenticated() const = 0;
    virtual void withdrawAuth() = 0;
    virtual ~IAuthenticable() {}
};

#endif
