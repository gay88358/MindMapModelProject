#ifndef UTCOMPONENT_H
#define UTCOMPONENT_H
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "./include/component.h"
#include "./include/composite.h"
#include "./include/root.h"
#include "./include/node.h"
#include "./include/nodeIdCounter.h"

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::invalid_argument;

TEST(Component, initializeComponentWithId) {
    NodeIdCounter::initialize();

    Component *c = new Component();
    int id = c->getId();
    ASSERT_EQ(id, 0);
}

TEST(Component, description) {
    Component *root = new Root();
    root->setDescription("Computer");
    string description = root->getDescription();
    ASSERT_EQ(description, "Computer");
}

TEST(Composite, initializeCompositeWithId) {
    NodeIdCounter::initialize();
    Composite * cmp = new Composite();
    int id = cmp->getId();
    ASSERT_EQ(id, 0);
}

TEST(Composite, root_addParent) {
    Composite *cp = new Node();
    Composite *root = new Root();
    try {
        cp->addParent(root);
    } catch(const std::invalid_argument& e) {
        string error = e.what();
        ASSERT_EQ(error, "Please overwriten abstract method!!");
    }
}

TEST(Composite, root_addSibling) {
    Composite *cp = new Node();
    Composite *root = new Root();
    try {
        root->addSibling(root);
    } catch(const std::invalid_argument& e) {
        string error = e.what();
        ASSERT_EQ(error, "Please overwriten abstract method!!");
    }
}

TEST(Component, root_addChild) {
    Component *root = new Root();
    root->setDescription("Computer");
    
    Component *window = new Node();
    window->setDescription("Window");
    root->addChild(window);

    Component *mac = new Node();
    mac->setDescription("Mac Os");
    root->addChild(mac);

    Component *linux = new Node();
    linux->setDescription("Linux");
    root->addChild(linux);

    vector<Component*> list = root->getNodeList();

    string result[] = { "Window", "Mac Os", "Linux" };
    for (int i = 0; i < list.size(); i++) 
        ASSERT_EQ(result[i], list[i]->getDescription());
    
}

TEST(Component, node_addSibling) {
    Component *root = new Root();
    root->setDescription("Computer");

    Component *windows = new Node();
    windows->setDescription("Windows");

    Component *os = new Node();
    os->setDescription("Os");

    Component *linux = new Node();
    linux->setDescription("Linux");

    root->addChild(windows);
    windows->addSibling(os);
    os->addSibling(linux);
    vector<Component*> list = root->getNodeList();

    string result[] = { "Windows", "Os", "Linux" };
    for (int i = 0; i < list.size(); i++) 
        ASSERT_EQ(result[i], list[i]->getDescription());
}

TEST(Component, createIdAutomaticlly) {
    NodeIdCounter::initialize();
    Component *root = new Root();
    ASSERT_EQ(0, root->getId());
    Component *windows = new Node();
    ASSERT_EQ(1, windows->getId());
    Component *os = new Node();
    ASSERT_EQ(2, os->getId());
    Component *linux = new Node();
    ASSERT_EQ(3, linux->getId());
}




TEST(Component, complicated_addParent_and_addChild) {
    NodeIdCounter::initialize();
    Component *root = new Root();
    root->setDescription("Computer");

    Component *os = new Node();
    os->setDescription("Os");

    
    Component *network = new Node();
    network->setDescription("NetWork");
    root->addChild(network);
    root->addChild(os);


    Component *wireless = new Node();
    wireless->setDescription("WIRELESS");
    network->addChild(wireless);

    Component *cable = new Node();
    cable->setDescription("CABLE");
    network->addChild(cable);

    Component *windows = new Node();
    windows->setDescription("Windows");
    os->addChild(windows);

    Component *ios = new Node();
    ios->setDescription("IOS");
    os->addChild(ios);

    Component *linux = new Node();
    linux->setDescription("LINUX");
    os->addChild(linux);

    Component *directX = new Node();
    directX->setDescription("DirectX");
    windows->addChild(directX);

    Component *microsoft = new Node();
    microsoft->setDescription("Microsoft");
    windows->addChild(microsoft);


    string result = "+-Computer(Root, ID: 0)\n   +-NetWork(Node, ID: 2)\n   |  +-WIRELESS(Node, ID: 3)\n   |  +-CABLE(Node, ID: 4)\n   +-Os(Node, ID: 1)\n      +-Windows(Node, ID: 5)\n      |  +-DirectX(Node, ID: 8)\n      |  +-Microsoft(Node, ID: 9)\n      +-IOS(Node, ID: 6)\n      +-LINUX(Node, ID: 7)\n";

    ASSERT_EQ(root->getMap(), result);


}

