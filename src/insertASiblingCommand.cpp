#include "../include/insertASiblingCommand.h"


InsertASiblingCommand::InsertASiblingCommand(Component *target, Component *sibling): _target(target), _sibling(sibling) {

}

void InsertASiblingCommand::execute() {
    _target->addSibling(_sibling);
}

void InsertASiblingCommand::unexecute() {
    _target->getParent()->removeNode(_sibling);
}