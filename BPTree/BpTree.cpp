#include "BpTree.h"
#include <math.h>

BpTree::BpTree(int degree) {
  /*
  Objective: constructor function of B+ Tree class aims at initializing the tree
  Approach: Self implementation of B+ Trees is being used
  Input Parameters:
      degree: degree of the b+ tree
  Return Values: None
  */

  n = degree;
  head = new LeafNode();
}

BpTree::~BpTree() {
  /*
  Objective: destructor function of B+ Tree class aims at deleting the tree
  Approach: Self implementation of B+ Trees is being used
  Input Parameters: None
  Return Values: None
  */

  // todo : Incorrect, i need to delete whole tree, not just root node
  if (head) {
    delete head;
  }
}

void BpTree::insert(int key, string value) {
  /*
  Objective: function aims at inserting elements to the B+ Tree
  Approach: Self implementation of B+ trees is being used
  Input Parameters:
      key: element to be inserted as entered by the user
      value: value of the key entered
  Return Values: None
  */

  // find the appropriate location for the element

  Node *t = this->head; // start from head


  while (!t->isLeaf) {  // until i reach a leaf node
    int flag = 0;

    // until a larger value in found in the key array, keep moving forward
    for (int i = 0; i < t->Keys.size(); ++i) {
     // found a key with larger value
      if (t->Keys[i] > key) {
        // Morph as a NonLeafNode and goto ith child
        t = ((NonLeafNode *)t)->Children[i];
        flag = 1;
        break;
      }
    }
    // if no key is larger, it is the largest
    if (!flag) {
            // smartly put value  ?? check
      t = ((NonLeafNode *)t)->Children[t->Keys.size()];
    }
  }


  // if key should be after last ( also handles if the key has currently 0 keys)
  if (t->Keys.size() == 0 || key > t->Keys.back()) {
    t->Keys.push_back(key);
    ((LeafNode *)t)->Value.push_back(value);

  } else {
    for (int i = 0; i < t->Keys.size(); ++i) { // insertion into the leaf node
      if (t->Keys[i] == key) {
        cout << "You cannot insert duplicate keys!" << endl;
        return;
      } else if (t->Keys[i] > key) {
        t->Keys.insert(t->Keys.begin() + i, key);
        ((LeafNode *)t)
            ->Value.insert(((LeafNode *)t)->Value.begin() + i, value);
        break;
      }
    }
  }
  if (t->Keys.size() > this->n) { // splitting the leaf node
    Node *tnew = new LeafNode();
    tnew->Parent = t->Parent;
    
    // make new leaf with second half - adding keys
    tnew->Keys.insert(tnew->Keys.begin(), t->Keys.begin() + ceil((n + 1) / 2), t->Keys.end());
    // make new leaf with second half - adding values
    ((LeafNode *)tnew)
        ->Value.insert(((LeafNode *)tnew)->Value.begin(),
                       ((LeafNode *)t)->Value.begin() + ceil((n + 1) / 2),
                       ((LeafNode *)t)->Value.end());
    
    // deleting those second half keys & values from original
    t->Keys.erase(t->Keys.begin() + ceil((n + 1) / 2), t->Keys.end());
    ((LeafNode *)t)
        ->Value.erase(((LeafNode *)t)->Value.begin() + ceil((n + 1) / 2),
                      ((LeafNode *)t)->Value.end());
    
     // new made leaf points to NULL
    ((LeafNode *)tnew)->Next = ((LeafNode *)t)->Next;
    // old leaf points to new leafnode
    ((LeafNode *)t)->Next = tnew;


    key = t->Keys[ceil((n + 1) / 2) - 1];

    // t's parent is a non leaf node
    while (t->Parent != NULL) {
      // now new t = t -> parent, because all the process now needs to be done on parent
      t = t->Parent;

      for (int i = 0; i < t->Keys.size(); ++i) {

        // if current key is largest of already present keys
        if (key > t->Keys.back()) {
          // because it is largest, push it at last
          t->Keys.push_back(key);
          // push the newly splitted leaf node to the children array of its parent
          ((NonLeafNode *)t)->Children.push_back(tnew);
          break;
        }
        // if current key not the largest 
        else if (t->Keys[i] > key) {
          // insert the t child to its children array
          t->Keys.insert(t->Keys.begin() + i, key);
          // insert the tnew child to its children array
          ((NonLeafNode *)t) ->Children.insert(((NonLeafNode *)t)->Children.begin() + i + 1, tnew);
          break;
        }
      }
      // if the parent also needs spilitting
      if (t->Keys.size() > this->n) {
        // make new node
        Node *nright = new NonLeafNode();
        nright->Parent = t->Parent;
        // split to 2
        nright->Keys.insert(nright->Keys.begin(),
                            t->Keys.begin() + floor((n + 2) / 2),
                            t->Keys.end());
        ((NonLeafNode *)nright)
            ->Children.insert(((NonLeafNode *)nright)->Children.begin(),
                              ((NonLeafNode *)t)->Children.begin() +
                                  floor((n + 2) / 2),
                              ((NonLeafNode *)t)->Children.end());
        for (int i = floor((n + 2) / 2);
             i < ((NonLeafNode *)t)->Children.size(); ++i) {
          ((NonLeafNode *)t)->Children[i]->Parent = nright;
        }
        key = t->Keys[floor((n + 2) / 2) - 1];
        t->Keys.erase(t->Keys.begin() + floor((n + 2) / 2) - 1, t->Keys.end());
        ((NonLeafNode *)t)
            ->Children.erase(((NonLeafNode *)t)->Children.begin() +
                                 floor((n + 2) / 2),
                             ((NonLeafNode *)t)->Children.end());
        tnew = nright;
      } else {
        tnew->Parent = t;
        return;
      }
    }
    // when we have reached root
    if (t->Parent == NULL) {
      // make a non leaf node
      t->Parent = new NonLeafNode();
      
      // insert t and tnew to children array of this new nonleafnode
      ((NonLeafNode *)t->Parent) -> Children.insert(((NonLeafNode *)t->Parent)->Children.begin(), t);
      ((NonLeafNode *)t->Parent) -> Children.insert(((NonLeafNode *)t->Parent)->Children.begin() + 1, tnew);
      
      if (t->isLeaf) {
        // move the last key of the leaf node to the begin of parent node
        (t->Parent)->Keys.insert((t->Parent)->Keys.begin(), t->Keys.back());
      } else {
        // move ( the last key of its last child ) to the begin of parent of t
        (t->Parent)->Keys.insert(
            (t->Parent)->Keys.begin(),
            ((NonLeafNode *)t)->Children.back()->Keys.back());
      }
      tnew->Parent = t->Parent;
      head = t->Parent;
    }

  } else {
    return;
  }
}

