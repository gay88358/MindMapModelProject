#ifndef UTNODEOPERATOR_H
#define UTNODEOPERATOR_H


#include "./include/nodeOperator.h"
#include "./include/mindMapModel.h"
#include <iostream>

using std::endl;
using std::cout;
/*
MindMapModel createMindMapModel() {
    NodeIdCounter::initialize();
    MindMapModel model;
    model.createMindMap("Computer"); // 0
    model.insertNode(0, "Windows", "b"); // 1
    model.insertNode(0, "Mac Os", "b"); // 2
    model.insertNode(0, "Linux", "b"); // 3
    model.insertNode(1, "Microsoft", "b");
    model.insertNode(2, "Apple", "b");
    return model;    
}
*/
TEST(NodeOperator, deleteNodeById) {
    MindMapModel model = createMindMapModel();
    Component *root = model.getRoot();
    Component *target = root->findNodeById(1);
    cout << model.showMap() << endl;
    ASSERT_TRUE(target != nullptr);

    NodeOperator nodeOperator(&model);

    nodeOperator.deleteNodeById(1);
    target = root->findNodeById(1);
    cout << model.showMap() << endl;

    ASSERT_EQ(target, nullptr);
    nodeOperator.restoreDeletedNodeById(1);
    target = root->findNodeById(1);
    cout << model.showMap() << endl;
        ASSERT_TRUE(target != nullptr);

}

#endif