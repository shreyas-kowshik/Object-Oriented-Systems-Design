#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <bits/stdc++.h>

using namespace std;

int len;
void read_line(char str[]) {
     string item_name;
     ifstream nameFileout;
     nameFileout.open("input.txt");
     string line;
     getline(nameFileout, line);
     for(int i = 0;i < line.size();i++) {
          str[i] = line[i];
     }
     len = line.size();
}

void write_line() {

}

int main()
{
     int i,j,k,turns,code[100][1000],col;
     
      
     char str[1000];
     read_line(str);
     
     for(int i = 0;i < len;i++) {
          cout << str[i];
     }
     cout << endl;
     printf("Enter diameter : ");
     cin >> turns;
     
     // initialize the values of the required indices to zero
     k=0;
     for(i=0;i<len;) // iterate over characters
     {
       for(j=0;j<turns;j++) // iterate over cells in a circle
       {
        code[k][j]=0; // code -> [num_circles,num_turns]
        i++;
       }
       k++;
      }
     
     k=0; // pointer to increase one row at a time
     //storing messages in code according to turns on band
     for(i=0;i<len;) // iterate over characters
     {
       if(str[i]!=' ') // if the character is not a space
       {
       for(j=0;j<turns;) 
       {
          if(i<len)
          {
               if(str[i]!=' ')//to avoid spaces in between words
               {
                      code[k][j]=(int)str[i];
                      i++;   
                      j++;  
               }
               else
               {
                      i++;
               }
     
          }
          else
          {
               break;
          }
       }
       k++;
       }
     else
     {
          i++;
     }
    }
    
     printf("The encrypted message is\n");
     //printing encrypted message which is column wise
     
     ofstream out("encrypt.txt");
     
     col=k;
     string output;
     for(i=0;i<turns;i++)
     {
      for(j=0;j<col;j++)
      { 
          if(code[j][i]!=0) {
               printf("%c",code[j][i]);
               output+=(char)code[j][i];
          }
      } 
     }
     out << output;
     out.close();
     printf("\n");
     return 0;
}
