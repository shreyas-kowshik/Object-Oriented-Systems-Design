// A C++ program to illustrate Caesar Cipher Technique 
#include <iostream>
#include <bits/stdc++.h> 
using namespace std; 

// Comparison function for sorting the set by increasing order of its pair's 
// second value. If second value are equal, order by the pair's first value
struct comp
{
	template<typename T>
	bool operator()(const T& l, const T& r) const
	{
		if (l.second != r.second)
			return l.second > r.second;

		return l.first > r.first;
	}
};

int key[26];
string input;
string sample;

vector<string> ug,bg,rg,ugi,bgi,rgi;

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

void add_to_map(map<string,int> &m,string s) {
     //cout << s << endl;
     map<string,int>::iterator it;
     it = m.find(s);
     if(it == m.end())
          m[s] = 1;
     else
          m[s] += 1;
     //cout << m[s] << endl;
}

void print_map(map<string,int> &m) {
     cout << "---Printing Map---\n";
     for(it : m)
     {
          cout << it.first << " " << it.second << "\n";
     }
}

void sort_print_map(map<string,int> &m) {
	set<pair<string,int>, comp> set(m.begin(), m.end());

     int i = 1;
	for (auto const &pair: set) {
	   if(i > 5) break;
	   cout << '{' << pair.first << "," << pair.second << '}' << '\n';
	   i++;
	}
}

void sort_print_map(map<string,int> &m,vector<string> &v) {
	set<pair<string,int>, comp> set(m.begin(), m.end());

     int i = 1;
	for (auto const &pair: set) {
	   if(i > 5) break;
	   cout << '{' << pair.first << "," << pair.second << '}' << '\n';
	   v.push_back(pair.first);
	   i++;
	}

}

// Driver program to test the above function 
int main() 
{ 
     read_keys();
     read_sample();
     // cout << input << endl;
     
     /* Computations for the sample text */
     map<string,int> uf; // unigram frequencies
     map<string,int> bf; // bigram frequencies
     map<string,int> rf; // repeat frequencies
     
     for(int i = 0;i < sample.length();i++) {
          if(((int)sample[i]) < 91 && ((int)sample[i]) >= 65) sample[i] = (char)(((int)sample[i]) + 32);
     }
     
     for(int i = 0;i < sample.length();i++) {
          if(sample[i] == ' ' || sample[i] == ',' || sample[i] == '-' || sample[i] == '.') continue;
          add_to_map(uf,getString(sample[i]));
     }
     
     // print_map(uf);
     
     for(int i = 0;i < sample.length() - 1;i++) {
          if(sample[i] == ' ' || sample[i] == ',' || sample[i] == '-' || sample[i] == '.') continue;
          if(sample[i+1] == ' ' || sample[i+1] == ',' || sample[i+1] == '-' || sample[i+1] == '.') continue;
          string bigram;
          bigram += sample[i];
          bigram += sample[i + 1];
          
          if(sample[i] == sample[i + 1])
               add_to_map(rf,bigram);
          else
               add_to_map(bf,bigram);
     }
     
     // print_map(bf);
     cout << "---Sample Statistics---" << endl;
     cout << "Top 5 unigrams" << endl;
     sort_print_map(uf,ug);
     cout << "Top 5 bigrams" << endl;
     sort_print_map(bf,bg);
     cout << "Top 5 repeats" << endl;
     sort_print_map(rf,rg);
     //print_map(rf);
     
     /* Computations for input text */
     map<string,int> ufi; // unigram frequencies
     map<string,int> bfi; // bigram frequencies
     map<string,int> rfi; // repeat frequencies
     
     for(int i = 0;i < input.length();i++) {
          if(input[i] == ' ' || input[i] == ',' || input[i] == '-' || input[i] == '.') continue;
          add_to_map(ufi,getString(input[i]));
     }
     
     // print_map(uf);
     
     for(int i = 0;i < input.length() - 1;i++) {
          if(input[i] == ' ' || input[i] == ',' || input[i] == '-' || input[i] == '.') continue;
          if(input[i+1] == ' ' || input[i+1] == ',' || input[i+1] == '-' || input[i+1] == '.') continue;
          string bigram;
          bigram += input[i];
          bigram += input[i + 1];
          
          if(input[i] == input[i + 1])
               add_to_map(rfi,bigram);
          else
               add_to_map(bfi,bigram);
     }
     
     // print_map(bf);
     cout << "---Input Statistics---" << endl;
     cout << "Top 5 unigrams" << endl;
     sort_print_map(ufi,ugi);
     cout << "Top 5 bigrams" << endl;
     sort_print_map(bfi,bgi);
     cout << "Top 5 repeats" << endl;
     sort_print_map(rfi,rgi);
     //print_map(rf);
     
     cout << "INPUT : " << input << endl;
     
     for(int i = 0;i < bgi.size();i++) {
          string curr_bg = bgi[i];
          string rep_bg = bg[i];
          for(int j = 0;j < input.length() - 1;j++) {
               if(input[j] == curr_bg[0] && input[j + 1] == curr_bg[1]) {
                    input[j] = rep_bg[0];
                    input[j+1] = rep_bg[1];
               }
          }
     }
     
     for(int i = 0;i < rgi.size();i++) {
          string curr_bg = rgi[i];
          string rep_bg = rg[i];
          for(int j = 0;j < input.length() - 1;j++) {
               if(input[j] == curr_bg[0] && input[j + 1] == curr_bg[1]) {
                    input[j] = rep_bg[0];
                    input[j+1] = rep_bg[1];
               }
          }
     }
     
     for(int i = 0;i < ugi.size();i++) {
          string s = ugi[i];
          char cstr[s.size() + 1];
	     strcpy(cstr, s.c_str());	// or pass &s[0]
          char curr_ug = cstr[0];
          
          s = ug[i];
          cstr[s.size() + 1];
	     strcpy(cstr, s.c_str());	// or pass &s[0]
          char rep_ug = cstr[0];
          
          for(int j = 0;j < input.length();j++) {
               if(input[j] == curr_ug) {
                    input[j] = rep_ug;
               }
          }
     }
     
     cout << "OUTPUT : " << input << endl;
	return 0;
} 

