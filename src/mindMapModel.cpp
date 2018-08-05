#include "../include/mindMapModel.h"
#include <iostream>

#include "../include/editCommand.h"
#include "../include/changeParentCommand.h"
#include "../include/deleteCommand.h"

#include "../include/insertAParentCommand.h"
#include "../include/insertAChildCommand.h"
#include "../include/insertASiblingCommand.h"

using std::cout;
using std::endl;

MindMapModel::MindMapModel():_root(nullptr), _nodeOperator(nullptr) {
}

void MindMapModel::createMindMap(string description) {
    this->_root = this->_factory.createRoot(description);
}

Component* MindMapModel::getRoot() {
    return this->_root;
}

Component* MindMapModel::createNode(string name) {
    return this->_factory.createNode(name);
}

void MindMapModel::editNodeDescription(int id, string name) {
    Component *target = _root->findNodeById(id);
    target->setDescription(name);
}

string MindMapModel::getDescriptionById(int id) const {
    Component *target = _root->findNodeById(id);
    return target->getDescription();
}

Command* createCommand(string insertType, Component *target, Component *node) {
    if (insertType == "a") { // parent
        return new InsertAParentCommand(target, node);
    } else if (insertType == "b") { // child
        return new InsertAChildCommand(target, node);
    } else if (insertType == "c") { // sibling
        return new InsertASiblingCommand(target, node);
    } 

    throw std::string("invalie input type");
}


void MindMapModel::insertNode(int id, string name, string insertType) {
    
    Component *target = _root->findNodeById(id);
    if (target == nullptr)
        return;

    Component *node = createNode(name);
    _commandManager.execute(createCommand(insertType, target, node));
}

void MindMapModel::saveMindMap() {
    _fileManager.writeFile("mindMap.txt", this->_root->formatMindMap(this->_root));
}

string MindMapModel::showMap() {
    if (this->_root == nullptr)
        throw std::string("There is not mindMap to show!");
    return this->_root->getMap();
}

void MindMapModel::editNodeDescriptionCommand(int targetId, string description) {
    Command *command = new EditCommand(*this, targetId, description);
    this->_commandManager.execute(command);
}


void MindMapModel::changeNodeParentCommand(int targetId, int parentId) {
    Command *command = new ChangeParentCommand(*this, targetId, parentId);
    this->_commandManager.execute(command);
}

void MindMapModel::deleteNodeCommand(int targetId) {
    MindMapModel model = *this;
    Command *command = new DeleteCommand(model, targetId);
    this->_commandManager.execute(command);
}

void MindMapModel::undo() {
    this->_commandManager.undo();
}

void MindMapModel::loadMindMap(string path) {
    vector<string> mindMaps = _fileManager.readFile("mindMap.txt");
    vector<vector<string>> mindMaptokens;
    for (int i = 0; i < mindMaps.size(); i++) {
        string mindMapChip = mindMaps[i];
        mindMaptokens.push_back(_fileManager.split(mindMapChip, ' '));
    }
    this->_root = this->_componentFactory.createComponent(mindMaptokens);
}


void MindMapModel::redo() {
    this->_commandManager.redo();
}

Component* MindMapModel::findNodeById(int id) {
    if (_root == nullptr)
        return nullptr;
    return _root->findNodeById(id);
}

NodeOperator* MindMapModel::createNodeOperator() {
    if (_nodeOperator == nullptr)
        _nodeOperator = new NodeOperator(this);
    return _nodeOperator;
}

void MindMapModel::deleteById(int targetId) {
    createNodeOperator()->deleteNodeById(targetId);
}

void MindMapModel::restoreDeletedNodeById(int targetId) {
    createNodeOperator()->restoreDeletedNodeById(targetId);
}

int MindMapModel::getParentId(int id) {
    if (id == 0) // because it is root's id and root doesn't has parent
        return -1;
    return _root->findNodeById(id)->getParent()->getId();
}

void MindMapModel::changeParent(int targetId, int parentId) {
    createNodeOperator()->changeParent(targetId, parentId);
}



