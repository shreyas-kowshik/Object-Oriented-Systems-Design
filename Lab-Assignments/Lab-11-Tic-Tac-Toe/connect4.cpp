#include <bits/stdc++.h>
#include <iostream>

using namespace std;

char board[6][7];

int move(int player,int col) {
     for(int i = 0;i < 6;i++) {
          if(board[6 - i - 1][col] == '-') {
               if(player == 0) board[6 - i - 1][col] = 'x';
               else board[6 - i - 1][col] = 'o';
               
               return 6 - i - 1;
          }
     }
     
     cout << "Move not possible!\n";
     return -1;
}

void initBoard() {
     for(int i = 0;i < 6;i++)
          for(int j = 0;j < 7;j++)
               board[i][j] = '-';
}

void showBoard() {
     cout << "\n-------------\n";
     for(int i = 0;i < 6;i++) {
          for(int j = 0;j < 7;j++) {
               cout << board[i][j] << " | ";
          }
          cout << endl;
     }
     cout << "\n";
}

int checkBoard(int row,int col) {
    int i,ii;
    int ver = 0,hor = 0,d1 = 0,d2 = 0;
    int p = board[row][col];
    
     // vertical case checking
     for(i = row+1;i <= 5 && board[i][col] == p;i++,ver++);
     for(i = row-1;board[i][col] == p && i >= 0;i--,ver++);
     if(ver >= 3) {
          if(p == 'x') return 0;
          else return 1;
     }

     
     for(ii = col -1;board[row][ii] == p && ii >= 0;ii--,hor++);
	for(ii = col +1;board[row][ii] == p && ii <= 6;ii++,hor++);
	if(hor >= 3) {
          if(p == 'x') return 0;
          else return 1;
	}
	
	
     
	for(i = row -1, ii= col -1;board[i][ii] == p && i>=0 && ii >=0; d1 ++, i --, ii --);
	for(i = row +1, ii = col+1;board[i][ii] == p && i<=5 && ii <=6;d1 ++, i ++, ii ++);
	if(d1 >= 3) {
          if(p == 'x') return 0;
          else return 1;
	}
	
	
	for(i = row -1, ii= col +1;board[i][ii] == p && i>=0 && ii <= 6; d2 ++, i --, ii ++);
	for(i = row +1, ii= col -1;board[i][ii] == p && i<=5 && ii >=0; d2 ++, i ++, ii --);
	if(d2 >= 3) {
          if(p == 'x') return 0;
          else return 1;
	}
	
	return -1;
}

int main() {
     initBoard();
     
     int p = 0;
     int row,col;
     
     showBoard();
     
     while(true) {
          if(p == 0) cout << "Player 1 Enter column : ";
          else cout << "Player 2 Enter column : ";
          cin >> col;
          row = move(p,col);
          showBoard();
          int res = checkBoard(row,col);
          cout << "Res : " << res << endl;
          
          if(res == -1) {
               if(p == 0) p = 1;
               else p = 0;
               
               continue;
          }
          else {
               cout << "Player : " << res << " wins!\n";
               break;
          }
     }
}

