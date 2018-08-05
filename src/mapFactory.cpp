#include "../include/mapFactory.h"
#include <iostream>

using std::endl;
using std::cout;
MapFactory::MapFactory(Component *root): _root(root) {
}


void MapFactory::insertSetToMap(Component *key) {
    set<int> s;
    _map.insert(pair<Component*, set<int>>(key, s));
}

void MapFactory::insertPairToMap(Component *key, int value) {
    if (_map.find(key) == _map.end()) 
        insertSetToMap(key);
    _map[key].insert(value);
}

map<Component*, set<int>> MapFactory::createComponentMap() {
    cout << "create" << endl;
    createMap(_root);
    return _map;
}

void MapFactory::createMap(Component * root) {
    vector<Component*> list = root->getNodeList();
    if (list.size() == 0) {
        insertSetToMap(root);
        return;
    }

    for (int i = 0; i < list.size(); i++) {
        insertPairToMap(root, list[i]->getId());
        createMap(list[i]);
    }   
}
