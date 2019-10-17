// A C++ program to illustrate Caesar Cipher Technique 
#include <iostream>
#include <bits/stdc++.h> 
using namespace std; 


int key[26];

void read_keys() {
     ifstream nameFileout;
     nameFileout.open("key.txt");
     string line;
     while(getline(nameFileout, line)) {
          char s = line[0];
          char d = line[2];
          key[int(s) - 97] = int(d) - 97;
     }
}

string encrypt(string text, int s) 
{ 
	string result = ""; 

	for (int i=0;i<text.length();i++) 
	{
	     if(text[i] == ' ' || text[i] == ',' || text[i] == '.') {
	          continue;
	     }
	     
          if (isupper(text[i])) 
			text[i] = text[i] + 32; 
	     
	     int cur_char = text[i] - 97;
	     if(key[cur_char] != -1)
		     result += char(key[cur_char] + 97);
		else
		     result += text[i];
	} 

	return result; 
} 

// Driver program to test the above function 
int main() 
{ 
     for(int i = 0;i < 26;i++)
          key[i] = -1;
     read_keys();
     
	string text="To pass an encrypted message from one person to another, it is first necessary that both parties have the  for the cipher, so that the sender may encrypt it and the receiver may decrypt it For the caesar cipher the key is the number of characters to shift the cipher alphabet"; 
	int s = 23; 
	cout << "String : " << text << endl;
	string enc = encrypt(text, s);
	cout << "Caesar Cipher: " << enc << endl;
	ofstream out("output.txt");
	out << enc;
	out.close();
	
	return 0;
} 

