#include <bits/stdc++.h>

using namespace std;
int N; // size of the board
int sx,sy; // the co-ordinates for the start point
// these variables store the relative position to move to at each instant
int movei[4] = {-1,-2,1,2};
int movej[4] = {-1,-2,1,2};

// Function to check if a given number is a digit or not, useful for printing
bool isDigit(int n) {
        if(n == 0 || n == 1 || n == 2 || n == 3 || n == 4 || n == 5 || n == 6 || n == 7 || n == 8 || n == 9)
                return true;
        return false;
}

// Print the board
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

// check if a cell is within bounds and is empty
bool checkValid(int **board,int i,int j) {
	if(i >= 0 && i < N && j >= 0 && j < N) {
		if(board[i][j] == -1) {
			return true;
		}
	}
	return false;
}

// check if a cell is within bounds
bool checkBounds(int **board,int i,int j) {
	if(i >= 0 && i < N && j >= 0 && j < N)
		return true;
	return false;
}

// returns the degree of a cell
int getValidNeighbors(int **board,int i,int j) {
	int movei[4] = {-1,-2,1,2};
	int movej[4] = {-1,-2,1,2};

	int count = 0;
	for(int ti = 0;ti < 4;ti++) {
		for(int tj = 0;tj < 4;tj++) {
			if(abs(movei[ti]) == abs(movej[tj])) continue; // skip as these moves are invalid
			int nexti = i + movei[ti];
			int nextj = j + movej[tj];
			if(!checkValid(board,nexti,nextj)) continue;
			count++;
		}
	}
	
	return count;
}

bool solve(int **board,int i,int j,int move) {
	if(move == N*N)  {
		return true;
	}
	
	int min_count = 1000000;
	int ni = -1,nj = -1;

	// obtain the minimum degree vertex of all the neighbors
	for(int ti = 0;ti < 4;ti++) {
		for(int tj = 0;tj < 4;tj++) {
			if(abs(movei[ti]) == abs(movej[tj])) continue;
			int nexti = i + movei[ti];
			int nextj = j + movej[tj];
			if(!checkValid(board,nexti,nextj))  {
				continue;
			}

			int count = getValidNeighbors(board,nexti,nextj);
			if(count <= min_count) {
				min_count = count;
				ni = nexti;
				nj = nextj;
			}
		}
	}
	
	if(ni == -1 && nj == -1) return false; // no point can be moved to, thus no solution found
	board[ni][nj] = move;
	return solve(board,ni,nj,move + 1);
}

void resetBoard(int **board) {
	for(int i = 0;i < N;i++) 
		for(int j = 0;j < N;j++)
			board[i][j] = -1;
}

int main() {
	cout << "Enter size of board (N) for NxN : ";
	cin >> N;
	if(N < 5) {
		cout << "No Solution Exists" << endl;
		return 0;
	}
	int **board = (int **)malloc(N * sizeof(int *));
	for(int i = 0;i < N;i++)
		board[i] = (int *)malloc(N * sizeof(int));

	for(int i = 0;i < N;i++) 
		for(int j = 0;j < N;j++)
			board[i][j] = -1;
	
	srand(time(NULL));
	sx = rand()%N;
	sy = rand()%N;
	board[sx][sy] = 0;
	while(!solve(board,sx,sy,1)) {
		// randomly keep generating start points until solution is found
		sx = rand()%N;
		sy = rand()%N;
		resetBoard(board);
		board[sx][sy] = 0;	
	}
	
	print_board(board);
	return 0;
}
