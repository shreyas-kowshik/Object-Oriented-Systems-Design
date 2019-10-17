#include <bits/stdc++.h>
using namespace std;

void computeLPSArray(string p,int m,int lps[]) {
     int len = 0,i = 1;
     lps[0] = 0;
     
		while (i < m) 
		{ 
			if (p[i] == p[len]) 
			{ 
				len++; 
				lps[i] = len; 
				i++; 
			} 
			else
			{ 
				if (len != 0) 
				{ 
					len = lps[len-1]; 
				} 
				else
				{ 
					lps[i] = len; 
					i++; 
				} 
			} 
		} 
}

int search(string t,string p) {
     int m = p.length();
     int n = t.length();
     
     int lps[m]; // to store longest proper prefix of p[0...i] which is also a proper suffix of p[0...i]
     int j = 0;
     
     computeLPSArray(p,m,lps); // obtain the lps
     
     int i = 0; // index for t[]
		int res = 0; 
		int next_i = 0; 
		
		vector<int> indices;
		
		while (i < n) 
		{ 
			if (p[j] == t[i]) 
			{ 
				j++; 
				i++; 
			} 
			if (j == m) 
			{ 
				j = lps[j-1]; 
				res++; 
				indices.push_back(i - m);

				if (lps[j]!=0) 
					i = ++next_i; // to account for overlapping sub-sequences
				j = 0; 
			} 
               
			else if (i < n && p[j] != t[i]) 
			{ 
				if (j != 0) 
					j = lps[j-1]; 
				else
					i = i+1; 
			} 
		} 
		for(int i = 0;i < indices.size();i++) 
		     cout << indices[i] << " ";
		cout << endl;
		return res; 
}

// AABAACAABAA
int main() {
     string text = "geeksforgeekseeksojdoafjoeeks";
     string pattern = "eeks";
     
     cout << search(text,pattern) << endl;
}
