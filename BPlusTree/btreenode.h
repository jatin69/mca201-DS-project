#ifndef BTREENODE_H
#define BTREENODE_H

class BTreeNode {
  private:
    int *keys;  // An array of keys
    int t;      // Minimum degree (defines the range for number of keys)
    BTreeNode **C; // An array of child pointers
    int n;     // Current number of keys
    bool leaf; // Is true when node is leaf. Otherwise false
  public:
    /** Default constructor */
    BTreeNode();

    /** Default destructor */
    ~BTreeNode();

    /** Copy constructor
     *  \param other Object to copy from
     */
    BTreeNode(const BTreeNode& other);

    /** Assignment operator
     *  \param other Object to assign from
     *  \return A reference to this
     */
    BTreeNode& operator=(const BTreeNode& other);

    BTreeNode(int _t, bool _leaf);   // Constructor

    // A utility function to insert a new key in the subtree rooted with
    // this node. The assumption is, the node must be non-full when this
    // function is called
    void insertNonFull(int k);

    // A utility function to split the child y of this node. i is index of y in
    // child array C[].  The Child y must be full when this function is called
    void splitChild(int i, BTreeNode *y);
    // A function to traverse all nodes in a subtree rooted with this node

    void traverse();

    // A function to search a key in subtree rooted with this node.
    BTreeNode *search(int k);   // returns nullptr if k is not present.

    // Make BTree friend of this so that we can access private members of this
    // class in BTree functions
    friend class BTree;

};

#endif // BTREENODE_H
