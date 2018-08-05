#include "../include/nodeModifier.h"
#include "../include/component.h"


NodeModifier::NodeModifier() {
    
}

NodeModifier::NodeModifier(vector<Component*> &list): _list(list) {

}

void NodeModifier::removeNode(vector<Component*> &list, Component* node) {
    for (int i = 0; i < list.size(); i++) {
        if (list[i] == node) {
            list[i]->releaseParent();
            list.erase(list.begin() + i);
        }
    }
}
