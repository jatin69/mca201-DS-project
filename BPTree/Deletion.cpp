#include "BpTree.h"
#include "Node.h"
#include <math.h>

void BpTree::remove(int key) {
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
  int flag = 0;
  for (int i = 0; i < t->Keys.size(); ++i) {
    if (t->Keys[i] == key) {
      t->Keys.erase(t->Keys.begin() + i);
      ((LeafNode *)t)->Value.erase(((LeafNode *)t)->Value.begin() + i);
      flag = 1;
      break;
    }
  }
  if (!flag) {
    cout << "The key you want to delete does not exist!" << endl;
    return;
  }
  if (((LeafNode *)t)->Value.size() < ceil((n + 1) / 2) && t->Parent != NULL) {

    Node *Rsibling;
    Node *Lsibling;
    Rsibling = Lsibling = NULL;

    int Child_num = -1;
    for (int i = 0; i < ((NonLeafNode *)t->Parent)->Children.size(); ++i) {
      if (((NonLeafNode *)t->Parent)->Children[i] == t) {
        Child_num = i;
        break;
      }
    }
    if (Child_num - 1 >= 0) {
      Lsibling = ((NonLeafNode *)t->Parent)->Children[Child_num - 1];
    }

    if (Child_num + 1 < ((NonLeafNode *)t->Parent)->Children.size()) {
      Rsibling = ((NonLeafNode *)t->Parent)->Children[Child_num + 1];
    }

    if (Rsibling != NULL &&
        ((LeafNode *)Rsibling)->Value.size() - 1 >= ceil((n + 1) / 2)) {
      t->Keys.push_back(Rsibling->Keys.front());
      ((LeafNode *)t)->Value.push_back(((LeafNode *)Rsibling)->Value.front());
      Rsibling->Keys.erase(Rsibling->Keys.begin());
      ((LeafNode *)Rsibling)
          ->Value.erase(((LeafNode *)Rsibling)->Value.begin());
      t->Parent->Keys[Child_num] = t->Keys.back();
      return;
    } else if (Lsibling != NULL &&
               ((LeafNode *)Lsibling)->Value.size() - 1 >= ceil((n + 1) / 2)) {
      t->Keys.insert(t->Keys.begin(), Lsibling->Keys.back());
      ((LeafNode *)t)
          ->Value.insert(((LeafNode *)t)->Value.begin(),
                         ((LeafNode *)Lsibling)->Value.back());
      Lsibling->Keys.erase(Lsibling->Keys.end() - 1);
      ((LeafNode *)Lsibling)
          ->Value.erase(((LeafNode *)Lsibling)->Value.end() - 1);
      t->Parent->Keys[Child_num - 1] = Lsibling->Keys.back();
      return;
    } else {
      if (Rsibling != NULL &&
          ((LeafNode *)Rsibling)->Value.size() - 1 < ceil((n + 1) / 2)) {
        t->Keys.insert(t->Keys.end(), Rsibling->Keys.begin(),
                       Rsibling->Keys.end());
        ((LeafNode *)t)
            ->Value.insert(((LeafNode *)t)->Value.end(),
                           ((LeafNode *)Rsibling)->Value.begin(),
                           ((LeafNode *)Rsibling)->Value.end());
        ((LeafNode *)t)->Next = ((LeafNode *)Rsibling)->Next;

        t->Parent->Keys.erase(t->Parent->Keys.begin() + Child_num);
        ((NonLeafNode *)t->Parent)
            ->Children.erase(((NonLeafNode *)t->Parent)->Children.begin() +
                             Child_num + 1);
      } else if (Lsibling != NULL &&
                 ((LeafNode *)Lsibling)->Value.size() - 1 < ceil((n + 1) / 2)) {
        Lsibling->Keys.insert(Lsibling->Keys.end(), t->Keys.begin(),
                              t->Keys.end());
        ((LeafNode *)Lsibling)
            ->Value.insert(((LeafNode *)Lsibling)->Value.begin(),
                           ((LeafNode *)t)->Value.begin(),
                           ((LeafNode *)t)->Value.end());

        ((LeafNode *)Lsibling)->Next = ((LeafNode *)t)->Next;

        t->Parent->Keys.erase(t->Parent->Keys.begin() + Child_num - 1);
        ((NonLeafNode *)t->Parent)
            ->Children.erase(((NonLeafNode *)t->Parent)->Children.begin() +
                             Child_num);
        t = Lsibling;
      }

      while (t->Parent != this->head) {
        Rsibling = Lsibling = NULL;
        t = t->Parent;
        if (((NonLeafNode *)t)->Children.size() >= floor((n + 2) / 2)) {
          return;
        }
        int Child_num = -1;
        for (int i = 0; i < ((NonLeafNode *)t->Parent)->Children.size(); ++i) {
          if (((NonLeafNode *)t->Parent)->Children[i] == t) {
            Child_num = i;
            break;
          }
        }
        if (Child_num - 1 >= 0) {
          Lsibling = ((NonLeafNode *)t->Parent)->Children[Child_num - 1];
        }

        if (Child_num + 1 < ((NonLeafNode *)t->Parent)->Children.size()) {
          Rsibling = ((NonLeafNode *)t->Parent)->Children[Child_num + 1];
        }
        if (Rsibling != NULL &&
            ((NonLeafNode *)Rsibling)->Children.size() - 1 >=
                floor((n + 2) / 2)) {
          ((NonLeafNode *)t)
              ->Children.push_back(((NonLeafNode *)Rsibling)->Children.front());
          t->Keys.push_back(t->Parent->Keys[Child_num]);
          t->Parent->Keys[Child_num] = Rsibling->Keys.front();
          ((NonLeafNode *)Rsibling)
              ->Children.erase(((NonLeafNode *)Rsibling)->Children.begin());
          Rsibling->Keys.erase(Rsibling->Keys.begin());
          ((NonLeafNode *)t)->Children.back()->Parent = t;
          return;
        } else if (Lsibling != NULL &&
                   ((NonLeafNode *)Lsibling)->Children.size() - 1 >=
                       floor((n + 2) / 2)) {
          ((NonLeafNode *)t)
              ->Children.insert(((NonLeafNode *)t)->Children.begin(),
                                ((NonLeafNode *)Lsibling)->Children.back());
          t->Keys.insert(t->Keys.begin(), t->Parent->Keys[Child_num - 1]);
          t->Parent->Keys[Child_num] = Lsibling->Keys.back();
          ((NonLeafNode *)Lsibling)
              ->Children.erase(((NonLeafNode *)Lsibling)->Children.end() - 1);
          Lsibling->Keys.erase(Lsibling->Keys.end() - 1);
          ((NonLeafNode *)t)->Children.front()->Parent = t;
          return;
        } else if (Rsibling != NULL &&
                   ((NonLeafNode *)Rsibling)->Children.size() - 1 <
                       floor((n + 2) / 2)) {
          ((NonLeafNode *)Rsibling)
              ->Children.insert(((NonLeafNode *)Rsibling)->Children.begin(),
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
        } else if (Lsibling != NULL &&
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
      if (t->Parent == this->head && this->head->Keys.size() == 0) {
        this->head = t;
        return;
      }
    }
  }
}
