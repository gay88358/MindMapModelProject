#include "../include/nodeOperator.h"
#include "../include/mindMapModel.h"
#include <iostream>

using std::endl;
using std::cout;

NodeOperator::NodeOperator(MindMapModel *model): _model(model), _root(model->getRoot()) {
    _root = model->getRoot();
}

void NodeOperator::rememberTarget(int targetId) {
    _deletedTarget = _root->findNodeById(targetId);
    _parentOfDeletedTarget = _deletedTarget->getParent();
    _list = _deletedTarget->getNodeList();
    _removedIndex = getRemovedIndex();
}

int NodeOperator::getRemovedIndex() {
    vector<Component*> list = _parentOfDeletedTarget->getNodeList();
    for (int i = 0; i < list.size(); i++) {
        if (list[i] == _deletedTarget)
            return i;
    }
    return -1;
}

void NodeOperator::deleteNodeById(int id) {
    Component *target = _root->findNodeById(id);
    Component *parentOfTarget = target->getParent();

    rememberTarget(id);
    changeListNodeParentWithIndex(parentOfTarget);
    removeNodeById(id);
}

void NodeOperator::restoreDeletedNodeById(int id) {
    changeListNodeParent(_deletedTarget);
    _parentOfDeletedTarget->addChildWithIndex(_deletedTarget, _removedIndex);
}

void NodeOperator::changeListNodeParent(Component *parentOfTarget) {
    for (int i = 0; i < _list.size(); i++)
        changeParent(_list[i], parentOfTarget);
}

void NodeOperator::changeListNodeParentWithIndex(Component *parentOfTarget) {
    int tempIndex = _removedIndex;
    for (int i = 0; i < _list.size(); i++)
        changeParentWithIndex(_list[i], parentOfTarget, tempIndex++);
}

void NodeOperator::changeParentWithIndex(Component *target, Component *modifiedParent, int index) {
    Component *parentOfTarget = target->getParent();    
    parentOfTarget->removeNode(target);
    modifiedParent->addChildWithIndex(target, index);
}

void NodeOperator::changeParent(Component *target, Component *modifiedParent) {
    Component *parentOfTarget = target->getParent();    
    parentOfTarget->removeNode(target);
    modifiedParent->addChild(target);
}

void NodeOperator::removeNodeById(int id) {
    Component *target = _root->findNodeById(id);
    Component *parentOfTarget = target->getParent();
    parentOfTarget->removeNode(target);
} 


void NodeOperator::changeParent(int targetId, int parentId) {
    Component *target = _root->findNodeById(targetId);
    Component *parentOfTarget = target->getParent();
    Component *modifiedParent = _root->findNodeById(parentId);
    parentOfTarget->removeNode(target);
    modifiedParent->addChild(target);
}
