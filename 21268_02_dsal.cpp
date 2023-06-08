//============================================================================
// Name        : 21268_02_dsal.cpp
// Author      : Vibhav Sahasrabudhe
// Version     :
// Copyright   : I'm not the best coder
// Description : Hello World in C++, Ansi-style
//============================================================================

#include<bits/stdc++.h>
using namespace std;
#define MAX 20

class Node{
private:
	int data;
	Node* rchild;
	Node* lchild;
	friend class BT;
	friend class Queue;
	friend class Stack;
public:
	Node(){
		data = 0;
		rchild = NULL;
		lchild = NULL;
	}
	Node(int d){
		data = d;
		rchild = NULL;
		lchild = NULL;
	}
};

class Stack{
	private:
	int top;
	Node* data[MAX];
public:
	Stack(){
		top = -1;
	}
	void push(Node* p);
	Node* pop();
	bool is_full();
	bool is_empty();
};

void Stack::push(Node* p){
	if(!is_full()){
		data[++top]=p;
	} else {
		cout<<"Stack Overflow!"<<endl;
	}
}

Node* Stack::pop(){
	if(!is_empty()){
		return data[top--];
	} else {
		return NULL;
	}
}

bool Stack::is_empty(){
	if(top==-1)
		return true;
	return false;
}

bool Stack::is_full(){
	if(top==MAX-1)
		return true;
	return false;
}

class Queue{
private:
	Node* data[MAX];
	int front, rear;
public:
	Queue(){
		front = rear = -1;
	}
	void push(Node*);
    Node * pop();
    bool is_empty();
    bool is_full();
    Node* first();
};

void Queue::push(Node* p){
	if(!is_full())
    {
        if(is_empty())
        {
            front=0;
        }
        rear=(rear+1)%MAX;
        data[rear]=p;
    }
}

Node* Queue::pop(){
	if(!is_empty())
    {
        Node* p=data[front];
        if(front==rear)
        {
            front=rear=-1;
        }
        else
        {
            front=(front+1)%MAX;
        }
        return p;
    }
    else
        return NULL;
}

Node* Queue::first()
  {
    return data[front];
  }

bool Queue::is_full(){
	if(front==(rear+1)%MAX)
        return 1;
    return 0;
}

bool Queue::is_empty(){
	if(rear==-1)
        return 1;
    return 0;
}

class BT{
private:
	Node* root;
public:
	BT(){
		root = NULL;
	}
	Node* getr(){
	    	return root;
	    }
	void setRoot(Node *t){
		root=t;
	}

	Node* createR(); //recursive
	void create(); //non-recursive
	void preorderR(Node* root);//recursive
	void postorderR(Node* root);//recursive
	void inorderR(Node* root);//recursive
	void inorder();//non-recursive
	void preorder();//non-recursive
	void postorder();//non-recursive

	Node* mirror(Node* p);
	int height(Node* p);
	void delete_tree(Node* p);
	int countLeaf(Node* p);
	int countInternal(Node* p);
	Node* copy(Node* p);
	void operator=(BT &t);

};

void BT::create(){
	Queue obj;
    Node *p=NULL;
    int x;
    if(root==NULL)
    {
        cout<<"Enter integer Data (or -1)\n";
        cin>>x;
        if(x==-1)
            return;
        root=new Node(x);
        obj.push(root);
    }
    p=root;
    while(!obj.is_empty())
    {
        p=obj.pop();
        cout<<"Enter Left of "<<p->data<<" (OR -1) \n";
        cin>>x;
        if(x!=-1)
        {
            p->lchild=new Node(x);
            obj.push(p->lchild);
        }
        cout<<"Enter Right of "<<p->data<<" (OR -1) \n";
        cin>>x;
        if(x!=-1)
        {
            p->rchild=new Node(x);
            obj.push(p->rchild);
        }
    }
}

Node* BT::createR(){
	cout<<"\nEnter data: ";
	int d;
	cin>>d;
	if(d==-1){
		return NULL;
	}
	Node* p;
	p = new Node(d);
	cout<<"Enter left child: ";
	p->lchild = createR();
	cout<<"Enter right child: ";
	p->rchild = createR();
	return p;
}

void BT::inorder(){
	cout<<"INORDER TRAVERSAL NON-RECURSIVE\n";
    Stack S;
    Node *p=root;
    while(p!=NULL)
    {
        S.push(p);
        p=p->lchild;
    }
    while(!S.is_empty())
    {
        p=S.pop();
        cout<<p->data<<"\n";
        p=p->rchild;
        while(p!=NULL)
        {
            S.push(p);
            p=p->lchild;
        }
    }
    cout<<"\n";
}

void BT::inorderR(Node* root){
    if (root != NULL){
        inorderR(root->lchild);
        cout << root->data <<endl;
        inorderR(root->rchild);
    }
}

void BT::preorder(){
	cout<<"PREORDER TRAVERSAL NON-RECURSIVE\n";
    Stack S;
    Node *p=root;
    S.push(p);
    while(!S.is_empty())
    {
        p=S.pop();
        cout<<p->data<<"\n";
        if(p->rchild!=NULL)
            S.push(p->rchild);
        if(p->lchild!=NULL)
            S.push(p->lchild);
    }
    cout<<"\n";
}

