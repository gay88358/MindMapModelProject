#ifndef INSERTASIBLINGCOMMAND_H
#define INSERTASIBLINGCOMMAND_H
#include "./command.h"
#include "./component.h"

class InsertASiblingCommand : public Command {
public:
    InsertASiblingCommand(Component * tatget, Component *sibling);
    void execute();
    void unexecute();
private:
    Component *_target;
    Component *_sibling;
};


#endif