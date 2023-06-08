//============================================================================
// Name        : 21268_02_dsal.cpp
// Author      : Vibhav Sahasrabudhe
// Version     :
// Copyright   : I'm not the best coder
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
using namespace std;
#define MAX 5

class Entry{
private:
	string word;
	string meaning;
	Entry* next;
public:
	Entry(){
		word = "____";
		meaning = "----";
		next = NULL;
	}
	Entry(string w, string m){
		word = w;
		meaning = m;
		next = NULL;
		}
	friend class HT;
};

class HT{
private:
	Entry* ht[MAX];
public:
	HT(){
		for(int i=0; i<MAX; i++){
			ht[i] = NULL;
		}
	}
	int hashfun(string w);
	void insert(string w, string m);
	void display();
	bool search(string w);
	void del(string w);
};

int HT::hashfun(string w){
	int index;
	int len = w.length();
	index = w[0] + w[len-1];
	index = index%MAX;
	return index;
}

void HT::insert(string w, string m){
	Entry* temp;
	temp = new Entry(w, m);
	int hi = hashfun(w);
	if(ht[hi] == NULL){
		ht[hi] = temp;
	} else {
		Entry* t;
		t = ht[hi];
		while(t->next != NULL){
			t = t->next;
		}
		t->next = temp;
	}
	cout<<"Entry inserted!\n";
}

bool HT::search(string w){
	int hi = hashfun(w);
	if(ht[hi] == NULL){
		cout<<"Not Found!!\n";
		return false;
	} else {
		Entry* t;
		t = ht[hi];
		while(t->next != NULL){
			if(t->word == w){
				cout<<"\nFound!!\n";
				cout<<t->word<<": "<<t->meaning<<endl;
				return true;
				break;
			} else {
				t = t->next;
			}
		}
		if(t->word == w){
			cout<<"\nFound!!\n";
			cout<<t->word<<": "<<t->meaning<<endl;
			return true;
		} else {
			cout<<"Not Found!!\n";
			return false;
		}
	}
}

void HT::del(string w){
	int hi = hashfun(w);
	if(ht[hi] == NULL){
		cout<<"Entry doesnt exist!\n";
	} else {
		Entry* t, *p;
		t = ht[hi];
		p = t;
		if(t->word == w){
			ht[hi] = NULL;
			delete t;
			cout<<"Deleted!"<<endl;
		} else {
			bool flag = true;
			t = t->next;
			while(t->next != NULL){
				if(t->word == w){
					p->next = t->next;
					cout<<"Deleted!\n";
					flag = false;
					delete t;
				} else {
					p = p->next;
					t = t->next;
				}
			}
			if(flag){
				if(t->word == w ){
					p->next = NULL;
					delete t;
					cout<<"Deleted!\n";
				} else {
					cout<<"Entry doesnt exist!\n";
				}
			}
		}
	}
}

void HT::display(){
	cout<<"\n\n--------DICTIONARY--------\n\n";
	for(int i=0; i<MAX; i++){
		cout<<i<<": ";
		if(ht[i]==NULL){
			cout<<"----"<<endl;
		} else {
			Entry* t;
			t = ht[i];
			while(t->next != NULL){
				cout<<t->word<<" - "<<t->meaning<<" ---> ";
				t = t->next;
			}
			cout<<t->word<<" - "<<t->meaning<<endl;
		}
	}
}

int main() {
	HT h;
	char ch = 'y';
	while(ch == 'y'){
		int cho;
		cout<<"\n1. Insert\n2. Search\n3. Display\n4. Delete\n";
		cout<<"Enter your choice: ";
		cin>>cho;
		if(cho == 1){
			cout<<"Enter the number of entries: ";
			int n;
			cin>>n;
			for(int i=0; i<n; i++){
				string a, b;
				cout<<"\nEnter the word: ";
				cin>>a;
				cout<<"Enter the meaning: ";
				cin>>b;
				h.insert(a, b);
			}
		} else if(cho == 2){
			cout<<"Enter word to search: ";
			string w;
			cin>>w;
			h.search(w);
		} else if(cho == 3){
			h.display();
		} else if(cho == 4){
			cout<<"Enter element to be deleted: ";
			string t;
			cin>>t;
			h.del(t);
		}

		cout<<"\nDo you wish to continue? (y/n): ";
		cin>>ch;
	}
	return 0;
}
