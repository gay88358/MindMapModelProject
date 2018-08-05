#include "../include/root.h"

Root::Root(): Composite() {

}

Root::Root(string description): Composite(description) {

}

string Root::getType() const {
    return "Root";
}

int Root::getPositionFromParentNodeList() {
    throw invalid_argument("Root Has No Parent!");
}
