//============================================================================
// Name        : 21268_04_dsal.cpp
// Author      : Vibhav Sahasrabudhe
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
#define MAX 5

class Entry{
private:
	int mobile;
	string name;
public:
	Entry(){
		mobile = -1;
		name = "blank";
	}
	Entry(int v, string n){
		mobile = v;
		name = n;
	}
	friend class HT;
};

class HT{
private:
	Entry* ht[MAX];
	Entry* temp;
public:
	void insertWithout(int key, string n);
	void insertWith(int key, string n);
	int hashfun(int key);
	int search(int key);
	void displayHT();
	void create();
	void update(int key, string n);
	void delete_num(int key);
	int searchd(int key);
};

void HT::create(){
	for(int i=0; i<MAX; i++){
		Entry* temp;
		temp = new Entry(-1, "-----");
		ht[i] = temp;
	}
}

void HT::update(int key, string n){
	int index;
	int count;
	index = hashfun(key);
	if(ht[index]->mobile == key){
		ht[index]->name = n;
		cout<<"Name updated!\n";
	} else {
		while(ht[index]->mobile != key){
			index++;
			count++;
			index = index%MAX;
			if(count == MAX){
				break;
			}
		}
		if(count == MAX){
			cout<<"Key not found!\n";
		} else {
			ht[index]->name = n;
			cout<<"Name updated!\n";
		}
	}
}

void HT::displayHT(){
	cout<<"\n\n";
	for(int i=0; i<MAX; i++){
		cout << i << "		" << ht[i]->mobile << "		" << ht[i]->name << endl;
	}
}

void HT::insertWithout(int key, string n){
	Entry* temp;
	temp = new Entry(key, n);
	int hi;
	int count = 0;
	hi = hashfun(key);
	if(ht[hi]->mobile == -1)
		ht[hi] = temp;
	else{
		while((ht[hi]->mobile != -1) && (count <= MAX)){
			hi++;
			hi = hi%MAX;
			count++;
		}
		if(count == MAX){
			cout<<"Hash table full!\n";
		} else {
			ht[hi] = temp;
		}
	}
}

void HT::insertWith(int key, string n){
	Entry* temp;
	temp = new Entry(key, n);
	int hi;
	int tempin;
	int count = 0;
	hi = hashfun(key);
	if(ht[hi]->mobile == -1)
		ht[hi] = temp;
	else {
		tempin = hashfun(ht[hi]->mobile);
		if(hi == tempin){
			while((ht[hi]->mobile != -1) && (count <= MAX)){
				hi++;
				hi = hi%MAX;
				count++;
			}
			if(count == MAX){
				cout<<"Hash table full!\n";
			} else {
				ht[hi] = temp;
			}
		} else {
			Entry* t;
			t = ht[hi];
			ht[hi] = temp;
			while((ht[hi]->mobile != -1) && (count <= MAX)){
				hi++;
				hi = hi%MAX;
				count++;
			}
			if(count == MAX){
				cout<<"Hash table full!\n";
			} else {
				ht[hi] = t;
			}
		}

	}
}

int HT::hashfun(int key){
	return key%MAX;
}

int HT::search(int key){
	int ans;
	int coll = 1;
	ans = hashfun(key);
	if(ht[ans]->mobile == key){
		cout<<"Name: "<<ht[ans]->name<<endl;
		cout<<"Found at location "<<ans<<endl;
		cout<<"No of collisions: "<<coll<<endl;
		return ans;
	} else {
		while(ht[ans]->mobile != key){
			ans++;
			ans = ans%MAX;
			coll++;
			if(coll == MAX+1){
				break;
			}
		}
		if(coll == MAX+1){
			cout<<"Not found"<<endl;
			return -1;
		} else {
			cout<<"Name: "<<ht[ans]->name<<endl;
			cout<<"Found at location "<<ans<<endl;
			cout<<"No of collisions: "<<coll<<endl;
			return ans;
		}
	}
}

int HT::searchd(int key){
	int ans;
	int coll = 1;
	ans = hashfun(key);
	if(ht[ans]->mobile == key){
		return ans;
	} else {
		while(ht[ans]->mobile != key){
			ans++;
			ans = ans%MAX;
			coll++;
			if(coll == MAX+1){
				break;
			}
		}
		if(coll == MAX+1){
			return -1;
		} else {
			return ans;
		}
	}
}

void HT::delete_num(int key){
	int del_index;
	del_index = searchd(key);

	int main_hash = del_index;
	if(del_index == -1){
		cout<<"Number doesnt exist!\n";
	} else {
		ht[del_index]->mobile = -1;
		ht[del_index]->name = "----";
		int curr = del_index;
		for(int i=0; i<MAX; i++){
			curr++;
			curr = curr%MAX;
			int t_index;
			t_index = hashfun(ht[curr]->mobile);
			if(t_index == main_hash){
				ht[del_index] = ht[curr];
				del_index = curr;
			}
		}
		ht[del_index]->mobile = -1;
		ht[del_index]->name = "----";
		cout<<"Deleted!!\n";
	}
}

int main() {
	HT h;
	h.create();

	char ch = 'y';
	while(ch == 'y'){
		int cho;
		cout<<"\n1. Insert\n2. Search\n3. Update Name\n4. Display\n5. Delete\n";
		cout<<"Enter your choice: ";
		cin>>cho;
		if(cho == 1){
			int c;
			cout<<"\n1. Without Replacement\n2. With Replacement\n";
			cout<<"Choice: ";
			cin>>c;
			if(c == 1){
				cout<<"\n----WITHOUT REPLACEMENT----\n";
				int n;
				cout<<"Enter elements you wish to add in the Hash table: ";
				cin>>n;
				for(int i=0; i<n; i++){
					int no;
					string name;
					cout<<"Enter mobile number: ";
					cin>>no;
					cout<<"Enter name: ";
					cin>>name;
					h.insertWithout(no, name);
				}
				h.displayHT();
			} else if(c == 2) {
				cout<<"\n----WITH REPLACEMENT----\n";
				int n;
				cout<<"Enter elements you wish to add in the Hash table: ";
				cin>>n;
				for(int i=0; i<n; i++){
					int no;
					string name;
					cout<<"Enter mobile number: ";
					cin>>no;
					cout<<"Enter name: ";
					cin>>name;
					h.insertWith(no, name);
				}
				h.displayHT();
			} else {
				cout<<"Wrong Choice!\n";
			}
		} else if(cho == 2){
			int s;
			cout<<"\nEnter element to be searched: ";
			cin>>s;
			h.search(s);
		} else if(cho == 3){
			int keys;
			string newname;
			cout<<"Enter key and new name: \n";
			cout<<"Key: ";
			cin>>keys;
			cout<<"New name: ";
			cin>>newname;
			h.update(keys, newname);
		} else if(cho == 4){
			h.displayHT();
		} else if(cho == 5){
			cout<<"Enter element to be deleted: ";
			int del;
			cin>>del;
			h.delete_num(del);
		} else {
			cout<<"\nWrong choice!\n";
		}
		cout<<"\nDo you wish to continue?? (y/n):";
		cin>>ch;
	}


	return 0;
}