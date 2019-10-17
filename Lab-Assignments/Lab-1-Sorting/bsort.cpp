#include <bits/stdc++.h>

using namespace std;

vector<int> arr;

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
/******************************/

void bsort(vector<int>& a) {
	int swaps = 0;
	
	while(1) {
		swaps = 0;
		for(int i = 1;i < a.size();i++) {
			if(a[i-1] > a[i]) {
				swap(&a[i-1],&a[i]);
				swaps+=1;
			}
		}

		if(swaps == 0)
			break;
	}
}

int main() {
	// Read input from files
	read_nos();
	cout << "---Before---" << endl;
	print_array(arr);
	
	bsort(arr);
	
	cout << "---After---" << endl;
	print_array(arr);
	
	// Save to file
	print_ar(arr);
}

