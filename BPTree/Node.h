#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Node
{
    /*
	Objective: Create a class for a Node for B+ tree
	Approach: Class defines data items as vector of integer and link is named parent pf node type
	Input Parameters: none
	Return Value: none
	Description: node class defines the node structure
	*/

public:
    vector<int> Keys;
    Node* Parent;
    bool isLeaf;
};

class LeafNode: public Node
{
    /*
	Objective: Create a class for a Leaf Node for B+ tree
	Approach: Class defines data item is names element with datatype string and link is named next pf node type
	Input Parameters: none
	Return Value: none
	Description: node class defines the node structure
	*/

public:
    Node* Next;
    vector<string> Value;
    LeafNode(){isLeaf=true; Next=NULL; Parent=NULL; }
};

class In_Node:public Node
{
    /*
	Objective: Create a class for a Leaf Node for B+ tree
	Approach: Class defines vector of links named  pf Children type
	Input Parameters: none
	Return Value: none
	Description: node class defines the node structure
	*/

public:
    vector<Node*> Children;
    In_Node(){isLeaf=false; Parent=NULL; }
};


#endif // NODE_H
