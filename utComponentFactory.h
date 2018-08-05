#ifndef UTCOMPONENTFACTORY_H
#define UTCOMPONENTFACTORY_H

#include <vector>
#include <string>
#include "./include/component.h"
#include "./include/fileManager.h"
#include "./include/componentFactory.h"

#include <iostream>

using std::endl;
using std::cout;

using std::string;
using std::vector;

TEST(ComponentFactory, createComponent) {
    NodeIdCounter::initialize();
    ComponentFactory cFactory;
    FileManager fileManager;
    vector<vector<string>> mindMapToken;

    vector<string> mindMap = fileManager.readFile("mindMap.txt");
    cout << mindMap.size();
    for (int i = 0; i < mindMap.size(); i++) {
        mindMapToken.push_back(fileManager.split(mindMap[i], ' '));
    }

    Component *root = cFactory.createComponent(mindMapToken);
    cout << root->getMap() << endl;

}


#endif