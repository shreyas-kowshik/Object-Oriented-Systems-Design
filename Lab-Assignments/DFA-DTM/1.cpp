#include <bits/stdc++.h>
#include <iostream>

using namespace std;
     
int main() {
     ofstream myfile;
	myfile.open("output.txt");
	
     string str;
     cout << "Enter a binary string : ";
     getline(cin,str);
     
     cout << "Input string : ";
     cout << str << endl;
     
     // Delta - 2 x 7 array, representing for each state, the input alphabet and the corresponding output state
     int delta[2][7] = {{0,2,4,6,1,3,5},{1,3,5,0,2,4,6}};
     
     int state = 0;
     for(int i = 0;i < str.length();i++) {
          int alphabet;
          cout << "----------------------" << endl;
          myfile << "-------------------\n";
          myfile << "Current state : " << state << "\n";
          cout << "Current state : " << state << endl;
          if(str[i] == '0') alphabet = 0;
          else alphabet = 1;
          cout << "Currently read alphabet : " << alphabet << endl;
          myfile << "Currently read alphabet : " << alphabet << "\n";
          cout << "String left to read : ";
          myfile << "String left to read : ";
          for(int k = i + 1;k < str.length();k++) {
               cout << str[k];
               myfile << str[k] << " ";
          }
          myfile << "\n";
          int next_state = delta[alphabet][state];
          state = next_state;
     }
     
     cout << endl;
     cout << "Remainder : " << state << endl;
     myfile.close();
}
