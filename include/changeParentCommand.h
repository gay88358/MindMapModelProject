#ifndef CHANGEPARENTCOMMAND_H
#define CHANGEPARENTCOMMAND_H


#include "./command.h"
#include "./mindMapModel.h"

class ChangeParentCommand : public Command {
public:
    ChangeParentCommand(MindMapModel mindMapModel, int targetId, int parentId);
    void execute();
    void unexecute();
private:
    MindMapModel _mindMapModel;
    int _targetId;
    int _previousParentId;
    int _modifiedParentId;
};

#endif