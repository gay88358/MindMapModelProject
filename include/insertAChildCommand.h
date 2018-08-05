#ifndef INSERTACHILDCOMMAND_H
#define INSERTACHILDCOMMAND_H
#include "./command.h"
#include "./component.h"

class InsertAChildCommand : public Command {
public:
    InsertAChildCommand(Component* target, Component*insertedChild);
    void execute();
    void unexecute();
private:
    Component* _target;
    Component* _insertedChild;
};


#endif