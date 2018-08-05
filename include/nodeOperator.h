#ifndef NODEOPERATOR_H
#define NODEOPERATOR_H


class MindMapModel;
class Component;
#include <vector>
using std::vector;

class NodeOperator {
public:
    NodeOperator(MindMapModel *model);
    void deleteNodeById(int id);
    void changeParent(int targetId, int parentId);
    void changeParent(Component *target, Component *modifiedParent);
    void restoreDeletedNodeById(int id);
private:
    int getRemovedIndex();
    void removeNodeById(int id);
    void changeListNodeParent(Component *parentOfTarget);
    void rememberTarget(int targetId);
    void changeParentWithIndex(Component *target, Component *modifiedParent, int index);
    void changeListNodeParentWithIndex(Component *parentOfTarget);
    Component *_deletedTarget;
    Component *_parentOfDeletedTarget;
    Component *_root;
    int _removedIndex;
    vector<Component*> _list;
    MindMapModel *_model;
};

#endif