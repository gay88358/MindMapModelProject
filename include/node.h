#ifndef NODE_H
#define NODE_H

#include "./composite.h"

class Node : public Composite {
public:
    Node();
    Node(string description);
    void addParent(Component* node);
    void addSibling(Component* node);
    string getType() const;
private:
    void setParent(Component *node);
};

#endif