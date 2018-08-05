#ifndef MAPFACTORY_H
#define MAPFACTORY_H

#include <map>
#include <set>
#include <iterator>
#include <algorithm>    // std::sort
#include <sstream>
#include "./component.h"

using std::stringstream;
using std::sort;
using std::set;
using std::iterator;
using std::pair;
using std::map;

class MapFactory {
public:
    MapFactory(Component* root);
    map<Component*, set<int>> createComponentMap();
private:
    struct CmpByKeyId 
    :
    public std::binary_function <bool, Component, Component>
    {
    bool operator() (const Component& c1, const Component& c2)
    {
        return c1.getId() < c2.getId();  
    }
    };
/*
    struct CmpByKeyId {  
        bool operator() (const Component& c1, const Component& c2) {  
            return c1.getId() < c2.getId();  
        }  
    };  */

    void createMap(Component * root);
    void insertPairToMap(Component *key, int value);
    void insertSetToMap(Component *key);
    Component *_root;
    //map<Component*, set<int>, CmpByKeyId> _map;
    map<Component*, set<int>> _map;
};

#endif