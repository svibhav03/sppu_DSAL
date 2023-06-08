//============================================================================
// Name        : 21268_01_dsal.cpp
// Author      : Vibhav Sahasrabudhe
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

class node{
    string w, m;
    node *lchild, *rchild;
public:
    node(){
        lchild = NULL;
        rchild = NULL;
    }
    node(string w, string m){
        this->w = w;
        this->m = m;
        rchild = lchild = NULL;
    }
    friend class BST;
};

class BST{
    node *root;
public:
    BST(){root = NULL;}
    void insert(string w, string m);
    string search(string w);
    void search(string word, node*& curr, node*& par);
    void display(node *root);
    void update(string w, string nm);
    void del(string k,node * curr , node * par);
    node* getr(){
    	return root;
    }
};

void BST::insert(string w, string m){
	        node *nnode = new node(w, m);
	        if (root == NULL){
	            root = nnode;
	        }
	        else{
	            node *temp = root;
	            node *parent = NULL;

	            while (temp != NULL){
	                parent = temp;
	                if (temp->w > w){
	                    temp = temp->lchild;
	                }
	                else{
	                    temp = temp->rchild;
	                }
	            }
	            if (parent->w > w){
	                parent->lchild = nnode;
	            }
	            else{
	                parent->rchild = nnode;
	            }
	        }
	    cout<<"\nElement inserted!"<<endl;
}

string BST::search(string w){
    node *temp = root;
    while (temp != NULL){
        if (temp->w == w){
        	string ans;
        	ans = temp->w + ": " + temp->m;
            return ans;
        }
        else if (temp->w > w){
            temp = temp->lchild;
        }
        else{
            temp = temp->rchild;
        }
    }
    return "not found";
}
void BST::search(string word, node*& curr, node*& par){
    while(curr != NULL){
    	if(curr->w == word){
    		return;
    	} else if(curr->w > word){
    		par = curr;
    		curr = curr->lchild;
    	} else {
    		par = curr;
    		curr = curr->rchild;
    	}
    }
}

void BST::display(node* root){
    if (root != NULL){
        display(root->lchild);
        cout << root->w << " : " << root->m << endl;
        display(root->rchild);
    }
}

void BST::update(string w, string nm){
    node *temp = root;
    while (temp != NULL){
        if (temp->w == w){
            temp->m = nm;
            cout << "Updated successfully\n" << endl;
            display(root);
            return;
        }
        else if (temp->w > w){
            temp = temp->lchild;
        }
        else{
            temp = temp->rchild;
        }
    }
    cout << "word not found" << endl;
    return;
}

void BST::del(string k,node * curr , node * par){
		search(k,curr,par);
		if(curr==NULL){
			cout<<"No such word exists in the dictionary!"<<endl;
			return;
		}
		else if(curr == root){
			if(curr->lchild==NULL && curr->rchild==NULL){
				root = NULL;
			}
			else if(curr->lchild!=NULL && curr->rchild==NULL){
				root = curr->lchild;
			}
			else if(curr->lchild==NULL && curr->rchild!=NULL){
				root = curr->rchild;
			}
			else{
				node *temp = curr->rchild;
				node *temp_parent = curr;
				while(temp->lchild!=NULL){
					temp_parent = temp;
					temp = temp->lchild;
				}
				string s,l;
				s = curr->w;
				l = curr->m;
				curr->w = temp->w;
				curr->m = temp->m;
				temp->w = s;
				temp->m = l;
				del(s,temp,temp_parent);
			}
		}
		else{
			if(curr->lchild==NULL && curr->rchild==NULL){
				if(par->lchild==curr){
					par->lchild = NULL;
				}
				else{
					par->rchild = NULL;
				}
			}
			else if(curr->lchild!=NULL && curr->rchild==NULL){
				node *child = curr->lchild;
				if(par->lchild==curr){
					par->lchild = child;
				}
				else{
					par->rchild = child;
				}
			}
			else if(curr->lchild==NULL && curr->rchild!=NULL){
				node *child = curr->rchild;
				if(par->lchild==curr){
					par->lchild = child;
				}
				else{
					par->rchild = child;
				}
			}
			else{
				node *temp = curr->rchild;
				node *temp_parent = curr;
				while(temp->lchild!=NULL){
					temp_parent = temp;
					temp = temp->lchild;
				}
				string s,l;
				s = curr->w;
				l = curr->m;
				curr->w = temp->w;
				curr->m = temp->m;
				temp->w = s;
				temp->m = l;
				del(s,temp,temp_parent);
			}
			cout<<"deleted !"<<endl;
		}
	}

int main(){
	BST b;
	char choice = 'y';
	while(choice == 'y'){
		cout<<"\n1. Insert element\n2. Delete element\n3. Update element\n4. "
				"Search element\n5. Display entire dictionary\n"<<endl;
		cout<<"Enter your choice: ";
		int c;
		cin>>c;
		if(c==1){
			cout<<"Enter the word and meaning:\n";
			string w, m;
			cout<<"Word: ";
			cin>>w;
			cout<<"Meaning: ";
			cin>>m;
			b.insert(w, m);
		} else if(c==2){
			cout<<"Enter the element you wish to delete: ";
			string d;
			cin>>d;
			b.del(d, b.getr(), NULL);
		} else if(c==3){
			cout<<"Enter the word and it's new meaning: \n";
			string s, n;
			cout<<"Word: ";
			cin>>s;
			cout<<"New meaning: ";
			cin>>n;
			b.update(s, n);
		} else if(c==4){
			cout<<"Enter word you wish to search: ";
			string wo;
			cin>>wo;
			cout<<b.search(wo);
		} else if(c==5){
			b.display(b.getr());
		} else {
			cout<<"Enter a valid response!\n";
		}
		cout<<"\nDo you wish to continue? (y/n): "<<endl;
		cin>>choice;
	}
    return 0;
}
