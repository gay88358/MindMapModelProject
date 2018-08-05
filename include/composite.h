#ifndef COMPOSITE_H
#define COMPOSITE_H

#include <map>
#include <set>
#include <iterator>
#include <algorithm>    // std::sort
#include <sstream>

using std::stringstream;
using std::sort;
using std::set;
using std::iterator;
using std::pair;
using std::map;


#include "./component.h"
#include "./nodeModifier.h"
#include "./mapFactory.h"

class Composite : public Component {
public:
    Composite();
    Composite(string description);
    // virtual function
    string getMap();
    void addParent(Component* node);
    void addSibling(Component* node);
    void addChild(Component* node);
    void addChildWithIndex(Component* node, int index);
    vector<Component*> getNodeList();
    virtual string getType() const;
    Component* getParent();

    int getPositionFromParentNodeList();
// unchecked method
    Component* findNodeById(int id);
    string formatMindMap(Component *root);
    void removeNode(Component* node);
    Component* findNodeById(Component *root, int id);
    bool deleteNodeById(int id);
    void releaseParent();    

private:
    void formatTreeStructureString(Component *root, string indent, bool last, string &result);
    bool isNodeInList(Component *node);
protected:
    vector<Component*> _nodeList;
    Component* _parent;
// unchecked variable
    NodeModifier _modifier;    
};

#endif