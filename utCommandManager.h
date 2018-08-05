#ifndef UTCOMMANDMANAGER_H
#define UTCOMMANDMANAGER_H

#include "./include/commandManager.h"
#include "./include/deleteCommand.h"
#include "./include/editCommand.h"
#include "./include/changeParentCommand.h"
#include "./include/mindMapModel.h"

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

TEST(CommandManager, TestExecuteEditCommand) {
    MindMapModel model = createMindMapModel();
    cout << model.showMap() << endl;
    ASSERT_EQ(model.getRoot()->getDescription(), "Computer");

    CommandManager manager; 
    Command *editCommand = new EditCommand(model, 0, "Computer Science");
    manager.execute(editCommand);
    cout << model.showMap() << endl;
    ASSERT_EQ(model.getRoot()->getDescription(), "Computer Science");
    manager.undo();
    ASSERT_EQ(model.getRoot()->getDescription(), "Computer");
    manager.redo();
    ASSERT_EQ(model.getRoot()->getDescription(), "Computer Science");
}

TEST(CommandManager, TestExecuteChangeParentCommand) {
    MindMapModel model = createMindMapModel();
    cout << model.showMap() << endl;
    Component *root = model.getRoot();
    Component *target = root->findNodeById(2);
    ASSERT_EQ(target->getParent()->getDescription(), "Computer");
    int targetId = 2;
    int modifiedParentId = 4;
    Command *changeParentCommand = new ChangeParentCommand(model, targetId, modifiedParentId);
    CommandManager manager;
    manager.execute(changeParentCommand);
    ASSERT_EQ(target->getParent()->getDescription(), "Microsoft");
    manager.undo();
    ASSERT_EQ(target->getParent()->getDescription(), "Computer");
    manager.redo();
    ASSERT_EQ(target->getParent()->getDescription(), "Microsoft");
    manager.undo();
    ASSERT_EQ(target->getParent()->getDescription(), "Computer");
}

TEST(CommandManager, TestExecuteDeleteCommand) {
    MindMapModel model = createMindMapModel();
    cout << model.showMap() << endl;
    Component *root = model.getRoot();
    Component *target = root->findNodeById(2);
    ASSERT_TRUE(target != nullptr);

    int targetId = 2;
    Command *deleteCommand = new DeleteCommand(model, targetId);
    CommandManager manager;
    manager.execute(deleteCommand);

    cout << model.showMap() << endl;

    target = root->findNodeById(targetId);
    ASSERT_EQ(target, nullptr);
    manager.undo();
    cout << model.showMap() << endl;
    target = root->findNodeById(targetId);

    ASSERT_TRUE(target != nullptr);
    manager.redo();
    cout << model.showMap() << endl;
    target = root->findNodeById(targetId);

    ASSERT_EQ(target, nullptr);
    manager.undo();
        target = root->findNodeById(targetId);

    ASSERT_TRUE(target != nullptr);
    cout << model.showMap() << endl;

}

TEST(CommandManager, TestMultipleCommand) {
    MindMapModel model = createMindMapModel();
    cout << model.showMap() << endl;

    CommandManager manager;
    int targetId = 2;
    Command *deleteCommand = new DeleteCommand(model, targetId);
    manager.execute(deleteCommand);
    cout << model.showMap() << endl;
    
    targetId = 3;
    deleteCommand = new DeleteCommand(model, targetId);
    manager.execute(deleteCommand);
    cout << model.showMap() << endl;

    manager.undo();
    cout << model.showMap() << endl;
    manager.undo();
    cout << model.showMap() << endl;
    
}


TEST(CommandManager, testZeroUndoStack) {
    CommandManager manager;
    try {
        manager.undo();
    } catch(std::string error) {
        ASSERT_EQ("Can't not undo!", error);
    }
}

TEST(CommandManager, testZeroRedoStack) {
    CommandManager manager;
    try {
        manager.redo();
    } catch(std::string error) {
        ASSERT_EQ("Can't not redo!", error);
    }
}


#endif