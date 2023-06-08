#include <iostream>
using namespace std;

/*Problem Statement:A dictionary stores keywords and its meanings .
Provide facility for adding new keywords, deleting keywords ,updating values of entry
Provide facility to display whole data sorted in ascending or descending order .
Also find how many maximum cmparisons may require for finding any keyword .Use height balanced tree and find complexiety */


class Node{
	Node *left;
	Node *right;
	int height=1;
	int key;
	string value;
public:
	Node(int k,string val){
		left=right=NULL;
		key=k;
		value=val;
	}
	friend class AVLTree;
};

class AVLTree{
public:
	Node *root=NULL;
	int nodeHeight(Node *p){
		if (p==NULL) return 0;
		return p->height;
	}

	void updateHeight(Node *p){
		if (p==NULL) return;
		p->height=max(nodeHeight(p->left),nodeHeight(p->right)+1);
	}

	int balanceFactor(Node *p){
		if (p==NULL) return 0;
		return nodeHeight(p->left)-nodeHeight(p->right);
	}

	Node *LLRotation(Node *p){
		Node *newroot=p->left;
		newroot->right=p;
		p->left=NULL;
		updateHeight(p);
		updateHeight(newroot);
		return newroot;
	}

	Node *RRRotation(Node *p){
		Node *newroot=p->right;
		newroot->left=p;
		p->right=NULL;
		updateHeight(p);
		updateHeight(newroot);
		return newroot;
	}

	Node *LRRotation(Node *p){
		p->left=RRRotation(p->left);
		return LLRotation(p);
	}

	Node *RLRotation(Node *p){
		p->right=LLRotation(p->right);
		return RRRotation(p);
	}

	Node *balance(Node *node){
		if (balanceFactor(node)==2){
			if (balanceFactor(node->left)<0){
				node=LRRotation(node);
			}
			else{
				node=LLRotation(node);
			}
		}
		else if (balanceFactor(node)==-2){
			if (balanceFactor(node->right)<0){
				node=RRRotation(node);
			}
			else{
				node=RLRotation(node);
			}
		}
		updateHeight(node);
		return node;
	}

	Node *insertSubTree(Node *curr,int k,string val){
		if (curr==NULL){
			Node *newNode=new Node(k,val);
			curr=newNode;
			return curr;
		}
		else if (curr->key>k){
			curr->left=insertSubTree(curr->left,k,val);
		}
		else if (curr->key<k){
			curr->right=insertSubTree(curr->right,k,val);
		}
		else{
			curr->value=val;
			return curr;
		}
		return balance(curr);

	}

	Node* update(Node *curr,int k,string val){
		if (curr==NULL){
			return NULL;
		}
		else if (curr->key>k){
			curr->left=update(curr->left,k,val);
		}
		else if (curr->key<k){
			curr->right=update(curr->right,k,val);
		}
		else{
			curr->value=val;
			return curr;
		}

	}
	Node* ser(Node *curr,int k){
		if (curr==NULL){
			return NULL;
		}
		else if (curr->key>k){
			curr->left=ser(curr->left,k);
		}
		else if (curr->key<k){
			curr->right=ser(curr->right,k);
		}
		else{
			return curr;
		}
	}

	void inorder(Node *p){
		if (p==NULL){
			return;
		}
		inorder(p->left);
		cout<<p->key<<"\t"<<p->value<<endl;
		inorder(p->right);
	}

	void display(){
		cout<<"KEY\t"<<"VALUE"<<endl;
		inorder(root);
	}

	void insert(int key,string value){
		root=insertSubTree(root,key,value);
	}

	void upda(int key,string value){
		root=update(root,key,value);
	}

	void search(int key){
		Node *ans=ser(root,key);
		if (ans==NULL){
			cout<<"Not found"<<endl;
		}
		else{
			cout<<"Found"<<endl;
		}
	}

	void search1(int key) {
		Node* curr = root;
		int comparisons = 0;
		while (curr != NULL) {
			comparisons++;
			if (curr->key == key) {
				cout << "Found" << endl;
				cout << "Number of comparisons: " << comparisons << endl;
				return;
			} else if (curr->key > key) {
				curr = curr->left;
			} else {
				curr = curr->right;
			}
		}
		cout << "Not found" << endl;
		cout << "Number of comparisons: " << comparisons << endl;
	}

};

int main(){
	AVLTree t1;
	t1.insert(10,"Hello");
	t1.insert(20,"Lllo");
	t1.insert(30,"llo");
	//cout<<"Hello"<<endl;
	t1.display();
	cout<<endl;
	cout<<"Updated"<<endl;
	t1.upda(20,"Aditya");
	t1.display();
	t1.search1(20);
	t1.search1(120);
	return 0;
}