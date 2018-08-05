#ifndef DELETECOMMAND_H
#define DELETECOMMAND_H

#include "./command.h"
#include "./mindMapModel.h"

class DeleteCommand : public Command {
public:
    DeleteCommand(MindMapModel mindMapModel, int targetId);
    void execute();
    void unexecute();
private:
    MindMapModel _mindMapModel;
    int _targetId;
};

#endif