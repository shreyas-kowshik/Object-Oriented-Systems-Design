#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <bits/stdc++.h>

using namespace std;

int len;
string input;

void read_line(char str[]) {
     string item_name;
     ifstream nameFileout;
     nameFileout.open("encrypt.txt");
     string line;
     getline(nameFileout, input);
     len = input.size();
}

void write_line() {

}

int main()
{
     int i,j,k,turns,code[100][1000],col;
     
      
     char str[1000];
     read_line(str);
     cout << input << endl;
     cout << len << endl;
     
     int d = 1;

     for(int d = 1;d <= 10;d++) {
          int step = len/d + 1;
          cout << "d = " << d - 1 << endl;
          for(int i = 0;i < step;i++) {
               for(int j = 0;j < d;j++) {
                    int index = i + step*j;
                    if (index > len) break;
                    cout << input[index];
               }
          }
          cout << endl;
     }
     return 0;
}
