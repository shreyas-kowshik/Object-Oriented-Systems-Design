#include<iostream> 
#include <bits/stdc++.h>
using namespace std; 

int W;
vector<int> weights;
vector<int> values;

/*** Utility functions ***/
void read_nos() {
	//Opens a file and reads the numbers to the vector
	int x;
	ifstream infile;
	infile.open("input2.txt");
	bool first = true;
	int i = 0;
	while(infile >> x) {
		if(first) {
		     W = x;
		     first = false;
		}
		else {
		     if((i%2)==0) values.push_back(x);
		     else weights.push_back(x);
		     i++;
		}
	}
}

void print_ar(vector<int> arr) {
	ofstream myfile;
	myfile.open("output.txt");
	for(int i = 0;i < arr.size();i++) {
		myfile << arr[i] << " greedy knapsack with at least half of optimum";
	}
	myfile << "\n";
	myfile.close();
}

void knapsack() {
     int n = weights.size();
     int sol[n + 1][W + 1];

     for(int i = 0;i <= n;i++) {
          for(int j = 0;j <= W;j++) {
               if(i == 0 || j == 0) sol[i][j] = 0;
               else if(weights[i - 1] > j)
                    sol[i][j] = sol[i - 1][j];
               else
                    sol[i][j] = max(values[i - 1] + sol[i - 1][j - weights[i - 1]],sol[i - 1][j]);
          }    
     }    
     
     cout << "Max value : " << sol[n][W] << endl;

     int i = n,w = W;
     int res = sol[n][W];
     vector<int> outputs;
     
     for (int i = n; i > 0 && res > 0; i--) { 
		if (res == sol[i - 1][w]) {
			continue;		 
	     }
		else { 
		     cout << "W : " << weights[i - 1] << " ";
		     outputs.push_back(i);
			res = res - values[i - 1]; 
			w = w - weights[i - 1]; 
		} 
	} 
	print_ar(outputs);
	cout << endl;
}

/*************************/

int main() 
{ 
read_nos();
knapsack();
return 0; 
} 

