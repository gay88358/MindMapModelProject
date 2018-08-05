#ifndef UTCOMMAND_H
#define UTCOMMAND_H


#include "./include/command.h"
#include <iostream>
#include <string>
#include <stdexcept>      // std::invalid_argument
#include "./include/mindMapModel.h"
#include "./include/editCommand.h"
#include "./include/changeParentCommand.h"
#include "./include/deleteCommand.h"
#include "./include/insertAParentCommand.h"
#include "./include/insertAChildCommand.h"
#include "./include/insertASiblingCommand.h"


using std::string;
using std::cout;
using std::endl;
using std::invalid_argument;

TEST(EditCommand, execute) {
    NodeIdCounter::initialize();

    MindMapModel mapModel;
    // id: ...., description
    mapModel.createMindMap("Computer");
    mapModel.insertNode(0, "os", "b");

    Command *editCmd = new EditCommand(mapModel, 1, "Mac Os");
    editCmd->execute();

    Component *root = mapModel.getRoot();
    Component *target = root->findNodeById(root, 1);
    ASSERT_EQ(target->getDescription(), "Mac Os");
}

TEST(EditCommand, unexecute) {
    NodeIdCounter::initialize();
    MindMapModel mapModel;
    // id: ...., description
    mapModel.createMindMap("Computer");
    mapModel.insertNode(0, "os", "b");
    Command *editCmd = new EditCommand(mapModel, 1, "Mac Os");
    editCmd->execute();

    Component *root = mapModel.getRoot();
    Component *target = root->findNodeById(root, 1);
    ASSERT_EQ(target->getDescription(), "Mac Os");

    editCmd->unexecute();

    target = root->findNodeById(root, 1);
    ASSERT_EQ(target->getDescription(), "os");
}

TEST(ChangeParentCommand, change_parent_command_execute) {
    NodeIdCounter::initialize();
    MindMapModel mapModel;
    // id: ...., description
    mapModel.createMindMap("Computer");
    mapModel.insertNode(0, "os", "b");
    mapModel.insertNode(0, "window", "b");
    mapModel.insertNode(2, "keyboard", "b");
    mapModel.insertNode(2, "mouse", "b");
    string map = mapModel.showMap();
    cout << map << endl;
    // (targetId, parentId)
    Command *changeParentCommand = new ChangeParentCommand(mapModel, 2, 1);
    changeParentCommand->execute();
    Component *root = mapModel.getRoot();
    Component *target = root->findNodeById(root, 2);

    cout << target << endl;
    map = mapModel.showMap();
    cout << map << endl;
    ASSERT_EQ("os", target->getParent()->getDescription());

    changeParentCommand->unexecute();
    map = mapModel.showMap();

    cout << map << endl;
    ASSERT_EQ("Computer", target->getParent()->getDescription());
}

TEST(ChangeParentCommand, change_parent_2) {
    NodeIdCounter::initialize();
    MindMapModel mapModel;
    // id: ...., description
    mapModel.createMindMap("Computer");
    mapModel.insertNode(0, "os", "b");
    mapModel.insertNode(0, "window", "b");
    mapModel.insertNode(2, "keyboard", "b");
    mapModel.insertNode(2, "mouse", "b");
    string map = mapModel.showMap();
    cout << map << endl;

    Command *changeParentCommand = new ChangeParentCommand(mapModel, 4, 0);
    changeParentCommand->execute();

    Component *root = mapModel.getRoot();
    Component *target = root->findNodeById(root, 4);

    map = mapModel.showMap();
    cout << map << endl;
    ASSERT_EQ("Computer", target->getParent()->getDescription());

    changeParentCommand->unexecute();

    map = mapModel.showMap();

    cout << map << endl;
    ASSERT_EQ("window", target->getParent()->getDescription());
}

TEST(DeleteCommand, delete_command_execute) {
    NodeIdCounter::initialize();

    MindMapModel mapModel;
    // id: ...., description
    mapModel.createMindMap("Computer");
    mapModel.insertNode(0, "os", "b");
    mapModel.insertNode(0, "window", "b");
    mapModel.insertNode(2, "keyboard", "b");
    mapModel.insertNode(2, "mouse", "b");
    string map = mapModel.showMap();
    cout << map << endl;

    //Component *target = root->findNodeById(root, 2);
    //Component *targetParent = target->getParent();
    Command *deleteCommand = new DeleteCommand(mapModel, 2);
    //cout << root << endl;
    deleteCommand->execute();
    map = mapModel.showMap();
    cout << map << endl;

    Component *root = mapModel.getRoot();
    Component *target = root->findNodeById(root, 2);
    ASSERT_EQ(target, nullptr);

    //vector<Component*> list = targetParent->getNodeList();

}

TEST(DeleteCommand, delete_command_unexecute) {
    NodeIdCounter::initialize();

    MindMapModel mapModel;
    // id: ...., description
    mapModel.createMindMap("Computer");
    mapModel.insertNode(0, "os", "b");
    mapModel.insertNode(0, "window", "b");
    mapModel.insertNode(2, "keyboard", "b");
    mapModel.insertNode(2, "mouse", "b");
    string map = mapModel.showMap();
    cout << map << endl;

    //Component *target = root->findNodeById(root, 2);
    //Component *targetParent = target->getParent();
    Command *deleteCommand = new DeleteCommand(mapModel, 2);
    deleteCommand->execute();
    
    map = mapModel.showMap();
    cout << map << endl;

    deleteCommand->unexecute();

    map = mapModel.showMap();
    cout << map << endl;

}

