#include<iostream> 
#include <bits/stdc++.h>
using namespace std; 

char* convert_to_char(string s) {
     char *c = (char *)malloc(sizeof(char) * (s.length() + 1));
     strcpy(c,s.c_str());
     return c;
}

vector<string> strings;

/*** Utility functions ***/
void read_strings() {
	ifstream infile;
	infile.open("input.txt");
	string line;
	while(getline(infile,line)) {
		strings.push_back(line);
	}
}

void print_ar(char *out,int len) {
	ofstream myfile;
	myfile.open("output.txt");
	for(int i = 0;i < len;i++) {
		myfile << out[i];
	}
	myfile << "\n";
	myfile.close();
}
/*************************/

/* Finds and prints the LCS of X and Y */
void lcs( char *X, char *Y, int m, int n ) 
{ 
int L[m+1][n+1]; 

for (int i=0; i<=m; i++) 
{ 
	for (int j=0; j<=n; j++) 
	{ 
	if (i == 0 || j == 0) 
		L[i][j] = 0; 
	else if (X[i-1] == Y[j-1]) 
		L[i][j] = L[i-1][j-1] + 1; 
	else
		L[i][j] = max(L[i-1][j], L[i][j-1]); 
	} 
} 

int index = L[m][n]; 

char lcs[index+1]; 
lcs[index] = '\0';

// Keep following the trail of the maximum numbers at each cell
// this will lead us to the longest common subsequence
int i = m, j = n; 
while (i > 0 && j > 0) 
{ 
	if (X[i-1] == Y[j-1]) 
	{ 
		lcs[index-1] = X[i-1];
		i--; j--; index--;
	} 

	else if (L[i-1][j] > L[i][j-1]) 
		i--; 
	else
		j--; 
} 

cout << "LCS of " << X << " and " << Y << " is " << lcs << endl; 
print_ar(lcs,L[m][n]);
} 

int main() 
{ 
read_strings();
char *X = convert_to_char(strings[0]);
char *Y = convert_to_char(strings[1]);
int m = strlen(X); 
int n = strlen(Y); 
lcs(X, Y, m, n); 
return 0; 
} 

