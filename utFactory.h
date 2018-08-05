#ifndef UTFACTORY_H
#define UTFACTORY_H

#include "./include/component.h"

TEST(Factory, create_node) {
    Factory factory;
    Component *node = factory.createNode(); 
    ASSERT_EQ("Node", node->getType());
}
/*
TEST(Factory, create_root) {

}
*/


#endif