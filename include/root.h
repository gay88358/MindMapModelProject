#ifndef ROOT_H
#define ROOT_H

#include "./composite.h"

class Root : public Composite {
public:
    Root();
    Root(string description);
    string getType() const;
    int getPositionFromParentNodeList();
};

#endif