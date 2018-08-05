#include "../include/factory.h"

Factory::Factory() {

}

Component* Factory::createNode(string description) {
    Component *node = new Node();
    node->setDescription(description);
    return node;
}

Component* Factory::createRoot(string description) {
    Component *root = new Root();
    root->setDescription(description);
    return root;
}
