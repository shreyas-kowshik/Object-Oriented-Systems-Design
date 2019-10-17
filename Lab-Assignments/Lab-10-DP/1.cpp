#include<bits/stdc++.h>  
using namespace std; 

vector<int> arr;
int counter;

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

void write_nos_to_file() {
        int RANGE = 100;
        int N = 1000;
        ofstream myfile;
        myfile.open("input.txt");
	   
        for(int i = 0;i < N;i++) {
                myfile << rand()%RANGE + 1 << " ";
        }
        myfile << "\n";
        myfile.close();
}

void printLIS(vector<int>& arr) 
{ 
    for (int x : arr) 
        cout << x << " "; 
    cout << endl; 
} 

void print_ar(vector<int>& arr) {
	ofstream myfile;
	myfile.open("output.txt");
	for(int i = 0;i < arr.size();i++) {
		myfile << arr[i] << " ";
	}
	myfile << "\n";
	myfile.close();
}

void LIS() 
{ 
    int n = arr.size();
    vector<vector<int> > L(n); // L[i] stores LIS until index i
    
    L[0].push_back(arr[0]); // L[0] = arr[0]
    
    for (int i = 1; i < n; i++) // loop to find L[i]
    { 
        for (int j = 0; j < i; j++) // loop over previous elements
        { 
            /* L[i] = {Max(L[j])} + arr[i] 
            where j < i and arr[j] < arr[i] */
            counter += 1;
            if ((arr[i] > arr[j]) && 
                    (L[i].size() < L[j].size() + 1)) 
                L[i] = L[j]; // allocate elements until j to i
        }
        L[i].push_back(arr[i]); // add arr[i] to store the LIS
    } 
    
    // Find longest among all indices
    vector<int> max = L[0]; 

    for (int i = 0;i < L.size();i++) 
        if (L[i].size() > max.size()) 
            max = L[i]; 
    
    printLIS(max); 
    print_ar(max);
    cout  << counter << endl;
}

// Driver function 
int main() 
{ 
    write_nos_to_file();
    read_nos();
    LIS(); 
  
    return 0; 
}
