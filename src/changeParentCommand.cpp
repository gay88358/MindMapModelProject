#include "../include/changeParentCommand.h"

#include <iostream>

using std::endl;
using std::cout;


ChangeParentCommand::ChangeParentCommand(MindMapModel mindMapmodel, int targetId, int parentId): _mindMapModel(mindMapmodel),  _targetId(targetId),  _modifiedParentId(parentId), _previousParentId(_mindMapModel.getParentId(_targetId)) {
} 

void ChangeParentCommand::execute() {
    _mindMapModel.changeParent(_targetId, _modifiedParentId);
}

void ChangeParentCommand::unexecute() {
    _mindMapModel.changeParent(_targetId, _previousParentId);
}