TEST(DeleteCommand, delete_complex_execute) {
    NodeIdCounter::initialize();

    MindMapModel mapModel;
    // id: ...., description
    mapModel.createMindMap("Computer");
    mapModel.insertNode(0, "os", "b");
    mapModel.insertNode(0, "window", "b");
    mapModel.insertNode(2, "keyboard", "b");
    mapModel.insertNode(2, "mouse", "b");
    mapModel.insertNode(3, "good", "b");
    mapModel.insertNode(3, "noGood", "b");
    string map = mapModel.showMap();
    cout << map << endl;
    
    Command *deleteCommand = new DeleteCommand(mapModel, 3);
    deleteCommand->execute();
    
    map = mapModel.showMap();
    cout << map << endl;

    deleteCommand->unexecute();

    map = mapModel.showMap();
    cout << map << endl;

}

TEST(DeleteCommand, delete_complex_execute2) {
    NodeIdCounter::initialize();

    MindMapModel mapModel;
    // id: ...., description
    mapModel.createMindMap("Computer"); 
    mapModel.insertNode(0, "os", "b");
    mapModel.insertNode(0, "window", "b");
    mapModel.insertNode(0, "linux", "b");

    mapModel.insertNode(2, "keyboard", "b");
    mapModel.insertNode(2, "mouse", "b");
    mapModel.insertNode(2, "good", "b");
    string map = mapModel.showMap();
    cout << map << endl;
    
    Command *deleteCommand = new DeleteCommand(mapModel, 2);
    deleteCommand->execute();
    
    map = mapModel.showMap();
    cout << map << endl;

    deleteCommand->unexecute();

    map = mapModel.showMap();
    cout << map << endl;
}

TEST(Command, InsertAParentfddNodeCmd) {
    NodeIdCounter::initialize();
    MindMapModel mapModel;
    mapModel.createMindMap("Computer"); 
    mapModel.insertNode(0, "os", "b");
    mapModel.insertNode(0, "window", "b");
    mapModel.insertNode(0, "linux", "b");
    mapModel.insertNode(2, "keyboard", "b");
    mapModel.insertNode(2, "mouse", "b");
    mapModel.insertNode(2, "good", "b");
    string map = mapModel.showMap();
    cout << map << endl;

    ASSERT_EQ("Computer", mapModel.findNodeById(2)->getParent()->getDescription());
    ASSERT_EQ(1, mapModel.findNodeById(2)->getPositionFromParentNodeList());

    Component *target = mapModel.findNodeById(2);
    Component *node = new Node("TEE");

    Command *insertAParentCommand = new InsertAParentCommand(target, node);
    insertAParentCommand->execute();

    ASSERT_EQ("TEE", mapModel.findNodeById(2)->getParent()->getDescription());
    ASSERT_EQ(1, mapModel.findNodeById(7)->getPositionFromParentNodeList());


    map = mapModel.showMap();
    cout << map << endl;

    insertAParentCommand->unexecute();
    ASSERT_EQ("Computer", mapModel.findNodeById(2)->getParent()->getDescription());
    ASSERT_EQ(1, mapModel.findNodeById(2)->getPositionFromParentNodeList());

    map = mapModel.showMap();
    cout << map << endl;
}

TEST(Command, InsertAChildNodeCmd) {
    NodeIdCounter::initialize();
    MindMapModel mapModel;
    mapModel.createMindMap("Computer"); 
    mapModel.insertNode(0, "os", "b");
    mapModel.insertNode(0, "window", "b");
    mapModel.insertNode(0, "linux", "b");
    mapModel.insertNode(2, "keyboard", "b");
    mapModel.insertNode(2, "mouse", "b");
    mapModel.insertNode(2, "good", "b");
    string map = mapModel.showMap();
    cout << map << endl;

    Component *target = mapModel.findNodeById(2);
    Component *node = new Node("TEE");

    vector<Component*> list = target->getNodeList();
    for (int i = 0; i < list.size(); i++)
        ASSERT_FALSE(list[i] == node);


    Command *insertAChildCommand = new InsertAChildCommand(target, node);
    insertAChildCommand->execute();


    map = mapModel.showMap();
    cout << map << endl;
    
    list = target->getNodeList();
    for (int i = 0; i < list.size(); i++) 
        if (list[i] == node)
            ASSERT_EQ(list[i], node);
    

    insertAChildCommand->unexecute();

    map = mapModel.showMap();
        cout << map << endl;

    list = target->getNodeList();

    for (int i = 0; i < list.size(); i++)
        ASSERT_FALSE(list[i] == node);
}


TEST(InsertASiblingCommand, insertASiblingCmd) {
    NodeIdCounter::initialize();
    MindMapModel mapModel;
    mapModel.createMindMap("Computer"); 
    mapModel.insertNode(0, "os", "b");
    mapModel.insertNode(0, "window", "b");
    mapModel.insertNode(0, "linux", "b");
    mapModel.insertNode(2, "keyboard", "b");
    mapModel.insertNode(2, "mouse", "b");
    mapModel.insertNode(2, "good", "b");
    string map = mapModel.showMap();
    cout << map << endl;

    Component *target = mapModel.findNodeById(2);
    Component *node = new Node("TEE");

    Command* insertASiblingCommand = new InsertASiblingCommand(target, node);
    insertASiblingCommand->execute();
    map = mapModel.showMap();
    cout << map << endl;

    ASSERT_EQ(2, node->getPositionFromParentNodeList());

    insertASiblingCommand->unexecute();
    map = mapModel.showMap();
    cout << map << endl;
    ASSERT_EQ(nullptr, node->getParent());

}



#endif