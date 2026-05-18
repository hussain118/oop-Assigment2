#ifndef IVALUABLE_H
#define IVALUABLE_H

class IValuable {
public:
    virtual double fetchCost() const = 0;
    virtual void assignCost(double cost) = 0;
    virtual bool fitsWithinBudget(double limit) const = 0;
    virtual ~IValuable() {}
};

#endif
