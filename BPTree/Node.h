#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Node {
  /*
  Objective: Create a class for a Node for B+ tree
  Approach : Class defines data items as vector of integer and link is named
  parent of node type Input Parameters: none Return Value: none Description: A
  general node
  */

public:
  vector<int> Keys;
  Node *Parent;
  bool isLeaf;
};

class NonLeafNode : public Node {
  /*
  Objective: Create a class for a Non Leaf Node for B+ tree
  Approach: Class defines vector of links named  pf Children type
  Input Parameters: none
  Return Value: none
  Description: node class defines the node structure
  */

public:
  vector<Node *> Children;
  NonLeafNode() {
    isLeaf = false;
    Parent = NULL;
  }
};

class LeafNode : public Node {
  /*
  Objective: Create a class for a Leaf Node for B+ tree
  Approach: Class defines data item is names element with data type string and
  link is named next of node type Input Parameters: none Return Value: none
  Description: A leaf node (inherits general node)
  */
public:
  Node *Next;
  vector<string> Value;
  LeafNode() {
    isLeaf = true;
    Next = NULL;
    Parent = NULL;
  }
};

#endif // NODE_H