void BT::preorderR(Node* root){
	if(root != NULL){
		cout << root->data << endl;
		preorderR(root->lchild);
		preorderR(root->rchild);
	}
}

void BT::postorder(){
	cout<<"POSTORDER TRAVERSAL NON-RECURSIVE\n";
    Stack S1,S2;
    Node *p=root;
    S1.push(p);
    while(!S1.is_empty())
    {
        p=S1.pop();
        S2.push(p);
        if(p->lchild!=NULL)
            S1.push(p->lchild);
        if(p->rchild!=NULL)
            S1.push(p->rchild);
    }
    while(!S2.is_empty())
    {
        p=S2.pop();
        cout<<p->data<<"\n";
    }
    cout<<"\n";
}

void BT::postorderR(Node* root){
	if(root != NULL){
		postorderR(root->lchild);
		postorderR(root->rchild);
		cout << root->data << endl;
	}
}

Node* BT::mirror(Node* p){
	if(p!=NULL){
		mirror(p->lchild);
		mirror(p->rchild);
		Node* temp;
		temp = p->rchild;
		p->rchild = p->lchild;
		p->lchild = temp;
	}
}

void BT::delete_tree(Node* p){
	if(p!=NULL){
		delete_tree(p->lchild);
		delete_tree(p->rchild);
		cout<<"Deleted node: "<<p->data<<endl;
		delete p;
	}
}

Node* BT::copy(Node* p){
	Node* ct = NULL;
	if(p!=NULL){
		ct = new Node(p->data);
		ct->lchild = copy(p->lchild);
		ct->rchild = copy(p->rchild);
	}
	return ct;
}

void BT::operator =(BT &t){
	root = copy(t.root);
}

int BT::countInternal(Node* p){
	if(p==NULL)
		return 0;
	if(p->lchild==NULL && p->rchild==NULL)
		return 0;
	else {
		int l,r;
	    cout<<p->data<<" ";
	    l=countInternal(p->lchild);
        r=countInternal(p->rchild);
	    return 1+l+r;
	}
}

int BT::countLeaf(Node* p){
	if(p==NULL)
	    return 0;
	if(p->lchild==NULL&&p->rchild==NULL){
	    cout<<p->data<<" ";
	    return 1;
	}else{
	    return countLeaf(p->lchild)+countLeaf(p->rchild);
	}
}

int BT::height(Node* p){
	if(p==NULL){
		return 0;
	} else {
		int l, r;
		l = height(p->lchild);
		r = height(p->rchild);
		if(l>r){
			return l+1;
		} else {
			return r+1;
		}
	}
}

int main(){
	BT b;
	char loop;
	char loop2;
	loop = 'y';
	loop2 = 'y';
	cout<<"\n1. Recursive\n2. Non-Recursive\n";
	cout<<"Enter your choice: ";
	int c;
	cin>>c;
	if(c==1){
		while(loop == 'y'){
			cout<<"\n1. Insert and Traversal (recursive)\n2. Mirror the tree\n3. Copy tree\n4. Count Internal Nodes\n5. Count Leaf Nodes\n6. Calculate height\n7. Delete tree\n";
			int cr;
			cout<<"Enter your choice: ";
			cin>>cr;
			if(cr==1){
				Node* t = b.createR();
				b.setRoot(t);
				cout<<"\nINORDER TRAVERSAL RECURSIVE\n";
				b.inorderR(t);
				cout<<"\nPREORDER TRAVERSAL RECURSIVE\n";
				b.preorderR(t);
				cout<<"\nPOSTORDER TRAVERSAL RECURSIVE\n";
				b.postorderR(t);
			} else if(cr==2){
				Node* t = b.getr();
				b.mirror(t);
				cout<<"\nMirrored tree inorder\n";
				b.inorderR(t);
			} else if(cr==3){
				BT n;
				n = b;
				cout<<"\nTree copied!\n";
				cout<<"Old tree inorder\n";
				b.inorderR(b.getr());
				cout<<"New tree inorder\n";
				n.inorderR(n.getr());
			} else if(cr==4){
				Node* t = b.getr();
				int ans = b.countInternal(t);
				cout<<"\nNo. of internal nodes: "<<ans<<endl;
			} else if(cr==5){
				Node* t = b.getr();
				int ans = b.countLeaf(t);
				cout<<"\nNo. of leaf nodes: "<<ans<<endl;
			} else if(cr==6){
				Node* t = b.getr();
				int ans = b.height(t);
				cout<<"\nThe height of tree is: "<<ans<<endl;
			} else if(cr==7){
				Node* t = b.getr();
				b.delete_tree(t);
				t = NULL;
				b.inorderR(t);
			} else {
				cout<<"Wrong choice!"<<endl;
			}
			cout<<"Do you wish to continue in 'Recursive'? (y/n)";
			cin>>loop;
		}
	} else if(c==2){
		b.create();
		b.inorder();
		b.preorder();
		b.postorder();
	}
	return 0;
}