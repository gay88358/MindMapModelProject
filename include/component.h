#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include "./nodeIdCounter.h"

using std::string;
using std::vector;
using std::stringstream;
using std::invalid_argument;

class Component {
public:
    Component();
    Component(string description);
    int getId() const;
    void setDescription(string description);
    string getDescription() const;
    virtual string getMap();
    virtual void addChild(Component* node);
    virtual void addChildWithIndex(Component* node, int index);
    virtual void addParent(Component* node);
    virtual void addSibling(Component* node);
    virtual vector<Component*> getNodeList();
    virtual string getType() const;
    virtual Component* getParent();

    virtual int getPositionFromParentNodeList();

    virtual void releaseParent();    
    
    virtual bool deleteNodeById(int id);
    virtual Component* findNodeById(int id);
    virtual Component* findNodeById(Component *root, int id);
    virtual void removeNode(Component* node);
    virtual string formatMindMap(Component *root);

// unchecked method
    bool operator<(const Component &right) const; 
protected:
    int _id;
    string _description;
};

#endif