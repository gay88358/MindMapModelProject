#include "../include/composite.h"
// #include "../include/mapFactory.h"

#include <iostream>

using std::cout;
using std::endl;

Composite::Composite(): Component(), _parent(nullptr) {
}

Composite::Composite(string description): Component(description), _parent(nullptr) {

}

void Composite::addParent(Component* node) {
    throw invalid_argument("Please overwriten abstract method!!");
}

void Composite::addSibling(Component* node) {
    throw invalid_argument("Please overwriten abstract method!!");
}

bool Composite::isNodeInList(Component *node) {
    bool result = false;
    vector<Component*> list = this->_nodeList;
    for (int i = 0; i < list.size(); i++)
        if (list[i] == node)
            result = true;
    return result;
}

void Composite::releaseParent() {
    this->_parent = nullptr;
}


void Composite::addChildWithIndex(Component *node, int index) {
    if (isNodeInList(node))
        return;
        
    this->_nodeList.insert(this->_nodeList.begin() + index, node);
    node->addParent(this);
}

void Composite::addChild(Component* node) {
    if (isNodeInList(node))
        return;

    this->_nodeList.push_back(node);
    node->addParent(this);
}

string Composite::getMap() {
    string result;
    string indent = "";
    bool last = true;
    formatTreeStructureString(this, indent, last, result);
    return result;
}

void Composite::formatTreeStructureString(Component *root, string indent, bool last, string &result)
{
    result += indent + "+-" + root->getDescription() + "(" + root->getType() + ", ID: " + std::to_string(root->getId()) + ")\n";
    indent += last ? "   " : "|  ";
    vector<Component*> list = root->getNodeList();
    for (int i = 0; i < list.size(); i++) {
        formatTreeStructureString(list[i], indent, i == list.size() - 1, result);
    }
}

int Composite::getPositionFromParentNodeList() {
    int removeIndex = 0;
    vector<Component*> list = this->_parent->getNodeList();
    for (int i = 0; i < list.size(); i++) 
        if (list[i] == this)
            removeIndex = i;
    return removeIndex;
}

Component* Composite::getParent() {
    return this->_parent;
}

vector<Component*> Composite::getNodeList() {
    return this->_nodeList;
}

string Composite::getType() const {
    throw invalid_argument("Please overwriten abstract method!!");
}

void Composite::removeNode(Component* node) {
    _modifier.removeNode(this->_nodeList, node);
}



string Composite::formatMindMap(Component *root) {
    // create hashmap for the root
    MapFactory mapFactory(this);
    map<Component*, set<int>> componentMap = mapFactory.createComponentMap();
    // sorting hashmap
    // iterate hashmap format string 
    string format; 
    for (map<Component*, set<int>>::iterator it= componentMap.begin(); it!= componentMap.end(); ++it) {
        format += std::to_string(it->first->getId()) + " " + it->first->getDescription() + " ";
        set<int> s = it->second;
        cout << it->first->getDescription() << endl;
        for (set<int>::iterator it2 = s.begin(); it2 != s.end(); ++it2) {
            format += std::to_string(*it2);
            format += " ";
        }
        format += "\n";
    }
    return format;
}

bool Composite::deleteNodeById(int id) {
    vector<Component*> list = getNodeList();
    for (int i = 0; i < list.size(); i++) {
        if (list[i]->getId() == id) {
            removeNode(list[i]);
            return true;
        }
    }
    return false;
}

Component* Composite::findNodeById(int id) { // helper method, used to communicate well
    return findNodeById(this, id);
}

Component* Composite::findNodeById(Component *root, int id) {
    cout << "find" << endl;
    MapFactory mapFactory(this);
    map<Component*, set<int>> componentMap = mapFactory.createComponentMap();
    for (map<Component*, set<int>>::iterator it = componentMap.begin(); it != componentMap.end(); ++it)
        if (it->first->getId() == id)
            return it->first;
    return nullptr;
    //throw std::string("The node is not exist!");
}