#include <iostream>
using namespace std;

void swap(int *a,int *b){
	int temp=*a;
	*a=*b;
	*b=temp;
}

class HeapSort{
public:
	void heapify(int arr[],int n,int i){
		int largest=i;
		int l=2*i+1;
		int r=2*i+2;
		if (l<n && arr[l]>arr[largest]){
			largest=l;
		}
		if (r<n && arr[r]>arr[largest]){
			largest=r;
		}
		if (largest!=i){
			swap(&arr[largest],&arr[i]);
			heapify(arr,n,largest);
		}
	}

	void heapsort(int arr[],int n,int i){
		for (int i=n/2-1;i>=0;i--){
			heapify(arr,n,i);
		}

		for (int i=n-1;i>=0;i--){
			swap(&arr[0],&arr[i]);
			cout<<"Iteration "<<n-i<<": ";
			display(arr,n);
			heapify(arr,i,0);
		}
	}

	void display(int arr1[],int n){
		for (int i=0;i<n;i++){
			cout<<arr1[i]<<" ";
		}
		cout<<endl;
	}
};

int main(){
	HeapSort h1;
	int n;
	cout<<"Enter number of elements in the array: "<<endl;
	cin>>n;
	int *arr2=new int[n];
	for (int i=0;i<n;i++){
		cout<<"Enter element: "<<endl;
		cin>>arr2[i];
	}
	//int arr2[6]={2,8,5,3,9,1};
	//n=6;
	cout<<"Before sorting: "<<endl;
	h1.display(arr2,n);
	h1.heapsort(arr2,n,0);
	cout<<"After Sorting: "<<endl;
	h1.display(arr2,n);
	delete[] arr2;
	return 0;

}