#include <bits/stdc++.h>
#include <iostream>

using namespace std;

int main() {
     string str;
     cout << "Enter a binary string : ";
     getline(cin,str);
     
     int len = str.length();
     int n_pointer;
     int s_pointer;
     
     for(int n = 2;n < len;i++) {
          n_pointer = 0;
          s_pointer = 0;
          for(int i = 0;i < len;i++) {
               s_pointer += 1;
               n_pointer += 1;
          }
     }
     
     return 0;
}
