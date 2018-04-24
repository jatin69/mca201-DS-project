#include "btreenode.h"

#ifndef BTREE_H
#define BTREE_H

class BTree {
    BTreeNode *root; // Pointer to root node
    int t;  // Minimum degree
  public:
    // Constructor (Initializes tree as empty)
    BTree(int _t) {
        root = nullptr;
        t = _t;
    }

    /** Default constructor */
    BTree();
    /** Default destructor */
    ~BTree();

    /** Copy constructor
     *  \param other Object to copy from
     */
    BTree(const BTree& other);

    /** Assignment operator
     *  \param other Object to assign from
     *  \return A reference to this
     */
    BTree& operator=(const BTree& other);

    // The main function that inserts a new key in this B-Tree
    void insert(int k);

    // function to traverse the tree
    void traverse() {
        if (root != nullptr) root->traverse();
    }

    // function to search a key in this tree
    BTreeNode* search(int k) {
        return (root == nullptr)? nullptr : root->search(k);
    }


};

#endif // BTREE_H
