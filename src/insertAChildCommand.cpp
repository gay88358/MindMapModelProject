#include "../include/insertAChildCommand.h"

InsertAChildCommand::InsertAChildCommand(Component *target, Component *insertedChild): _target(target), _insertedChild(insertedChild) {

}

void InsertAChildCommand::execute() {
    _target->addChild(_insertedChild);
}

void InsertAChildCommand::unexecute() {
    _target->removeNode(_insertedChild);
}