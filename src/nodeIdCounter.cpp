#include "../include/nodeIdCounter.h"


int NodeIdCounter::_id = 0;

NodeIdCounter::NodeIdCounter() {

}

int NodeIdCounter::getId() {
    int id = _id;
    increment();
    return id;
}

void NodeIdCounter::increment() {
    _id++;
}

void NodeIdCounter::initialize() {
    _id = 0;
}

