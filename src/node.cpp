#include "../include/node.h"
#include <iostream>

using std::cout;
using std::endl;

Node::Node(): Composite() {

}

Node::Node(string description): Composite(description) {

}


void Node::addParent(Component* node) {
    if (this->_parent != nullptr) {
        Component *p = this->_parent;
        /*
        int removeIndex = 0;
        vector<Component*> list = p->getNodeList();
        for (int i = 0; i < list.size(); i++) {
            if (list[i] == this)
                removeIndex = i;
        }*/
        int removeIndex = getPositionFromParentNodeList();

        p->removeNode(this);
        p->addChildWithIndex(node, removeIndex);
        node->addChild(this);
    }
    this->_parent = node;
}

void Node::addSibling(Component* node) {
    int index = getPositionFromParentNodeList();
    int siblingIndex = index + 1;
    this->_parent->addChildWithIndex(node, siblingIndex);
}

string Node::getType() const {
    return "Node";
}

