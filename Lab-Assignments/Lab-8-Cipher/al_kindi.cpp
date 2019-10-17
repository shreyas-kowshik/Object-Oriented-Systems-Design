// A C++ program to illustrate Caesar Cipher Technique 
#include <iostream>
#include <bits/stdc++.h> 
using namespace std; 


int key[26];
string input;
string sample;

void read_keys() {
     ifstream nameFileout;
     nameFileout.open("output.txt");
     getline(nameFileout, input);
}

void read_sample() {
     ifstream nameFileout;
     nameFileout.open("sample.txt");
     getline(nameFileout, sample);
}

string getString(char x) 
{ 
    string s(1, x);
    return s;
}

bool checkInVec(string s,vector<string> v) {
     for(int i = 0;i < v.size();i++) {
          if(v[i] == s) return true;
     }
     return false;
}

// Driver program to test the above function 
int main() 
{ 
     read_keys();
     read_sample();
     cout << input << endl;
     
     vector<int> space_indices;
     for(int i = 0;i < sample.length();i++) {
          if(sample[i] == ' ') {
               space_indices.push_back(i);
          }
     }
     vector<int> unigram_indices;
     vector<int> bigram_indices;
     
     for(int i = 0;i < space_indices.size() - 1;i++) {
          if((space_indices[i+1] - space_indices[i]) == 2) {
               unigram_indices.push_back(i+1);
          }
          else if((space_indices[i+1] - space_indices[i]) == 3) {
               bigram_indices.push_back(i+1);
          }
     }
     
     vector<string> bigrams;
     vector<string> unigrams;
     for(int i = 0;i < unigram_indices.size();i++) {
          unigrams.push_back(getString(sample[unigram_indices[i]]));
     }
     for(int i = 0;i < bigram_indices.size();i++) {
          string b;
          if(sample[bigram_indices[i]] == ' ' || sample[bigram_indices[i+1]] == ' ') continue;
          b += sample[bigram_indices[i]];
          b += sample[bigram_indices[i+1]];
          bigrams.push_back(b);
     }
     
     map<string,int> uf;
     map<string,int> bf;
     for(int i = 0;i < bigrams.size();i++) {
          map<string,int>::iterator it;
          it = bf.find(bigrams[i]);
          if(it == bf.end())
               bf[bigrams[i]] = 1;
          else
               bf[bigrams[i]]+=1;
     }
     for(int i = 0;i < unigrams.size();i++) {
          map<string,int>::iterator it;
          it = uf.find(unigrams[i]);
          if(it == uf.end())
               uf[unigrams[i]] = 1;
          else
               uf[unigrams[i]]+=1;
     }
     
     cout << "Unigram Frequencies Sample : " << endl;
     for(it : uf)
     {
          cout << it.first << " " << it.second << "\n";
     }
     cout << "Bigram Frequencies Sample : " << endl;
     for(it : bf)
     {
          cout << it.first << " " << it.second << "\n";
     }
     
     map<string,int> iuf;
     map<string,int> ibf;
     for(int i = 0;i < input.length();i++) {
          map<string,int>::iterator it;
          it = iuf.find(getString(input[i]));
          if(it == iuf.end())
               iuf[getString(input[i])] = 1;
          else
               iuf[getString(input[i])]+=1;
     }
     cout << "Unigram Frequencies Enc : " << endl;
     for(it : iuf) {
          cout << it.first << " " << it.second << endl;
     }
     
     for(int i = 0;i < input.length();i++) {
          for(int j = i+1;j < input.length();j++) {
               map<string,int>::iterator it;
               string b;
               b += input[i];
               b += input[j];
               it = ibf.find(b);
               if(it == ibf.end())
                    ibf[b] = 1;
               else
                    ibf[b]+=1;
          }
     }
     cout << "Bigram Frequencies Enc : " << endl;
     for(it : ibf) {
          cout << it.first << " " << it.second << endl;
     }
     
	return 0;
} 

