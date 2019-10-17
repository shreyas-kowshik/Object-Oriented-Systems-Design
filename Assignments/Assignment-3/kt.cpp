#include <bits/stdc++.h>

using namespace std;
int N;
int sx,sy;
int movei[4] = {-1,-2,1,2};
int movej[4] = {-1,-2,1,2};

bool isDigit(int n) {
        if(n == 0 || n == 1 || n == 2 || n == 3 || n == 4 || n == 5 || n == 6 || n == 7 || n == 8 || n == 9)
                return true;
        return false;
}

void print_board(int **board) {
	for(int i = 0;i < N;i++) {
		for(int j = 0;j < N;j++) {
			if(isDigit(board[i][j]))
				cout << board[i][j] << "  ";
			else
				cout << board[i][j] << " ";
		}
		cout << endl;
	}
}

bool checkValid(int **board,int i,int j) {
	if(i >= 0 && i < N && j >= 0 && j < N)
		if(board[i][j] == -1)
			return true;
	return false;
}

bool checkBound(int **board,int i,int j) {
	if(i >= 0 && i < N && j >= 0 && j < N)
		return true;
	return false;
}

bool isNeighbor(int **board,int i,int j) {
	for(int ti = 0;ti < 4;ti++) {
		for(int tj = 0;tj < 4;tj++) {
			if(abs(movei[ti]) == abs(movej[tj])) continue;
			int nexti = sx + movei[ti];
			int nextj = sy + movej[tj];
			if(!checkBound(board,nexti,nextj)) continue;
			
			if(i == nexti && j == nextj) return true;
		}
	}
	return false;
}

bool solve(int **board,int i,int j,int move) {
	if(move == N*N)  {
		// if(!isNeighbor(board,i,j)) return false;
		return true;
	}

	for(int ti = 0;ti < 4;ti++) {
		for(int tj = 0;tj < 4;tj++) {
			if(abs(movei[ti]) == abs(movej[tj])) continue;
			int nexti = i + movei[ti];
			int nextj = j + movej[tj];
			if(!checkValid(board,nexti,nextj)) continue;
				
			board[nexti][nextj] = move;
			if(solve(board,nexti,nextj,move + 1)) return true;
			board[nexti][nextj] = -1;
		} 
	}

	return false;
}

int main() {
	cin >> N;
	int **board = (int **)malloc(N * sizeof(int *));
	for(int i = 0;i < N;i++)
		board[i] = (int *)malloc(N * sizeof(int));

	for(int i = 0;i < N;i++) 
		for(int j = 0;j < N;j++)
			board[i][j] = -1;

	srand(time(NULL));
	sx = 0;
    	sy = 0;	
	print_board(board);
	board[sx][sy] = 0;
	solve(board,0,0,1);
	print_board(board);
}
