#include "btree.h"

BTree::BTree() {
    //ctor
}

BTree::~BTree() {
    //dtor
}

BTree::BTree(const BTree& other) {
    //copy ctor
}

BTree& BTree::operator=(const BTree& rhs) {
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}
