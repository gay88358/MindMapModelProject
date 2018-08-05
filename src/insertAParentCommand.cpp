#include "../include/insertAParentCommand.h"

InsertAParentCommand::InsertAParentCommand(Component *target, Component *insertedNode): _target(target), _parentOfTarget(target->getParent()), _insertedNode(insertedNode), _removeTargetIndex(_target->getPositionFromParentNodeList()) {
}

void InsertAParentCommand::execute() {
    _target->addParent(_insertedNode);
}

void InsertAParentCommand::unexecute() {
    _insertedNode->removeNode(_target);
    _parentOfTarget->removeNode(_insertedNode);
    _parentOfTarget->addChildWithIndex(_target, _removeTargetIndex);
}