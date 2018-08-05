#ifndef UTMAPFACTORY_H
#define UTMAPFACTORY_H


#include "./include/mapFactory.h"
#include "./include/mindMapModel.h"
#include "./include/fileManager.h"

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

TEST(MapFactory, splitString) {
    string text = "this is my test";
    char token = ' ';
    FileManager file;
    string testCase[] {"this", "is", "my", "test"};
    vector<string> result = file.split(text, token);
    for (int i = 0; i < result.size(); i++)
        ASSERT_EQ(result[i], testCase[i]);
}

TEST(MapFactory, readFile) {
    FileManager file;
    string fileString[5] = { "0 computer 1 2 ", "1 window 3 4 ", "2 oxS ", "3 ausu ", "4 samsung "};
    int index = 0;
    vector<string> result = file.readFile("example.txt");
    for (vector<string>::iterator it = result.begin(); it != result.end(); ++it)
        ASSERT_EQ(fileString[index++], *it);
    
}

TEST(MapFactory, createMap) {
    MindMapModel model = createMindMapModel();
    cout << model.showMap() << endl;
    Component *root = model.getRoot();
    MapFactory factory(root);
    
    int result[] = {1, 2, 3, 4, 5};
    int index = 0;
    map<Component*, set<int>> maps = factory.createComponentMap();
    for (map<Component*, set<int>>::iterator it= maps.begin(); it!= maps.end(); ++it) {
        set<int> s = it->second;
        for (set<int>::iterator it2 = s.begin(); it2 != s.end(); ++it2) {
            ASSERT_EQ(*it2, result[index++]);
        }
    }
}


#endif