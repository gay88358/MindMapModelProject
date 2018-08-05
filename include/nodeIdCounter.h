#ifndef NODEIDCOUNTER_H
#define NODEIDCOUNTER_H

class NodeIdCounter {
public:
    NodeIdCounter();
    static int getId();
    static void increment();
    static void initialize();
private:
    static int _id;
};

#endif