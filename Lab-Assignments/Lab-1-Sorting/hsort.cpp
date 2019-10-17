#include <bits/stdc++.h>

using namespace std;

vector<int> arr;
vector<int> tem;

/*** Utility functions ***/
void read_nos() {
	//Opens a file and reads the numbers to the vector
	int x;
	ifstream infile;
	infile.open("input.txt");
	while(infile >> x) {
		if(x == EOF) break;
		arr.push_back(x);
	}
}

void print_array(vector<int>& a) {
	for(int i = 0;i < a.size();i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}

void print_ar(vector<int>& a) {
	ofstream myfile;
	myfile.open("output.txt");
	for(int i = 0;i < arr.size();i++) {
		myfile << arr[i] << " ";
	}
	myfile << "\n";
	myfile.close();
}

void swap(int *a,int *b) {
	int t = *a;
	*a = *b;
	*b = t;
}
/***********************/

void max_heapify(vector<int>& arr,int i,int size) {
	// We explicitly convert all indices to a 1-indexed version and work with that
	int l = 2*i;
	int r = 2*i + 1;
	
	int largest;
	
	if(l <= size && arr[l-1] > arr[i-1])
		largest = l;
	else
		largest = i;
	
	if(r <= size && arr[r-1] > arr[largest -1]) 
		largest = r;
	
	if(largest != i) {
		swap(&arr[i-1],&arr[largest-1]);
		max_heapify(arr,largest,size);
	}
}

void build_max_heap(vector<int>& arr,int size) {
	for(int i = size/2;i >= 1;i--) {
		max_heapify(arr,i,size);
	}
}

void heap_sort(vector<int>& arr) {
	build_max_heap(arr,arr.size());
	int size = arr.size();
	for(int i = arr.size();i >= 2;i--) {
		swap(&arr[0],&arr[i - 1]);
		size = size - 1;
		max_heapify(arr,1,size);
	}
}

int main() {
	// Read from file
	read_nos();
	cout << "---Printing Max Heap---" << endl;
	print_array(arr);
	heap_sort(arr);
	
	cout << "---Printing Sorted Array---" << endl;
	print_array(arr);
	
	// Save to file
	print_ar(arr);
}

