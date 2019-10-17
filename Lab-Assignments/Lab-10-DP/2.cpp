#include <bits/stdc++.h> 
using namespace std; 

vector<int> arr;
int counter = 0;

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
        int RANGE = 1000;
        int N = 100;
        ofstream myfile;
        myfile.open("input.txt");
	   
        for(int i = 0;i < N;i++) {
                myfile << rand()%RANGE + 1 << " ";
        }
        myfile << "\n";
        myfile.close();
}

int GetCeilIndex(vector<int>& T, int l, int r, 
                 int key) 
{ 
    while (r - l > 1) { 
        counter += 1;
        int m = l + (r - l) / 2; 
        if (arr[T[m]] >= key) 
            r = m; 
        else
            l = m; 
    } 
  
    return r; 
} 

void LongestIncreasingSubsequence() 
{
    int n = arr.size();
    vector<int> tailIndices(n, 0); // Initialized with 0 , stores end element of all the active sequences
    vector<int> prevIndices(n, -1); // initialized with -1 , stores previous index values for given sequence
   
    int len = 1; // it will always point to empty location
    for (int i = 1; i < n; i++) { 
        counter += 1;
        if (arr[i] < arr[tailIndices[0]]) { 
            // new smallest value 
            tailIndices[0] = i; 
        } 
        else if (arr[i] > arr[tailIndices[len - 1]]) { 
            // arr[i] wants to extend largest subsequence 
            prevIndices[i] = tailIndices[len - 1]; 
            tailIndices[len++] = i; 
        } 
        else { 
            // arr[i] wants to be a potential condidate of 
            // future subsequence 
            // It will replace ceil value in tailIndices 
            
            // find largest end element that is smaller than arr[i]
            int pos = GetCeilIndex(tailIndices, -1, 
                                   len - 1, arr[i]); 
            
            prevIndices[i] = tailIndices[pos - 1]; 
            tailIndices[pos] = i; 
        } 
    } 
    
    cout << "LIS of given input" << endl; 
    
    vector<int> out;
    for (int i = tailIndices[len - 1]; i >= 0; i = prevIndices[i]) // follow the indices back using previous indices
          out.push_back(arr[i]);
    for(int i = out.size()-1;i >= 0;i--)
         cout << out[i] << " ";
    cout << endl; 
}

int main()
{ 
    write_nos_to_file();
    read_nos();
    
    //int arr[] = { 2, 5, 3, 7, 11, 8, 10, 13, 6 }; 
    //int n = sizeof(arr) / sizeof(arr[0]); 

    LongestIncreasingSubsequence();
    cout << counter << endl;
    
    return 0; 
}

