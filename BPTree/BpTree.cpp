#include "BpTree.h"
#include <math.h>

BpTree::BpTree(int nptr)
{
    /*
	Objective: constructor function of B+ Tree class aims at initializing the tree
	Approach: Self implementation of B+ Trees is being used
	Input Parameters:
        nptr: degree of the b+ tree
	Return Values: None
	*/

    this->n = nptr;
    this->head = new LeafNode();
}

void BpTree::insert(int key, string value)
{
    /*
	Objective: function aims at inserting elements to the B+ Tree
	Approach: Self implementation of B+ trees is being used
	Input Parameters:
		key: element to be inserted as entered by the user
		value: value of the key entered
	Return Values: None
	*/

    Node* t=this->head;
    while (!t->isLeaf){     //find the appropriate location for the element
        int flag = 0;
        for (int i=0;i<t->Keys.size();++i){
            if(t->Keys[i]>key){
                t = ((In_Node*)t)->Children[i];
                flag = 1;
                break;
            }
        }
        if(!flag){
            t = ((In_Node*)t)->Children[t->Keys.size()];
        }
    }
    if(t->Keys.size()==0||key>t->Keys.back()){
        t->Keys.push_back(key);
        ((LeafNode*)t)->Value.push_back(value);
    }
    else{
        for(int i=0;i<t->Keys.size();++i){     //insertion into the leaf node
            if(t->Keys[i]==key){
                cout<<"You cannot insert duplicate keys!"<<endl;
                return;
            }
            else if(t->Keys[i]>key){
                t->Keys.insert(t->Keys.begin() + i, key);
                ((LeafNode*)t)->Value.insert(((LeafNode*)t)->Value.begin() + i, value);
                break;
            }
        }
    }
    if(t->Keys.size()>this->n){ //splitting the leaf node
        Node* tnew = new LeafNode();
        tnew->Parent = t->Parent;
        tnew->Keys.insert(tnew->Keys.begin(), t->Keys.begin()+ceil((n+1)/2), t->Keys.end());
        ((LeafNode*)tnew)->Value.insert(((LeafNode*)tnew)->Value.begin(), ((LeafNode*)t)->Value.begin()+ceil((n+1)/2), ((LeafNode*)t)->Value.end());
        t->Keys.erase(t->Keys.begin()+ceil((n+1)/2), t->Keys.end());
        ((LeafNode*)t)->Value.erase(((LeafNode*)t)->Value.begin()+ceil((n+1)/2), ((LeafNode*)t)->Value.end());
        ((LeafNode*)tnew)->Next=((LeafNode*)t)->Next;
            ((LeafNode*)t)->Next=tnew;
        key = t->Keys[ceil((n+1)/2)-1];
        while(t->Parent!=NULL){
            t=t->Parent;
            for(int i=0;i<t->Keys.size();++i){
                if(key>t->Keys.back()){
                    t->Keys.push_back(key);
                    ((In_Node*)t)->Children.push_back(tnew);
                    break;
                }
                else if(t->Keys[i]>key){
                    t->Keys.insert(t->Keys.begin() + i, key);
                    ((In_Node*)t)->Children.insert(((In_Node*)t)->Children.begin()+i+1, tnew);
                    break;
                }
            }
            if(t->Keys.size()>this->n){
                Node* nright = new In_Node();
                nright->Parent = t->Parent;
                nright->Keys.insert(nright->Keys.begin(), t->Keys.begin()+floor((n+2)/2), t->Keys.end());
                ((In_Node*)nright)->Children.insert(((In_Node*)nright)->Children.begin(), ((In_Node*)t)->Children.begin()+floor((n+2)/2), ((In_Node*)t)->Children.end());
                for(int i=floor((n+2)/2);i<((In_Node*)t)->Children.size();++i){
                    ((In_Node*)t)->Children[i]->Parent = nright;
                }
                key = t->Keys[floor((n+2)/2)-1];
                t->Keys.erase(t->Keys.begin()+floor((n+2)/2)-1, t->Keys.end());
                ((In_Node*)t)->Children.erase(((In_Node*)t)->Children.begin()+floor((n+2)/2), ((In_Node*)t)->Children.end());
                tnew = nright;
            }
            else{
                tnew->Parent = t;
                return;
            }


        }
        if(t->Parent==NULL){
            t->Parent = new In_Node();
            ((In_Node*)t->Parent)->Children.insert(((In_Node*)t->Parent)->Children.begin(), t);
            ((In_Node*)t->Parent)->Children.insert(((In_Node*)t->Parent)->Children.begin()+1,tnew);
            if(t->isLeaf){
                (t->Parent)->Keys.insert((t->Parent)->Keys.begin(),t->Keys.back());
            }
            else{
                (t->Parent)->Keys.insert((t->Parent)->Keys.begin(),((In_Node*)t)->Children.back()->Keys.back());
            }
            tnew->Parent=t->Parent;
            head = t->Parent;
        }

    }
    else{
        return;
    }

}


string BpTree:: find(int key){

    /*
	Objective: function aims at searching an element in the B+ Tree
	Approach: Self implementation of B+ trees is being used
	Input Parameters:
		key: element to be searched as entered by the user
	Return Values: None
	*/

    Node* t=this->head;
    while (!t->isLeaf){    //find the proper location
        int flag = 0;
        for (int i=0;i<t->Keys.size();++i){
            if(t->Keys[i]>=key){
                t = ((In_Node*)t)->Children[i];
                flag = 1;
                break;
            }
        }
        if(!flag){
            t = ((In_Node*)t)->Children[t->Keys.size()];
        }
    }
    for(int i=0;i<t->Keys.size();++i){
        if(t->Keys[i]==key){
            return ((LeafNode*)t)->Value[i];
        }
    }
    return "This key does not exist in this B+ tree!";
}


void BpTree:: printKeys()
{
    /*
	Objective: function aims at printing all the keys in the B+ Tree
	Approach: Self implementation of B+ trees is being used
	Input Parameters: None
	Return Values: None
	*/

    if(head->Keys.size()==0){
        cout<<"[]"<<endl;
        return;
    }
    vector<Node*> q;
    q.push_back(head);
    while(q.size()){
        unsigned long size = q.size();
        for(int i=0;i<size;++i){
            if(!q[i]->isLeaf){
                for(int j=0;j<((In_Node*)q[i])->Children.size();++j){
                        q.push_back(((In_Node*)q[i])->Children[j]);
                }
            }
            cout<<"[";
            int nk=0;
            for(nk=0;nk<q[i]->Keys.size()-1;++nk){
                cout<<q[i]->Keys[nk]<<",";
            }
            cout<<q[i]->Keys[nk]<<"] ";
        }
        q.erase(q.begin(),q.begin()+size);
        cout<<endl;
    }

}


void BpTree:: printValues()
{
    /*
	Objective: function aims at printing all the string values in the B+ Tree
	Approach: Self implementation of B+ trees is being used
	Input Parameters: None
	Return Values: None
	*/

    Node* t = this->head;
    while(!t->isLeaf){
        t = ((In_Node*)t)->Children[0];
    }
    while(t!=NULL){
        for(int i=0;i<t->Keys.size();++i){
            cout<<((LeafNode*)t)->Value[i]<<endl;
        }
        t=((LeafNode*)t)->Next;
    }
}

BpTree:: ~BpTree()
{
    /*
	Objective: destructor function of B+ Tree class aims at deleting the tree
	Approach: Self implementation of B+ Trees is being used
	Input Parameters: None
	Return Values: None
	*/

    if(this->head){
        delete this->head;
    }
}
