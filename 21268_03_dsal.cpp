//============================================================================
// Name        : 21268_03_dsal.cpp
// Author      : Vibhav Sahasrabudhe
// Version     :
// Copyright   : I'm not the best coder
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

class Node{
private:
	int data;
	Node* lchild;
	Node* rchild;
	bool lbit, rbit;
public:
	Node(){
		data = 0;
		lbit = rbit = 0;
		lchild = rchild = NULL;
	}
	Node(int key){
		data = key;
		lbit = rbit = 0;
		lchild = rchild = NULL;
	}
	friend class TBST;
};

class TBST{
private:
	Node* header;
	Node* root;
public:
	TBST(){
		root = header = NULL;
	}
	void createTBST(int key);
	void inorder();
	void preorder();
	void deleteNode(int key);
	void search(Node* &p, Node* &t, int key);
	Node* leftmost(Node* temp){
		while(temp->lbit == 1){
			temp = temp->lchild;
		}
		return temp;
	}
};

void TBST::createTBST(int key){
	if(root == NULL){
		header = new Node(-99);
		root = new Node(key);
		header->lbit = 1;
		header->lchild = root;
		header->rchild = header;
		root->lchild = root->rchild = header;
	} else {
		Node* temp;
		Node* ptr = root;
		while(1){
			if(ptr->data > key){
				if(ptr->lbit == 1){
					ptr = ptr->lchild;
				} else {
					temp = new Node(key);
					temp->lchild = ptr->lchild;
					temp->rchild = ptr;
					ptr->lbit = 1;
					ptr->lchild = temp;
					break;
				}
			} else {
				if(ptr->rbit == 1){
					ptr = ptr->rchild;
				} else {
					temp = new Node(key);
					temp->rchild = ptr->rchild;
					temp->lchild = ptr;
					ptr->rbit = 1;
					ptr->rchild = temp;
					break;
				}
			}
		}
	}
}

void TBST::inorder(){
	Node* t = leftmost(root);
	while(t != header){
		cout<<t->data<<" ";
		if(t->rbit==1){
			t = t->rchild;
			t = leftmost(t);
		} else {
			t = t->rchild;
		}
	}
}

void TBST::preorder(){
	if(root==NULL){
		cout<<"Tree NULL!"<<endl;
		return;
	}
	Node* temp = root;

	while(temp != header){
		cout<<temp->data<<" ";
		if(temp->lbit == 1){
			temp = temp->lchild;
		} else {
			if(temp->rbit == 1){
				temp = temp->rchild;
			} else {
				while(temp->rbit==0 && temp != header){
					temp = temp->rchild;
				}
				if(temp->rbit == 1){
					temp = temp->rchild;
				}
			}
		}
	}
}

void TBST::search(Node* &p, Node* &t, int key){
	while(t != header){
		if(t->data == key){
			break;
		} else if(t->data > key){
			p = t;
			t = t->lchild;
		} else {
			p = t;
			t = t->rchild;
		}
	}
}

void TBST::deleteNode(int key){
	Node *parent = NULL;
    Node *current = root;
    search(parent,current,key);

    if(current->lbit == 1 && current->rbit == 1){
       Node *c = current->rchild;
       Node *c_parent = current;
       while(c->lbit != 0){
       	c_parent = c;
        c = c->lchild;
       }

       int temp = current->data;
       current->data = c->data;
       c->data = temp;
       parent = c_parent;
       current = c;
	}

	if(current->rbit == 0 && current->lbit == 0){
		if(parent->rchild == current){
		parent->rchild = current->rchild;
		parent->rbit = 0;
		} else {
		parent->lchild = current->lchild;
		parent->lbit = 0;
		}
	}

	if(current->lbit == 0 && current->rbit == 1){
		Node *child = current->rchild;
		if(parent->lchild == current){
		child->lchild = current->lchild;
		parent->lchild = child;
		delete current;
		} else {
		parent->rchild = child;
		child->lchild = current->lchild;
		delete current;
		}
	}

	if(current->lbit == 1 && current->rbit == 0){
		Node *child = current->lchild;
		if(parent->lchild == current){
		parent->lchild = child;
		child->rchild = current->rchild;
		delete current;
		} else {
		parent->rchild = child;
		child->rchild = current->rchild;
		delete current;
		}
	}
}

int main() {
	TBST b;
	char ch;
	ch = 'y';
	while(ch == 'y'){
		cout<<"\n\n-----------------MENU-----------------\n";
		cout<<"1. Create TBST\n2. Inorder Traversal\n3. Preorder traversal\n4. Delete Node\n";
		cout<<"Enter your choice: ";
		int c;
		cin>>c;
		if(c==1){
			cout<<"\nEnter the number of elements in TBST: ";
			int n;
			cin>>n;
			while(n!=0){
				cout<<"Enter data element: ";
				int d;
				cin>>d;
				b.createTBST(d);
				n--;
			}
		} else if(c==2){
			cout<<"Inorder traversal: \n";
			b.inorder();
		} else if(c==3){
			cout<<"\nPreorder Traversal: "<<endl;
			b.preorder();
		} else if(c==4){
			int key;
			cout<<"Enter element to be deleted: ";
			cin>>key;
			cout<<"\nBefore deletion: ";
			b.inorder();
			b.deleteNode(key);
			cout<<"\nAfter deletion: ";
			b.inorder();
		}
		cout<<"\nDo you wish to continue? (y/n): ";
		cin>>ch;
	}

return 0;
}
