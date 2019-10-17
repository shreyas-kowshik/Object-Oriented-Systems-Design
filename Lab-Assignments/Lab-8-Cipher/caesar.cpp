// A C++ program to illustrate Caesar Cipher Technique 
#include <iostream>
#include <bits/stdc++.h> 
using namespace std; 

// This function receives text and shift and 
// returns the encrypted text 
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
	     
		result += char(int(text[i]+s-97)%26 +97); 
	} 

	return result; 
} 

// Driver program to test the above function 
int main() 
{ 
	string text="The quick brown fox jumps over the lazy dog"; 
	int s = 23; 
	cout << "String : " << text << endl;
	string enc = encrypt(text, s);
	cout << "Caesar Cipher: " << enc << endl;
	ofstream out("encrypt.txt");
	out << enc;
	out.close();
	
	// decrypt
	for(int s = 0;s < 26;s++) {
	     string dec;
	     cout << "s : " << s << endl;
	     for(int i = 0;i < enc.length();i++) {
	          int index = enc[i] - 97 - s;
	          if(index < 0) index += 26;
	          dec += char(int((index)%26 + 97));
	     }
	     cout << dec << endl;
	}
	
	return 0;
} 

