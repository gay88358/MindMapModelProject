#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include <stack>
#include <iostream>
#include "./command.h"

using std::cout;
using std::endl;
using std::stack;

class CommandManager {
public:
    CommandManager();
    void execute(Command *command);
    void undo();
    void redo();
private:
    bool undoAble();
    bool redoAble();
    Command* popCommand(stack<Command*> &commands);
    stack<Command*> _undoCommands;
    stack<Command*> _redoCommands;
};


#endif