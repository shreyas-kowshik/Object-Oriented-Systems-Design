#include <bits/stdc++.h>
#include <iostream>

typedef struct tuple {
     char subs; // character to substitute the tape element with
     char dir; // direction to move the tape in
     int next_state;
};

using namespace std;

int main() {
     ofstream myfile;
	myfile.open("output.txt");
	
     tuple delta[7][5]; // 7x5 array, 3 is the number of alphabets (a,b,c,X,Y,Z,B) where X,Y,Z are the tape alphabets, B is the empty alphabet and 5 is the number of states
     
     // Initialize delta with dummy values
     for(int i = 0;i < 7;i++) {
          for(int j = 0;j < 5;j++) {
               // assign default values for not storing anything
               tuple t;
               t.subs = '-';
               t.dir = '-';
               delta[i][j] = t;
          }
     }
     
     // Manually assign values to the transition function
     /******************************************/
     tuple t00;t00.subs = 'X';t00.dir = 'R';t00.next_state = 1;
     delta[0][0] = t00;
     
     tuple t40;t40.subs = 'Y';t40.dir = 'R';t40.next_state = 4;
     delta[4][0] = t40;
     
     tuple t01;t01.subs = 'a';t01.dir = 'R';t01.next_state = 1;
     delta[0][1] = t01;
     
     tuple t11;t11.subs = 'Y';t11.dir = 'R';t11.next_state = 2;
     delta[1][1] = t11;
     
     tuple t41;t41.subs = 'Y';t11.dir = 'R';t41.next_state = 1;
     delta[4][1] = t41;
     
     tuple t12;t12.subs = 'b';t11.dir = 'R';t12.next_state = 2;
     delta[1][2] = t12;
     
     tuple t22;t22.subs = 'Z';t22.dir = 'L';t22.next_state = 3;
     delta[2][2] = t22;
     
     tuple t52;t52.subs = 'Z';t52.dir = 'R';t52.next_state = 2;
     delta[5][2] = t52;
     
     tuple t03;t03.subs = 'a';t03.dir = 'L';t03.next_state = 3;
     delta[0][3] = t03;
     
     tuple t13;t13.subs = 'b';t13.dir = 'L';t13.next_state = 3;
     delta[1][3] = t13;
     
     tuple t33;t33.subs = 'X';t33.dir = 'R';t33.next_state = 0;
     delta[3][3] = t33;
     
     tuple t43;t43.subs = 'Y';t43.dir = 'L';t43.next_state = 3;
     delta[4][3] = t43;
     
     tuple t53;t53.subs = 'Z';t53.dir = 'L';t53.next_state = 3;
     delta[5][3] = t53;
     
     tuple t44;t44.subs = 'Y';t44.dir = 'R';t44.next_state = 4;
     delta[4][4] = t44;
     
     tuple t54;t54.subs = 'Z';t54.dir = 'R';t54.next_state = 4;
     delta[5][4] = t54;
     
     tuple t64;t64.subs = '$';t64.dir = 'L';t64.next_state = 5;
     delta[6][4] = t64;
     /******************************************/
     
     string str;
     cout << "Enter a binary string : ";
     getline(cin,str);
     
     int len = str.length();
     char tape[len + 2];
     
     tape[0] = '$';
     tape[len + 1] = '$';
     for(int i = 1;i <= len;i++) {
          tape[i] = str[i - 1];
     }
     
     int pointer = 1;
     int state = 0;
     
     while(true) {
          if(state == 5) break;
          int alphabet;
          if(tape[pointer] == 'a') alphabet = 0;
          else if(tape[pointer] == 'b') alphabet = 1;
          else if(tape[pointer] == 'c') alphabet = 2;
          else if(tape[pointer] == 'X') alphabet = 3;
          else if(tape[pointer] == 'Y') alphabet = 4;
          else if(tape[pointer] == 'Z') alphabet = 5;
          else alphabet = 6; // for '$'
          
          tuple transition_tuple = delta[alphabet][state];
          int next_state = transition_tuple.next_state;
          char subs = transition_tuple.subs;
          char dir = transition_tuple.dir;
          
          if(subs == '-') break; // no transition exists
          
          myfile << "-----------------------\n";
          myfile << "State : " << state << ":: Head : " << pointer << " :: Tape Contents : ";
          for(int i = 0;i < (len + 2);i++) {
               myfile << tape[i];
          }
          myfile << "\n";
          tape[pointer] = subs;
          if(dir == 'L') pointer -= 1;
          else pointer += 1;
          state = next_state;
     }
     
     if(state == 5) cout << "Accepted" << endl;
     else cout << "Rejected" << endl;
     return 0;
}
