#ifndef NODEMODIFIER_H
#define NODEMODIFIER_H

class Component;

#include <vector>

using std::vector;

class NodeModifier {
public:
    NodeModifier();
    NodeModifier(vector<Component*> &list);
    void removeNode(vector<Component*> &list, Component* node);
private:
    vector<Component*> _list;
};

#endif