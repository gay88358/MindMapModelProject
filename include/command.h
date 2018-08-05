#ifndef COMMAND_H
#define COMMAND_H

#include <stdexcept>      // std::invalid_argument

using std::invalid_argument;

class Command {
public:
    virtual void execute() = 0;
    virtual void unexecute() = 0;
private:
};


#endif