#ifndef COMPONENTFACTORY_H
#define COMPONENTFACTORY_H

#include "./factory.h"
#include <vector>

using std::vector;

class ComponentFactory {
public:
    ComponentFactory();
    Component* createComponent(vector<vector<string>>);
private:
    Component* getTreeStructureComponent();
    void insertChildToNodeFromSet(Component *node, set<int> s);
    void insertChildValueToMap(vector<string> mindMap, Component* component);
    Component* createComponentByToken(vector<string> mindMap);
    Component* createTreeStructureComponent();
    void formatingTreeStructureComponent();
    void setupComponentMap(vector<vector<string>> mindMapToken);
    void insertSetToMap(Component *key);
    void insertPairToMap(Component *key, int value);
    Component* getComponentByIdFromMap(int index);
    Factory _nodeFactory;
    map<Component*, set<int>> _map;
 };

#endif