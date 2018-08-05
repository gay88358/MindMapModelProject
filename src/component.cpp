#include "../include/component.h"
#include <iostream>
using std::endl;
using std::cout;

Component::Component(): _description(""), _id(NodeIdCounter::getId()) {
}

Component::Component(string description): _description(description), _id(NodeIdCounter::getId()) {

}

int Component::getId() const {
    return this->_id;
}

void Component::setDescription(string description) {
    this->_description = description;
}

vector<Component*> Component::getNodeList() {
    throw invalid_argument("Please overwriten abstract method!!");
}

int Component::getPositionFromParentNodeList() {
    throw invalid_argument("Please overwriten abstract method!!");
}

void Component::releaseParent() {
    throw invalid_argument("Please overwriten abstract method!!");
}

void Component::addChild(Component *component) {
    throw invalid_argument("Please overwriten abstract method!!");
}

void Component::addChildWithIndex(Component *component, int index) {
    throw invalid_argument("Please overwriten abstract method!!");
}

void Component::addParent(Component* node) {
    throw invalid_argument("Please overwriten abstract method!!");
}

void Component::addSibling(Component* node) {
    throw invalid_argument("Please overwriten abstract method!!");
}

Component* Component::getParent() {
    throw invalid_argument("Please overwriten abstract method!!");
}

string Component::getMap() {
    throw invalid_argument("Please overwriten abstract method!!");
}

Component* Component::findNodeById(int id) {
    throw invalid_argument("Please overwriten abstract method!!");
}
    

Component* Component::findNodeById(Component *root, int id) {
    throw invalid_argument("Please overwriten abstract method!!");
}

string Component::getDescription() const {
    return this->_description;
}

string Component::getType() const {
    throw invalid_argument("Please overwriten abstract method!!");
}

bool Component::deleteNodeById(int id) {
    throw invalid_argument("Please overwriten abstract method!!");
}


void Component::removeNode(Component* node) {
    throw invalid_argument("Please overwriten abstract method!! removeNode");
}

string Component::formatMindMap(Component *root) {
    throw invalid_argument("Please overwriten abstract method!!");
}

bool Component::operator<(const Component &right) const {
    cout << "compare" << endl;
    return this->_id < right.getId();
}