TEST(Component, printMap) {
    NodeIdCounter::initialize();
    Component *root = new Root();
    root->setDescription("Computer");

    Component *windows = new Node();
    windows->setDescription("Windows");

    Component *os = new Node();
    os->setDescription("Os");

    Component *linux = new Node();
    linux->setDescription("Linux");

    root->addChild(windows);
    windows->addSibling(os);

    windows->addChild(linux);
    string result = "+-Computer(Root, ID: 0)\n   +-Windows(Node, ID: 1)\n   |  +-Linux(Node, ID: 3)\n   +-Os(Node, ID: 2)\n";
    ASSERT_EQ(result, root->getMap());
}


TEST(Component, createMindMap) {
    NodeIdCounter::initialize();
    Component *computer = new Root();
    computer->setDescription("Computer");

    Component *window = new Node();
    window->setDescription("Window");
    Component *os = new Node();
    os->setDescription("Os");

    computer->addChild(window);
    window->addParent(os);

    string mindMap = computer->getMap();
    string result = "+-Computer(Root, ID: 0)\n   +-Os(Node, ID: 2)\n      +-Window(Node, ID: 1)\n";
    ASSERT_EQ(result, computer->getMap());
}
/*
TEST(Component, findNodeErrorHandling) {
    NodeIdCounter::initialize();
    Component *root = new Root(); // id: 0
    root->setDescription("Computer");

    try {
        root->findNodeById(2);
    } catch(std::string error) {
        ASSERT_EQ(error, "The node is not exist!");
    }
}*/

TEST(Component, findNodeById) {
    NodeIdCounter::initialize();
    Component *root = new Root(); // id: 0
    root->setDescription("Computer");

    Component *window = new Node(); // id: 1
    window->setDescription("Windows");

    Component *os = new Node(); // id: 2
    os->setDescription("OS");

    root->addChild(window);
    window->addParent(os);

    Component *target = root->findNodeById(root, 0);
    ASSERT_EQ("Computer", target->getDescription());
     
    target = root->findNodeById(root, 1);
    ASSERT_EQ("Windows", target->getDescription());

    target = root->findNodeById(root, 2);
    ASSERT_EQ("OS", target->getDescription());
}

TEST(Component, formetMindMap) {
    NodeIdCounter::initialize();
    Component *root = new Root(); // id: 0
    root->setDescription("Computer");

    Component *window = new Node(); // id: 1
    window->setDescription("Windows");

    Component *os = new Node(); // id: 2
    os->setDescription("OS");

    root->addChild(window);
    window->addParent(os);

    root->formatMindMap(root);
}

TEST(Component, add_complex_parent) {
    NodeIdCounter::initialize();
    Component *root = new Root();
    root->setDescription("Computer");

    Component *windows = new Node();
    windows->setDescription("Windows");

    Component *os = new Node();
    os->setDescription("Os");

    Component *linux = new Node();
    linux->setDescription("Linux");

    root->addChild(windows);
    windows->addSibling(os);

    windows->addChild(linux); 

    cout << root->getMap() << endl;



    windows->addParent(os);

    cout << root->getMap() << endl;
    Component *target = root->findNodeById(root, 1);
    ASSERT_EQ(target->getParent(), os);

}

TEST(Component, deleteNodeById) {
    NodeIdCounter::initialize();
    Component *root = new Root(); // id: 0
    root->setDescription("Computer");

    Component *window = new Node(); // id: 1
    window->setDescription("Windows");

    Component *os = new Node(); // id: 2
    os->setDescription("OS");
    root->addChild(window);
    window->addParent(os);

    cout << root->getMap() << endl;

    ASSERT_EQ(root->deleteNodeById(2), true);

    cout << root->getMap() << endl;

}

TEST(Component, getParent) {
    NodeIdCounter::initialize();
    Component *root = new Root(); // id: 0
    root->setDescription("Computer");

    Component *window = new Node(); // id: 1
    window->setDescription("Windows");

    Component *os = new Node(); // id: 2
    os->setDescription("OS");

    root->addChild(window);
        cout << root->getMap() << endl;

    window->addParent(os);

    cout << root->getMap() << endl;


    ASSERT_EQ(window->getParent()->getDescription(), "OS");
    ASSERT_EQ(os->getParent()->getDescription(), "Computer");

}


