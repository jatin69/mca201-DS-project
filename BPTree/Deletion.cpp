#include "BpTree.h"
#include "Node.h"
#include <math.h>

void BpTree::remove(int key) {
  Node *t = this->head;

  // find the node for Key
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

  // erase the key & value
  int flag = 0;
  for (int i = 0; i < t->Keys.size(); ++i) {
    if (t->Keys[i] == key) {
      t->Keys.erase(t->Keys.begin() + i);
      ((LeafNode *)t)->Value.erase(((LeafNode *)t)->Value.begin() + i);
      flag = 1;
      break;
    }
  }
  // not found
  if (!flag) {
    cout << "The key you want to delete does not exist!" << endl;
    return;
  }

  // adjustment is only needed when
  // case : nodes are less than required 
  if (((LeafNode *)t)->Value.size() < ceil((n + 1) / 2) && t->Parent != NULL) {

    Node *Rsibling;
    Node *Lsibling;
    Rsibling = Lsibling = NULL;

    // internal node
    int Child_num = -1;

    // in the key array, find the position of key
    for (int i = 0; i < ((NonLeafNode *)t->Parent)->Children.size(); ++i) {
      if (((NonLeafNode *)t->Parent)->Children[i] == t) {
        Child_num = i;
        break;
      }
    }

    // left of found is LEFT SIBLING
    if (Child_num - 1 >= 0) {
      Lsibling = ((NonLeafNode *)t->Parent)->Children[Child_num - 1];
    }
    // right of found is RIGHT SIBLING
    if (Child_num + 1 < ((NonLeafNode *)t->Parent)->Children.size()) {
      Rsibling = ((NonLeafNode *)t->Parent)->Children[Child_num + 1];
    }

    // siblings are now known.

    // if right sibling has enough nodes, take it from here
    if (Rsibling != NULL && ((LeafNode *)Rsibling)->Value.size() - 1 >= ceil((n + 1) / 2)) {

      // pick the first key of right sibling & insert it to current node
      t->Keys.push_back(Rsibling->Keys.front());
      ((LeafNode *)t)->Value.push_back(((LeafNode *)Rsibling)->Value.front());
      
      // erase it from right sibling
      Rsibling->Keys.erase(Rsibling->Keys.begin());
      ((LeafNode *)Rsibling)->Value.erase(((LeafNode *)Rsibling)->Value.begin());

      // these changes also need to be reflected to the parent of current node
      t->Parent->Keys[Child_num] = t->Keys.back();
      return;
    }

    // if left sibling has enough nodes, take it from here 
    else if (Lsibling != NULL && ((LeafNode *)Lsibling)->Value.size() - 1 >= ceil((n + 1) / 2)) {
      
      // pick the last key of left sibling & insert it to current node
      t->Keys.insert(t->Keys.begin(), Lsibling->Keys.back());
      ((LeafNode *)t)->Value.insert(((LeafNode *)t)->Value.begin(),
                         ((LeafNode *)Lsibling)->Value.back());

      // erase it from left sibling
      Lsibling->Keys.erase(Lsibling->Keys.end() - 1);
      ((LeafNode *)Lsibling) ->Value.erase(((LeafNode *)Lsibling)->Value.end() - 1);

      // these changes also need to be reflected to the parent of current node
      t->Parent->Keys[Child_num - 1] = Lsibling->Keys.back();
      return;
    }

    // siblings cant help, gotta merge with them to power up
    else {
      // right sibling has less than required
      if (Rsibling != NULL && ((LeafNode *)Rsibling)->Value.size() - 1 < ceil((n + 1) / 2)) {

        // merge all the keys of right sibling to current node
        t->Keys.insert(t->Keys.end(), Rsibling->Keys.begin(), Rsibling->Keys.end());
        // and values and well
        ((LeafNode *)t) ->Value.insert(((LeafNode *)t)->Value.end(),
                           ((LeafNode *)Rsibling)->Value.begin(),
                           ((LeafNode *)Rsibling)->Value.end());
        
        // now right sibling needs to be deleted
        
        // makes current->next = right sibling ->next
        ((LeafNode *)t)->Next = ((LeafNode *)Rsibling)->Next;

        // now we can safely delete right sibling

        // reflect changes to its parent first
        t->Parent->Keys.erase(t->Parent->Keys.begin() + Child_num);
        // delete entire right sibling node
        ((NonLeafNode *)t->Parent)->Children.erase(((NonLeafNode *)t->Parent)->Children.begin() + Child_num + 1);

        // current pointer is at current (it is left of right sibling) & right sibling has been deleted.
      } 
      // right sibling has less than required
      else if (Lsibling != NULL && ((LeafNode *)Lsibling)->Value.size() - 1 < ceil((n + 1) / 2)) {

        // merge all the keys of left sibling to current node
        Lsibling->Keys.insert(Lsibling->Keys.end(), t->Keys.begin(), t->Keys.end());
        // and values and well
        ((LeafNode *)Lsibling) ->Value.insert(((LeafNode *)Lsibling)->Value.begin(),
                           ((LeafNode *)t)->Value.begin(),
                           ((LeafNode *)t)->Value.end());

        // now left sibling needs to be deleted
        
        // makes left sibling ->next = current->next
        
        ((LeafNode *)Lsibling)->Next = ((LeafNode *)t)->Next;

        // now we can safely delete left sibling
        // reflect changes to its parent first
        t->Parent->Keys.erase(t->Parent->Keys.begin() + Child_num - 1);

        // delete entire left sibling node
        ((NonLeafNode *)t->Parent) ->Children.erase(((NonLeafNode *)t->Parent)->Children.begin() + Child_num);

        // current pointer shifted to original left and current deleted
        t = Lsibling;
      }

      // until current node processing does not catch up to head, recursively process all in-between nodes
      while (t->Parent != this->head) {

        Rsibling = Lsibling = NULL;
        // move t to t->parent to begin processing
        t = t->Parent;

        // if it has enough child, nothing to process
        if (((NonLeafNode *)t)->Children.size() >= floor((n + 2) / 2)) {
          return;
        }

        // find current node & hold its position to child_num
        int Child_num = -1;
        for (int i = 0; i < ((NonLeafNode *)t->Parent)->Children.size(); ++i) {
          if (((NonLeafNode *)t->Parent)->Children[i] == t) {
            Child_num = i;
            break;
          }
        }

        // left of current
        if (Child_num - 1 >= 0) {
          Lsibling = ((NonLeafNode *)t->Parent)->Children[Child_num - 1];
        }

        // right of current
        if (Child_num + 1 < ((NonLeafNode *)t->Parent)->Children.size()) {
          Rsibling = ((NonLeafNode *)t->Parent)->Children[Child_num + 1];
        }

        // if right sibling has enough nodes, take it from here
        if (Rsibling != NULL && ((NonLeafNode *)Rsibling)->Children.size() - 1 >= floor((n + 2) / 2)) {
          
          // take first child of right sibling & process similarly as above
          ((NonLeafNode *)t) ->Children.push_back(((NonLeafNode *)Rsibling)->Children.front());
          t->Keys.push_back(t->Parent->Keys[Child_num]);
          t->Parent->Keys[Child_num] = Rsibling->Keys.front();
          ((NonLeafNode *)Rsibling) ->Children.erase(((NonLeafNode *)Rsibling)->Children.begin());
          Rsibling->Keys.erase(Rsibling->Keys.begin());
          ((NonLeafNode *)t)->Children.back()->Parent = t;
          return;
        } 

        // if left sibling has enough nodes
        else if (Lsibling != NULL && ((NonLeafNode *)Lsibling)->Children.size() - 1 >= floor((n + 2) / 2)) {

          // take last child of left sibling & process similarly as above
          ((NonLeafNode *)t) ->Children.insert(((NonLeafNode *)t)->Children.begin(), ((NonLeafNode *)Lsibling)->Children.back());
          t->Keys.insert(t->Keys.begin(), t->Parent->Keys[Child_num - 1]);
          t->Parent->Keys[Child_num] = Lsibling->Keys.back();
          ((NonLeafNode *)Lsibling) ->Children.erase(((NonLeafNode *)Lsibling)->Children.end() - 1);
          Lsibling->Keys.erase(Lsibling->Keys.end() - 1);
          ((NonLeafNode *)t)->Children.front()->Parent = t;
          return;
        } 

        // if not enough on right side, gotta merge
        else if (Rsibling != NULL && ((NonLeafNode *)Rsibling)->Children.size() - 1 < floor((n + 2) / 2)) {
          ((NonLeafNode *)Rsibling) ->Children.insert(((NonLeafNode *)Rsibling)->Children.begin(),
                                ((NonLeafNode *)t)->Children.begin(),
                                ((NonLeafNode *)t)->Children.end());
          Rsibling->Keys.insert(Rsibling->Keys.begin(),
                                t->Parent->Keys[Child_num]);
          Rsibling->Keys.insert(Rsibling->Keys.begin(), t->Keys.begin(),
                                t->Keys.end());
          for (int i = 0; i < ((NonLeafNode *)t)->Children.size(); ++i) {
            ((NonLeafNode *)t)->Children[i]->Parent = Rsibling;
          }
          t->Parent->Keys.erase(t->Parent->Keys.begin() + Child_num);
          ((NonLeafNode *)t->Parent)
              ->Children.erase(((NonLeafNode *)t->Parent)->Children.begin() +
                               Child_num);
          t = Rsibling;
        } 
        // if not enough on left side, gotta merge
        else if (Lsibling != NULL &&
                   ((NonLeafNode *)Lsibling)->Children.size() - 1 <
                       floor((n + 2) / 2)) {
          ((NonLeafNode *)Lsibling)
              ->Children.insert(((NonLeafNode *)Lsibling)->Children.end(),
                                ((NonLeafNode *)t)->Children.begin(),
                                ((NonLeafNode *)t)->Children.end());
          Lsibling->Keys.insert(Lsibling->Keys.end(),
                                t->Parent->Keys[Child_num - 1]);
          Lsibling->Keys.insert(Lsibling->Keys.end(), t->Keys.begin(),
                                t->Keys.end());
          for (int i = 0; i < ((NonLeafNode *)t)->Children.size(); ++i) {
            ((NonLeafNode *)t)->Children[i]->Parent = Lsibling;
          }
          t->Parent->Keys.erase(t->Parent->Keys.begin() + Child_num - 1);
          ((NonLeafNode *)t->Parent)
              ->Children.erase(((NonLeafNode *)t->Parent)->Children.begin() +
                               Child_num);
          t = Lsibling;
        }
      }

      // reached at head & head has no keys 
      if (t->Parent == this->head && this->head->Keys.size() == 0) {
        // current node becomes head
        this->head = t;
        return;
      }
    }
  }
}
