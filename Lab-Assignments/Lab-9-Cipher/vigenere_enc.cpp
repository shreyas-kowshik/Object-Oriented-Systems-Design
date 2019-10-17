// A C++ program to illustrate Caesar Cipher Technique 
#include <iostream>
#include <bits/stdc++.h> 
#include <string.h>
using namespace std; 

string input;
string key;

void read_input() {
     ifstream nameFileout;
     nameFileout.open("input.txt");
     getline(nameFileout, input);
}

void readkey() {
     ifstream nameFileout;
     nameFileout.open("key.txt");
     getline(nameFileout, key);
}

int main() {
     read_input();
     readkey();
     cout << input << endl << key << endl;
     string out;
     for(int i = 0;i < input.length();i++) {
          int inp_char = input[i] - 97;
          int key_char = key[i%key.length()] - 97;
          int out_char = (inp_char + key_char)%26;
          out += (char)(out_char + 97);
     }
     cout << out << endl;
     return 0;
}
