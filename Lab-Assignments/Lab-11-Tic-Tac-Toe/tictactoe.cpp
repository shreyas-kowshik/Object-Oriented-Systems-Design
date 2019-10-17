#include <bits/stdc++.h>
#include <iostream>

using namespace std;

char board[3][3];
int air,aic;

int move(int player,int row,int col) {
     if(board[row][col] == '-') {
          if(player == 0) board[row][col] = 'x';
          else board[row][col] = 'o';
          return 1;
     }
     else cout << "Move not possible!\n";
     
     return 0;
}

void initBoard() {
     for(int i = 0;i < 3;i++)
          for(int j = 0;j < 3;j++)
               board[i][j] = '-';
}

void showBoard() {
     cout << "\n-------------\n";
     for(int i = 0;i < 3;i++) {
          for(int j = 0;j < 3;j++) {
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
     for(i = row+1;i <= 2 && board[i][col] == p;i++,ver++);
     for(i = row-1;board[i][col] == p && i >= 0;i--,ver++);
     if(ver >= 2) {
          if(p == 'x') return 0;
          else return 1;
     }

     
     for(ii = col -1;board[row][ii] == p && ii >= 0;ii--,hor++);
	for(ii = col +1;board[row][ii] == p && ii <= 2;ii++,hor++);
	if(hor >= 2) {
          if(p == 'x') return 0;
          else return 1;
	}
	
	
     
	for(i = row -1, ii= col -1;board[i][ii] == p && i>=0 && ii >=0; d1 ++, i --, ii --);
	for(i = row +1, ii = col+1;board[i][ii] == p && i<=2 && ii <=2;d1 ++, i ++, ii ++);
	if(d1 >= 2) {
          if(p == 'x') return 0;
          else return 1;
	}
	
	
	for(i = row -1, ii= col +1;board[i][ii] == p && i>=0 && ii <= 2; d2 ++, i --, ii ++);
	for(i = row +1, ii= col -1;board[i][ii] == p && i<=2 && ii >=0; d2 ++, i ++, ii --);
	if(d2 >= 2) {
          if(p == 'x') return 0;
          else return 1;
	}
	
	return -1;
}

void aiMove() {
     int i,ii;
     int j;
     
     // scan all rows horizontally
     for(i = 0;i < 3;i++) {
          int hor = 0;
          for(j = 0;j < 3;j++)
               if(board[i][j] == 'x') hor++;
          
          if(hor >= 2) {
               for(j = 0;j < 3;j++) {
                    if(board[i][j] == '-') {
                         move(1,i,j);
                         air = i;
                         aic = j;
                         return;    
                    }
               }
          }
     }

     // scan all columns vertically
     for(i = 0;i < 3;i++) {
          int ver = 0;
          for(j = 0;j < 3;j++)
               if(board[j][i] == 'x') ver++;
          
          if(ver >= 2) {
               for(j = 0;j < 3;j++) {
                    if(board[j][i] == '-') {
                         move(1,j,i);
                         air = j;
                         aic = i;
                         return;
                    }
               }
          }
     }
     
     // scan d1
     int d = 0;
     for(i = 0;i < 3;i++)
          for(j = 0;j < 3;j++)
               if(i == j && board[i][j] == 'x') d++;
     if(d >= 2) {
          for(i = 0;i < 3;i++)
               for(j = 0;j < 3;j++)
                    if(i == j && board[i][j] == '-') {
                         move(1,i,j);
                         air = i;
                         aic = j;
                         return;
                    }
     }
     
     // scan d2
     d = 0;
     for(i = 2;i >= 0;i--)
          for(j = 0;j < 3;j++)
               if(i+j == 2 && board[i][j] == 'x') d++;
     if(d >= 2) {
          for(i = 2;i >= 0;i--)
               for(j = 0;j < 3;j++)
                    if(i+j==2 && board[i][j] == '-') {
                         move(1,i,j);
                         air = i;
                         aic = j;
                         return;
                    }
     }
     
     // if none of above work
     if(board[1][1] == '-') {
          board[1][1] = 'o';
          air = 1;
          aic = 1;
          return;
     }
     else {
          for(int i = 0;i < 3;i++)
               for(int j = 0;j < 3;j++) {
                    if(i == j && board[i][j] == '-') {
                         move(1,i,j);
                         air = i;
                         aic = j;
                         return;
                    }
               }
          for(int i = 2;i >= 0;i--)
               for(int j = 0;j < 3;j++) {
                    if(i+j==2 && board[i][j] == '-') {
                         move(1,i,j);
                         air = i;
                         aic = j;
                         return;
                    }
               }
          for(int i = 0;i < 3;i++)
               for(int j = 0;j < 3;j++) {
                    if(board[i][j] == '-') {
                         move(1,i,j);
                         air = i;
                         aic = j;
                         return;
                    }
               }
     }
}

int main() {
     initBoard();
     int numMoves = 0;
     
     int p = 0;
     int row,col,mv = 0;
     
     showBoard();
     
     while(true) {
          if(numMoves == 9) {
               cout << "Draw!" << endl;
               break;
          }
          
          mv = 0;
          while(mv != 1) {
          if(p == 0) { 
               cout << "Player 1 Enter column : ";
               cin >> col;
               cout << "Player 1 Enter row : ";
               cin >> row;
               mv = move(p,row,col);
          }
          else {
               cout << "AI making move...\n";
               aiMove();
               row = air;
               col = aic;
               mv = 1;
          }
          }
          
          showBoard();
          int res = checkBoard(row,col);
          
          numMoves++;
          
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

