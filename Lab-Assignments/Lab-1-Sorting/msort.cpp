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

// Sorting functions defined
void merge(vector<int>& arr,vector<int>& tem,int p,int q,int r) {
	/*
	There are two partitions of the given subarray
	p ... q & q+1 ... r
	
	We merge the two subarrays into a single array
	*/
	int i = p,j = q+1; 
	
	// Fill in values in the temporary array
	for(int t = 0;t < arr.size();t++) {
		tem[t] = arr[t];
	}

	int k;
	
	for(k = p;k <=r;k++) {
		if(i > q && j <= r) {
			arr[k] = tem[j];
			j++;
			continue;
		}
		else if(i <= q && j > r) {
			arr[k] = tem[i];
			i++;
			continue;
		}
			
		if(tem[i] < tem[j]) {
			arr[k] = tem[i];
			i++;
		}
		else {
			arr[k] = tem[j];
			j++;
		}
	}
}

void mergesort(vector<int>& arr,vector<int>& tem,int l,int h) {
	if(l >= h)
		return;
	int m = (l + h)/2;
	mergesort(arr,tem,l,m);
	mergesort(arr,tem,m+1,h);
	merge(arr,tem,l,m,h);
}

int main() {
	// Read input from files
	read_nos();
	for(int i = 0;i < arr.size();i++) {
		tem.push_back(arr[i]);
	}
	
	cout << "---Before---" << endl;
	print_array(arr);
	
	mergesort(arr,tem,0,arr.size()-1);
	
	cout << "---After---" << endl;
	print_array(arr);
	
	// Save to file
	print_ar(arr);
}
