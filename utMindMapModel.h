#ifndef UTMINDMAPMODEL_H
#define UTMINDMAPMODEL_H

#include "./include/mindMapModel.h"
#include "./include/component.h"
#include <iostream>

using std::cout;
using std::endl;

TEST(MindMapModel, createMindMap) {
    MindMapModel model;
    model.createMindMap("Computer");
    Component *root = model.getRoot();
    ASSERT_EQ("Root", root->getType());
    ASSERT_EQ("Computer", root->getDescription());
}

TEST(MindMapModel, createNode) {
    MindMapModel model;
    Component* node = model.createNode("Windows");
    ASSERT_EQ("Node", node->getType());
    ASSERT_EQ("Windows", node->getDescription());
}

TEST(MindMapModel, insertNode) {
    NodeIdCounter::initialize();
    MindMapModel model;
    model.createMindMap("Computer");
    model.insertNode(0, "Windows", "b");
    model.insertNode(1, "mouse", "a");
    model.insertNode(2, "keyboard", "c");

    // model.insertNode(0, "sss", 0);
    // 0: parent 1: child 2: sibling
    string result = "+-Computer(Root, ID: 0)\n   +-mouse(Node, ID: 2)\n   |  +-Windows(Node, ID: 1)\n   +-keyboard(Node, ID: 3)\n";
    ASSERT_EQ(result, model.showMap());
}

TEST(MindMapModel, editNodeDescription) {
    NodeIdCounter::initialize();
    MindMapModel model;
    model.createMindMap("Computer");
    model.insertNode(0, "Windows", "b");

    model.editNodeDescription(1, "Mac OS");

    Component *root = model.getRoot();
    Component *target = root->findNodeById(root, 1);
    ASSERT_EQ(target->getDescription(), "Mac OS");
}




TEST(MindMapModel, changeParent) {
    MindMapModel model = createMindMapModel();
    cout << model.showMap() << endl;

    Component *root = model.getRoot();
    Component *target = root->findNodeById(2);
    ASSERT_EQ(target->getParent()->getDescription(), "Computer");

    // changeParent(int targetId, int parentId)
    model.changeParent(2, 4);
    cout << model.showMap() << endl;

    ASSERT_EQ(target->getParent()->getDescription(), "Microsoft");

    model.changeParent(2, 0);
    cout << model.showMap() << endl;

    ASSERT_EQ(target->getParent()->getDescription(), "Computer");

}

TEST(MindMapModel, TestGetParentId) {
    MindMapModel model = createMindMapModel();

    int id = model.getParentId(5);
    ASSERT_EQ(id, 2);
    
    id = model.getParentId(4);
    ASSERT_EQ(id, 1);
    
    id = model.getParentId(2);
    ASSERT_EQ(id, 0);
    
    id = model.getParentId(3);
    ASSERT_EQ(id, 0);
}

TEST(MindMapModel, TestGetParentIdBoundary) {
    MindMapModel model = createMindMapModel();
    int id = model.getParentId(0);
    ASSERT_EQ(id, -1);
}

TEST(MindMapModel, TestFindNodeById) {
    MindMapModel model = createMindMapModel();
    Component* node = model.findNodeById(0);
    ASSERT_EQ("Computer", node->getDescription());
    node = model.findNodeById(1);

    ASSERT_EQ("Windows", node->getDescription());
    node = model.findNodeById(2);

    ASSERT_EQ("Mac Os", node->getDescription());
    node = model.findNodeById(3);

    ASSERT_EQ("Linux", node->getDescription());
    node = model.findNodeById(4);

    ASSERT_EQ("Microsoft", node->getDescription());
    node = model.findNodeById(5);

    ASSERT_EQ("Apple", node->getDescription());


}

TEST(MindMapModel, TestDeleteMethod) {
    MindMapModel model = createMindMapModel();
    cout << model.showMap() << endl;
    Component *node = model.findNodeById(1);
    ASSERT_EQ(node->getDescription(), "Windows");
    
    model.deleteById(1);
    node = model.findNodeById(1);
    ASSERT_EQ(node, nullptr);
    cout << model.showMap() << endl;

    model.restoreDeletedNodeById(1);
    cout << model.showMap() << endl;
    node = model.findNodeById(1);
    ASSERT_EQ(node->getDescription(), "Windows");
    

}

TEST(MindMapModel, saveTheMindMap) {
    NodeIdCounter::initialize();
    MindMapModel model;
    model.createMindMap("Computer");
    model.insertNode(0, "Windows", "b");
    model.insertNode(0, "osx", "b");
    model.insertNode(1, "ausu", "b");
    model.insertNode(2, "mba", "b");
    cout << model.showMap() << endl;
    model.saveMindMap();

    FileManager file;
    vector<string> result = file.readFile("mindMap.txt");
    for (int i = 0; i < result.size(); i++)
        cout << result[i] << endl;
}

