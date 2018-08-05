#include "../include/editCommand.h"
#include <iostream>

using std::cout;
using std::endl;

EditCommand::EditCommand(MindMapModel mindMapModel, int id, string description): _mindMapModel(mindMapModel), _targetId(id), _modifiedDescription(description) {
    _previousDescription = _mindMapModel.getDescriptionById(id);
}

void EditCommand::execute() {
    _mindMapModel.editNodeDescription(_targetId, _modifiedDescription);
}

void EditCommand::unexecute() {
    _mindMapModel.editNodeDescription(_targetId, _previousDescription);
}