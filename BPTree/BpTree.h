#ifndef BPTREE_H
#define BPTREE_H

#include "Node.h"
#include <iostream>

using namespace std;

class BpTree {
  /*
  objective: Create a B+ Tree class
  Input parameters: none
  Output value: none
  Side effects: Class BPTree defines B+ Tree class
  Approach: Class definition
  */
private:
  Node *head; // head points to root of the tree
  int n;      // degree of tree

public:
  BpTree(int);
  void insert(int, string);
  void remove(int);
  string find(int);
  void printKeys();
  void printValues();
  ~BpTree();
};

#endif // BPTREE_H
