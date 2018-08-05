#ifndef UTNODEIDCOUNTER_H
#define UTNODEIDCOUNTER_H

#include "./include/nodeIdCounter.h"

#include "./include/fileManager.h"
TEST(FileManager, writeFile) {
    FileManager file;
    file.writeFile("test.txt", "this is my first test");
}

TEST(NodeIdCounter, IncrementIdAutomatic) {
    NodeIdCounter::initialize();
    NodeIdCounter *counter = new NodeIdCounter();
    int id = counter->getId();

    ASSERT_EQ(id, 0);

    id = counter->getId();

    ASSERT_EQ(id, 1);

    id = counter->getId();

    ASSERT_EQ(id, 2);
}

#endif