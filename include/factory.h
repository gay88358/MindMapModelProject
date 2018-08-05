#ifndef FACTORY_H
#define FACTORY_H

#include "./node.h"
#include "./root.h"

class Factory {
public:
    Factory();
    Component* createNode(string description);
    Component* createRoot(string description);
};

#endif