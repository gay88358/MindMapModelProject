#ifndef EDITCOMMAND_H
#define EDITCOMMAND_H


#include "./command.h"
#include "./mindMapModel.h"

class EditCommand : public Command {
public:
    EditCommand(MindMapModel mindMapModel, int id, string description);
    void execute();
    void unexecute();
private:
    MindMapModel _mindMapModel;
    int _targetId;
    string _previousDescription;
    string _modifiedDescription;
};

#endif