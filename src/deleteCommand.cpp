#include "../include/deleteCommand.h"
#include <iostream>

using std::cout;
using std::endl;

DeleteCommand::DeleteCommand(MindMapModel mindMapModel, int targetId): _mindMapModel(mindMapModel), _targetId(targetId) {
}

void DeleteCommand::execute() {
   _mindMapModel.deleteById(_targetId);
}

void DeleteCommand::unexecute() {
    _mindMapModel.restoreDeletedNodeById(_targetId);
}