TEST(MindMapModel, editNodeDescriptionWithCommandManager) {
    NodeIdCounter::initialize();
    MindMapModel model;
    model.createMindMap("Computer");
    model.insertNode(0, "Windows", "b");
    model.insertNode(0, "osx", "b");
    model.insertNode(1, "ausu", "b");
    model.insertNode(2, "mba", "b");
    cout << model.showMap() << endl;
    int targetId = 4;
    ASSERT_EQ(model.findNodeById(targetId)->getDescription(), "mba");
    string description = "mbpr";
    model.editNodeDescriptionCommand(targetId, description);
    ASSERT_EQ(model.findNodeById(targetId)->getDescription(), "mbpr");
}

TEST(MindMapModel, editNodeDescriptionWithUndoAndReDo) {
    NodeIdCounter::initialize();
    MindMapModel model;
    model.createMindMap("Computer");
    model.insertNode(0, "Windows", "b");
    model.insertNode(0, "osx", "b");
    model.insertNode(1, "ausu", "b");
    model.insertNode(2, "mba", "b");
    cout << model.showMap() << endl;
    int targetId = 4;
    ASSERT_EQ(model.findNodeById(targetId)->getDescription(), "mba");
    string description = "mbpr";
    model.editNodeDescriptionCommand(targetId, description);
    ASSERT_EQ(model.findNodeById(targetId)->getDescription(), "mbpr");

    model.undo();
    ASSERT_EQ(model.findNodeById(targetId)->getDescription(), "mba");

    model.redo();
    ASSERT_EQ(model.findNodeById(targetId)->getDescription(), "mbpr");

    model.undo();
    ASSERT_EQ(model.findNodeById(targetId)->getDescription(), "mba");

    model.redo();
    ASSERT_EQ(model.findNodeById(targetId)->getDescription(), "mbpr");
}

TEST(MindMapModel, changeNodeParentCommand) {
    NodeIdCounter::initialize();
    MindMapModel model;
    model.createMindMap("Computer");
    model.insertNode(0, "Windows", "b");
    model.insertNode(0, "osx", "b");
    model.insertNode(1, "ausu", "b");
    model.insertNode(2, "mba", "b");
    cout << model.showMap() << endl;
    int targetId = 1;
    int parentId = 2;
    ASSERT_EQ(model.findNodeById(targetId)->getParent()->getDescription(), "Computer");
    model.changeNodeParentCommand(targetId, parentId);
    ASSERT_EQ(model.findNodeById(targetId)->getParent()->getDescription(), "osx");
    cout << model.showMap() << endl;
}

TEST(MindMapModel, changeNodeParentCommandWithUndoAndRedo) {
    NodeIdCounter::initialize();
    MindMapModel model;
    model.createMindMap("Computer");
    model.insertNode(0, "Windows", "b");
    model.insertNode(0, "osx", "b");
    model.insertNode(1, "ausu", "b");
    model.insertNode(2, "mba", "b");
    cout << model.showMap() << endl;
    int targetId = 1;
    int parentId = 2;
    ASSERT_EQ(model.findNodeById(targetId)->getParent()->getDescription(), "Computer");
    model.changeNodeParentCommand(targetId, parentId);
    ASSERT_EQ(model.findNodeById(targetId)->getParent()->getDescription(), "osx");

    model.undo();
    ASSERT_EQ(model.findNodeById(targetId)->getParent()->getDescription(), "Computer");

    model.redo();
    ASSERT_EQ(model.findNodeById(targetId)->getParent()->getDescription(), "osx");
    
    model.undo();
    ASSERT_EQ(model.findNodeById(targetId)->getParent()->getDescription(), "Computer");

    model.redo();
    ASSERT_EQ(model.findNodeById(targetId)->getParent()->getDescription(), "osx");
}

TEST(MindMapModel, deleteNodeCommand) {
    NodeIdCounter::initialize();
    MindMapModel model;
    model.createMindMap("Computer");
    model.insertNode(0, "Windows", "b");
    model.insertNode(0, "osx", "b");
    model.insertNode(1, "ausu", "b");
    model.insertNode(2, "mba", "b");
    cout << model.showMap() << endl;
    int targetId = 1;
    Component *target = model.findNodeById(targetId);
    ASSERT_TRUE(target != nullptr);

    model.deleteNodeCommand(targetId);
    cout << model.showMap() << endl;
    target = model.findNodeById(targetId);
    ASSERT_EQ(target, nullptr);
}

TEST(MindMapModel, deleteNodeCommandWithUndoAndRedo) {
    NodeIdCounter::initialize();
    MindMapModel model;
    model.createMindMap("Computer");
    model.insertNode(0, "Windows", "b");
    model.insertNode(0, "osx", "b");
    model.insertNode(1, "ausu", "b");
    model.insertNode(2, "mba", "b");
    cout << model.showMap() << endl;
    int targetId = 1;
    Component *target = model.findNodeById(targetId);
    ASSERT_TRUE(target != nullptr);

    model.deleteNodeCommand(targetId);
    cout << model.showMap() << endl;
    target = model.findNodeById(targetId);
    ASSERT_EQ(target, nullptr);

    model.undo();
    target = model.findNodeById(targetId);
    ASSERT_TRUE(target != nullptr);

    model.redo();
    target = model.findNodeById(targetId);
    ASSERT_EQ(target, nullptr);



}
#endif