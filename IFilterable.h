#ifndef IFILTERABLE_H
#define IFILTERABLE_H

#include <string>
using namespace std;

class IFilterable {
public:
    virtual bool checkKeyword(const string& term) const = 0;
    virtual string getIndexedContent() const = 0;
    virtual ~IFilterable() {}
};

#endif
