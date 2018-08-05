#include "../include/componentFactory.h"
#include <iostream>

using std::endl;
using std::cout;


ComponentFactory::ComponentFactory() {

}

Component* ComponentFactory::createComponentByToken(vector<string> mindMap) {
    string id = mindMap[0];
    string descriptionName = mindMap[1];
    bool isRoot = (id == "0");
    return (isRoot) ? _nodeFactory.createRoot(descriptionName) : _nodeFactory.createNode(descriptionName);
}

void ComponentFactory::insertChildValueToMap(vector<string> mindMap, Component* component) {
    for (int i = 2; i < mindMap.size(); i++) {
        int value = atoi(mindMap[i].c_str());
        insertPairToMap(component, value);
    }
}

void ComponentFactory::setupComponentMap(vector<vector<string>> mindMapToken) {
    for (int i = 0; i < mindMapToken.size(); i++) {
        vector<string> mindMap = mindMapToken[i];
        Component *component = createComponentByToken(mindMap);
        insertSetToMap(component);
        insertChildValueToMap(mindMap, component);
    }
}

void ComponentFactory::insertChildToNodeFromSet(Component *node, set<int> s) {
    for (set<int>::iterator it2 = s.begin(); it2 != s.end(); ++it2) {
        Component* child = getComponentByIdFromMap((*it2));
        node->addChild(child);
    }
}

void ComponentFactory::formatingTreeStructureComponent() {
    for (map<Component*, set<int>>::iterator it= _map.begin(); it!= _map.end(); ++it) {
        Component *node = it->first; 
        set<int> s = it->second;
        insertChildToNodeFromSet(node, s);
    }
}

Component* ComponentFactory::getTreeStructureComponent() {
    const int ROOT_VALUE = 0;
    return getComponentByIdFromMap(ROOT_VALUE);
}

Component* ComponentFactory::createTreeStructureComponent() {
    formatingTreeStructureComponent();
    return getTreeStructureComponent();
}

Component* ComponentFactory::createComponent(vector<vector<string>> mindMapToken) {
    setupComponentMap(mindMapToken);
    Component *root = createTreeStructureComponent();
    return root;
}

Component* ComponentFactory::getComponentByIdFromMap(int index) {
    for (map<Component*, set<int>>::iterator it= _map.begin(); it!= _map.end(); ++it) {
        Component *component = it->first;
        if (component->getId() == index)
            return component;
    }
    return nullptr;
}

void ComponentFactory::insertSetToMap(Component *key) {
    set<int> s;
    _map.insert(pair<Component*, set<int>>(key, s));
}

void ComponentFactory::insertPairToMap(Component *key, int value) {
    if (_map.find(key) == _map.end()) 
        insertSetToMap(key);
    _map[key].insert(value);
}