#ifndef UTNODEMODIFIER_H
#define UTNODEMODIFIER_H

#include <string>
#include <vector>

#include "./include/nodeModifier.h"
#include "./include/component.h"
#include "./include/composite.h"
#include "./include/root.h"
#include "./include/node.h"

using std::vector;
using std::string;
using std::cout;
using std::endl;

TEST(NodeModifier, removeNode) {
    NodeIdCounter::initialize();
    Component *root = new Root();
    Component *node = new Node();
    vector<Component*> list = { root, node };

    NodeModifier *nodeModifier = new NodeModifier(list);
    nodeModifier->removeNode(list, root);

    int result[] = { 1 };
    cout << list.size() << endl;
    for (int i = 0; i < list.size(); i++) {
        ASSERT_EQ(list[i]->getId(), result[i]);
    }
}

#endif