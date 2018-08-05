#ifndef INSERTAPARENTCOMMAND_H
#define INSERTAPARENTCOMMAND_H

#include "./command.h"
#include "./mindMapModel.h"

class InsertAParentCommand : public Command {
public:
    InsertAParentCommand(Component *target, Component *insertedNode);
    void execute();
    void unexecute();
private:
    Component* _target;
    Component* _parentOfTarget;
    Component* _insertedNode;
    int _removeTargetIndex;
    MindMapModel _model;
};

#endif