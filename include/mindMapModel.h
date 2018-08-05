#ifndef MINDMAPMODEL_H
#define MINDMAPMODEL_H

#include "./component.h"
#include "./factory.h"

#include "./fileManager.h"
#include "./commandManager.h"
#include "./nodeOperator.h"
#include "./componentFactory.h"

class MindMapModel {
public:
    MindMapModel();
    void createMindMap(string description);
    Component* createNode(string name);
    Component* findNodeById(int id);
    void deleteById(int id);
    void restoreDeletedNodeById(int targetId);
    void insertNode(int id, string name, string insertType);
    void editNodeDescription(int id, string name);
    string getDescriptionById(int id) const;
    void changeParent(int targetId, int parentId);
    int getParentId(int id);
    void saveMindMap();
    string showMap();
    Component* getRoot();
    
    void editNodeDescriptionCommand(int targetId, string description);
    void changeNodeParentCommand(int targetId, int parentId);
    void deleteNodeCommand(int targetId);
    void undo();
    void redo();
    // load MindMap
    void loadMindMap(string path);
private:
    // inner factory, used to lazy initialize nodeOperator
    NodeOperator* createNodeOperator();
    Component *_root;
    FileManager _fileManager;
    Factory _factory;
    ComponentFactory _componentFactory;
    NodeOperator *_nodeOperator;
    CommandManager _commandManager;
};

#endif