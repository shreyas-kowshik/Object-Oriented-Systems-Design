#include <bits/stdc++.h>
#include <iostream>

using namespace std;

char board[6][7];
int air,aic;
int len[7];

int move(int player,int col) {
     for(int i = 0;i < 6;i++) {
          if(board[6 - i - 1][col] == '-') {
               if(player == 0) board[6 - i - 1][col] = 'x';
               else board[6 - i - 1][col] = 'o';
               
               len[col]++;
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

void aiMove() {
     int i,ii;
     int j;
     
     // scan all rows horizontally
     for(i = 0;i < 6;i++) {
          int hor = 0;
          for(j = 0;j < 7;j++)
               if(board[i][j] == 'x') hor++;
          
          if(hor >= 3) {
               for(j = 0;j < 7;j++) {
                    if(len[j] == 6 - i - 1)  {
                         air = move(1,j);
                         if(air == -1) {
                              continue;
                         }
                         aic = j;
                         return;
                    }
               }
          }
     }
     
     // scan all columns vertically
     for(i = 0;i < 7;i++) {
          int ver = 0;
          for(j = 0;j < 6;j++)
               if(board[j][i] == 'x') ver++;
          
          if(ver >= 3) {
               air = move(1,i);
               if(air == -1) {
                    if(i == 6) break;
                    else continue;
               }
               aic = i;
               return;
          }
     }
     
     // scan d1
     int d = 0;
     for(int t = 0;t <= 11;t++) {
          d = 0;
          for(i = 0;i < 6;i++) 
               for(j = 0;j < 7;j++) 
                    if(i+j==t && board[i][j] == 'x') d++;
          if(d >= 3) {
               for(i = 0;i < 6;i++) 
                    for(j = 0;j < 7;j++) 
                         if(i+j==t && board[i][j] == '-') {
                              air = move(1,j);
                              aic = j;
                              return;
                         }
          }          
     }
     
     int min = 1000000;
     int cl = -1;
     for(int i = 0;i < 7;i++) {
          if(len[i] < min) {
               min = len[i];
               cl = i;
          }
     }
     
     aic = cl;
     air = move(1,cl);
}

int main() {
     initBoard();
     for(int i = 0;i < 7;i++) len[i] = 0;
     int numMoves = 0;
     
     int p = 0;
     int row,col,mv = 0;
     row = -1;
     
     showBoard();
     
     while(true) {
          if(numMoves == 6*7) {
               cout << "Draw!" << endl;
               break;
          }
          
          mv = 0;
          if(p == 0) { 
              // while(row == -1) {
                    cout << "Player 1 Enter column : ";
                    cin >> col;
                    row = move(p,col);
              // }
          }
          else {
               cout << "AI making move...\n";
               aiMove();
               row = air;
               col = aic;
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

