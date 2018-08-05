#include "../include/commandManager.h"

CommandManager::CommandManager() {

}

void CommandManager::execute(Command *command) {
    _undoCommands.push(command);
    command->execute();
}

Command* CommandManager::popCommand(stack<Command*> &commands) {
    Command* command = commands.top();
    commands.pop();
    return command;
}

bool CommandManager::undoAble() {
    return _undoCommands.size() != 0;
}

bool CommandManager::redoAble() {
    cout << _redoCommands.size() << endl;
    return _redoCommands.size() != 0;
}

void CommandManager::undo() {
    if (!undoAble()) // guard clause
        throw std::string("Can't not undo!");

    Command *command = popCommand(_undoCommands);
    command->unexecute();
    _redoCommands.push(command);
}

void CommandManager::redo() {
    if (!redoAble())
        throw std::string("Can't not redo!");
        
    Command *command = popCommand(_redoCommands);
    command->execute();
    _undoCommands.push(command);
}