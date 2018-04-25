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
  Side effects: Class BpTree defines B+ Tree class
  Approach: Class definition
  */
private:
  Node *head;
  int n;

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
