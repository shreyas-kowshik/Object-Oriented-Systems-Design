#include <bits/stdc++.h>

using namespace std;
#define N 10

// int N;
int sx,sy;
int movei[4] = {-1,-2,1,2};
int movej[4] = {-1,-2,1,2};
bool isDigit(int n) {
        if(n == 0 || n == 1 || n == 2 || n == 3 || n == 4 || n == 5 || n == 6 || n == 7 || n == 8 || n == 9)
                return true;
        return false;
}

void print_board(int board[N][N]) {
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

// TEMPORARY
int count_zeros(int board[N][N]) {
	int count = 0;
	for(int i = 0;i < N;i++)
		for(int j = 0;j < N;j++)
			if(board[i][j] == -1) count++;

	return count;
}

bool checkValid(int board[N][N],int i,int j) {
	if(i >= 0 && i < N && j >= 0 && j < N)
		if(board[i][j] == -1)
			return true;
	return false;
}

bool checkBounds(int board[N][N],int i,int j) {
	if(i >= 0 && i < N && j >= 0 && j < N)
		return true;
	return false;
}

bool isNeighbor(int board[N][N],int i,int j) {
        for(int ti = 0;ti < 4;ti++) {
                for(int tj = 0;tj < 4;tj++) {
                        if(abs(movei[ti]) == abs(movej[tj])) continue;
                        int nexti = sx + movei[ti];
                        int nextj = sy + movej[tj];
                        if(!checkBounds(board,nexti,nextj)) continue;
                        
                        if(i == nexti && j == nextj) return true;
                }
        }
        return false;
}

int getValidNeighbors(int board[N][N],int i,int j) {
	int movei[4] = {-1,-2,1,2};
	int movej[4] = {-1,-2,1,2};

	int count = 0;
	for(int ti = 0;ti < 4;ti++) {
		for(int tj = 0;tj < 4;tj++) {
			if(abs(movei[ti]) == abs(movej[tj])) continue;
			int nexti = i + movei[ti];
			int nextj = j + movej[tj];
			if(!checkValid(board,nexti,nextj)) continue;
			count++;
		}
	}

	return count;
}

bool solve(int board[N][N],int i,int j,int move) {
	if(move == N*N)  {
		// if(!isNeighbor(board,i,j)) return false;
		return true;
	}

	int min_count = 1000000;
	int ni = -1,nj = -1;
	for(int ti = 0;ti < 4;ti++) {
		for(int tj = 0;tj < 4;tj++) {
			if(abs(movei[ti]) == abs(movej[tj])) continue;
			int nexti = i + movei[ti];
			int nextj = j + movej[tj];
			if(!checkValid(board,nexti,nextj)) continue;

			int count = getValidNeighbors(board,nexti,nextj);
			if(count <= min_count) {
				min_count = count;
				ni = nexti;
				nj = nextj;
			}
		}
	}
	
	board[ni][nj] = move;
	return solve(board,ni,nj,move + 1);
}

void resetBoard(int board[N][N]) {
	for(int i = 0;i < N;i++) 
		for(int j = 0;j < N;j++)
			board[i][j] = -1;
}

int main() {
	// cin >> N;
	// int board[N][N] = (int **)malloc(N * sizeof(int *));
	// for(int i = 0;i < N;i++)
	// 	board[i] = (int *)malloc(N * sizeof(int));

	int board[N][N];
	for(int i = 0;i < N;i++) 
		for(int j = 0;j < N;j++)
			board[i][j] = -1;
	
	print_board(board);
	srand(time(NULL));	
	sx = rand()%N;
	sy = rand()%N;
	board[sx][sy] = 0;
	while(!solve(board,sx,sy,1)) {
		sx = rand()%N;
		sy = rand()%N;
		resetBoard(board);
		board[sx][sy] = 0;	
	}
	
	print_board(board);
	cout << count_zeros(board) << endl;
}