TEST(Component, removeNode) {
    NodeIdCounter::initialize();
    Component *root = new Root(); // id: 0
    root->setDescription("Computer");

    Component *window = new Node(); // id: 1
    window->setDescription("Windows");

    Component *os = new Node(); // id: 2
    os->setDescription("OS");

    root->addChild(window);
    cout << root->getMap() << endl;
    cout << window->getParent()->getDescription() << endl;
    ASSERT_EQ("Computer", window->getParent()->getDescription());
    Component *mouse = new Node();
    mouse->setDescription("Mouse");

    window->addParent(mouse);

    ASSERT_EQ("Mouse", window->getParent()->getDescription());
}

TEST(Component, TestConstructor) {
    NodeIdCounter::initialize();
    Component *root = new Root("Computer"); // id: 0
    Component *window = new Node("Windows"); // id: 1
    ASSERT_EQ(root->getDescription(), "Computer");
    ASSERT_EQ(window->getDescription(), "Windows");
}

TEST(Component, TestFindNodeById) {
    NodeIdCounter::initialize();
    Component *root = new Root("Computer"); // id: 0
    Component *window = new Node("Windows"); // id: 1
    root->addChild(window);
    Component *target = root->findNodeById(0);
    ASSERT_EQ(target, root);
    target = root->findNodeById(1);
    ASSERT_EQ(target, window);
}

TEST(Component, TestFindNodeByIdComplex) {
    NodeIdCounter::initialize();
    Component *root = new Root("Computer"); // id: 0
    Component *window = new Node("Windows"); // id: 1NodeIdCounter::initialize();
    Component *macos = new Node("MacOs"); // id: 2
    Component *linux = new Node("Linux"); // id: 3
    root->addChild(window);
    window->addChild(macos);
    macos->addSibling(linux);
    Component *target = root->findNodeById(2);
    ASSERT_EQ(target, macos);
    target = root->findNodeById(1);
    ASSERT_EQ(target, window);
}

TEST(Component, addChildWithIndex) {
    NodeIdCounter::initialize();
    Component *root = new Root("Computer"); // id: 0
    Component *window = new Node("Windows"); // id: 1NodeIdCounter::initialize();
    Component *macos = new Node("MacOs"); // id: 2
    Component *linux = new Node("Linux"); // id: 3
    int index = 2;
    root->addChild(window);
    root->addChild(macos);
    root->addChildWithIndex(linux, index);
    vector<Component*> list = root->getNodeList();
    ASSERT_EQ(list[index], linux);
}

TEST(Component, addParentWithMultipleSibling) {
    NodeIdCounter::initialize();
    Component *root = new Root("Computer");
    Component *window = new Node("Windows"); // id: 1NodeIdCounter::initialize();
    Component *macos = new Node("MacOs"); // id: 2
    Component *linux = new Node("Linux"); // id: 3
    root->addChild(window);
    root->addChild(macos);
    root->addChild(linux);
    int position = 0;
    cout << root->getMap() << endl;
    //ASSERT_EQ(position, window->getPositionFromParentNodeList());
    ASSERT_EQ(root->getDescription(), root->findNodeById(1)->getParent()->getDescription());
    Component *newParent = new Node("XX");
    window->addParent(newParent);
    ASSERT_EQ(newParent->getDescription(), root->findNodeById(1)->getParent()->getDescription());
    cout << root->getMap() << endl;
}

TEST(Component, getPositionFromParentNodeList) {
    NodeIdCounter::initialize();
    Component *root = new Root("Computer");
    Component *window = new Node("Windows"); // id: 1NodeIdCounter::initialize();
    Component *macos = new Node("MacOs"); // id: 2
    Component *linux = new Node("Linux"); // id: 3
    root->addChild(window);
    root->addChild(macos);
    root->addChild(linux);
    cout << root->getMap() << endl;
    int position = 1;
    ASSERT_EQ(position, macos->getPositionFromParentNodeList());
    position = 0;
    ASSERT_EQ(position, window->getPositionFromParentNodeList());
    position = 2;
    ASSERT_EQ(position, linux->getPositionFromParentNodeList());
}

#endif