string BpTree::find(int key) {
  /*
  Objective: function aims at searching an element in the B+ Tree
  Approach: Self implementation of B+ trees is being used
  Input Parameters:
      key: element to be searched as entered by the user
  Return Values: None
  */

  Node *t = this->head;
  while (!t->isLeaf) { // find the proper location
    int flag = 0;
    for (int i = 0; i < t->Keys.size(); ++i) {
      if (t->Keys[i] >= key) {
        t = ((NonLeafNode *)t)->Children[i];
        flag = 1;
        break;
      }
    }
    if (!flag) {
      t = ((NonLeafNode *)t)->Children[t->Keys.size()];
    }
  }
  for (int i = 0; i < t->Keys.size(); ++i) {
    if (t->Keys[i] == key) {
      return ((LeafNode *)t)->Value[i];
    }
  }
  return "This key does not exist in this B+ tree!";
}

void BpTree::printKeys() {
  /*
  Objective: function aims at printing all the keys in the B+ Tree
  Approach: Self implementation of B+ trees is being used
  Input Parameters: None
  Return Values: None
  */

  if (head->Keys.size() == 0) {
    cout << "[]" << endl;
    return;
  }
  vector<Node *> q;
  q.push_back(head);
  while (q.size()) {
    unsigned long size = q.size();
    for (int i = 0; i < size; ++i) {
      if (!q[i]->isLeaf) {
        for (int j = 0; j < ((NonLeafNode *)q[i])->Children.size(); ++j) {
          q.push_back(((NonLeafNode *)q[i])->Children[j]);
        }
      }
      cout << "[";
      int nk = 0;
      for (nk = 0; nk < q[i]->Keys.size() - 1; ++nk) {
        cout << q[i]->Keys[nk] << ",";
      }
      cout << q[i]->Keys[nk] << "] ";
    }
    q.erase(q.begin(), q.begin() + size);
    cout << endl;
  }
}

void BpTree::printValues() {
  /*
  Objective: function aims at printing all the string values in the B+ Tree
  Approach: Self implementation of B+ trees is being used
  Input Parameters: None
  Return Values: None
  */

  Node *t = this->head;
  while (!t->isLeaf) {
    t = ((NonLeafNode *)t)->Children[0];
  }
  while (t != NULL) {
    for (int i = 0; i < t->Keys.size(); ++i) {
      cout << ((LeafNode *)t)->Value[i] << endl;
    }
    t = ((LeafNode *)t)->Next;
  }
}
