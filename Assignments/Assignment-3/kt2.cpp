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

// TEMPORARY
int count_zeros(int **board) {
	int count = 0;
	for(int i = 0;i < N;i++)
		for(int j = 0;j < N;j++)
			if(board[i][j] == -1) count++;

	return count;
}

bool checkValid(int **board,int i,int j) {
	// cout << "CHECK VALID " << i << " " << j << endl;
	if(i >= 0 && i < N && j >= 0 && j < N) {
		// cout << "IN 1" << endl;
		if(board[i][j] == -1) {
			// cout << "IN 2" << endl;
			return true;
		}
	}
	return false;
}

bool checkBounds(int **board,int i,int j) {
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
                        if(!checkBounds(board,nexti,nextj)) continue;
                        
                        if(i == nexti && j == nextj) return true;
                }
        }
        return false;
}

int getValidNeighbors(int **board,int i,int j) {
	// cout << "ISME AAYA" << endl;
	int movei[4] = {-1,-2,1,2};
	int movej[4] = {-1,-2,1,2};

	int count = 0;
	// cout << "ISME AAYA 1" << endl;
	for(int ti = 0;ti < 4;ti++) {
		for(int tj = 0;tj < 4;tj++) {
			// cout << "ISME AAYA 2" << endl;
			if(abs(movei[ti]) == abs(movej[tj])) continue;
			// cout << "ISME AAYA 3" << endl;
			int nexti = i + movei[ti];
			int nextj = j + movej[tj];
			// cout << "ISME AAYA 4" << endl;
			if(!checkValid(board,nexti,nextj)) continue;
			// cout << "LOOP COUNT " << count << endl;
			count++;
			// cout << "ISME AAYA 5" << endl;
		}
	}
	// cout << "IN COUNT " << count << endl;
	return count;
}

bool solve(int **board,int i,int j,int move) {
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
			if(!checkValid(board,nexti,nextj))  {
				continue;
			}
			// cout << "1" << endl;

			int count = getValidNeighbors(board,nexti,nextj);
			// cout << "2" << endl;
			// cout << "COUNT " << count << endl;
			if(count <= min_count) {
				min_count = count;
				ni = nexti;
				nj = nextj;
			}
		}
	}
	
	if(ni == -1 && nj == -1) return false;
	board[ni][nj] = move;
	return solve(board,ni,nj,move + 1);
}

void resetBoard(int **board) {
	for(int i = 0;i < N;i++) 
		for(int j = 0;j < N;j++)
			board[i][j] = -1;
}

int main() {
	cin >> N;
	int **board = (int **)malloc(N * sizeof(int *));
	for(int i = 0;i < N;i++)
		board[i] = (int *)malloc(N * sizeof(int));

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
	// cout << count_zeros(board) << endl;
}
