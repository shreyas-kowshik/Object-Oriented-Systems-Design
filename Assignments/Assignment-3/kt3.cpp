#include <bits/stdc++.h>

typedef struct perm {
	int vals[8];
};

typedef struct point {
	int x;
	int y;
};

using namespace std;

int m;
point get_next_square(int **board,int x,int y,perm permutation);

// TEMPORARY
int count_zeros(int **board) {
	int count = 0;
	for(int i = 0;i < m;i++)
		for(int j = 0;j < m;j++)
			if(board[i][j] == 0) count++;

	return count;
}

bool isDigit(int n) {
        if(n == 0 || n == 1 || n == 2 || n == 3 || n == 4 || n == 5 || n == 6 || n == 7 || n == 8 || n == 9)
                return true;
        return false;
}

void print_board(int **board) {
	for(int i = 0;i < m;i++) {
		for(int j = 0;j < m;j++) {
			if(isDigit(board[i][j]))
				cout << board[i][j] << "  ";
			else
				cout << board[i][j] << " ";
		}
		cout << endl;
	}
}

perm make_perm(int a) { // a is a 8-digit long integer forming the permutation
	perm p;
	for(int i = 7;i >= 0;i--) {
		int r = a%10;
		p.vals[i] = r;
		a = a/10;
	}

	return p;
}

point make_point(int x,int y) {
	point p;
	p.x = x;
	p.y = y;

	return p;
}

// Declare the global variables
vector<perm> permutations;
vector<point> switches;
int moves[2][8] = {{-2,-1,1,2,2,1,-1,-2},{1,2,2,1,-1,-2,-2,-1}}; // first x is stored then y

void push_perm(perm p) {
	permutations.push_back(p);
}

void push_point(point p) {
	switches.push_back(p);
}

/* Utility functions */
bool checkBounds(int **board,int x,int y) {
	if(x >= 1 && x <= m && y >= 1 && y <= m)
		return true;
	return false;
}
/*********************/

void initializeTable() {
	int r = m%8;

	switch(r) {
		case 0: // Done!
			push_perm(make_perm(34261578));
			push_perm(make_perm(87642135));
			push_perm(make_perm(51867342));
			push_perm(make_perm(51342678));
			push_perm(make_perm(21435678));
		
			push_point(make_point(m-1,m-2));
			push_point(make_point(2,2));
			push_point(make_point(m-8,1));
			push_point(make_point(7,m-3));
			push_point(make_point(-1,-1)); // to signify to use the permutation till the end	
			break;
		
		case 1: // Done!
			push_perm(make_perm(34261578));
			push_perm(make_perm(87642135));
			push_perm(make_perm(51342678));
			push_perm(make_perm(32481765));
			
			push_point(make_point(m-1,m-2));
			push_point(make_point(2,2));
			push_point(make_point(m-6,(m+9)/2));
			push_point(make_point(-1,-1)); // to signify to use the permutation till the end	
			break;

		case 2: // Done!
			push_perm(make_perm(34261578));
			push_perm(make_perm(87642135));
			push_perm(make_perm(51342678));
			push_perm(make_perm(52431678));
			push_perm(make_perm(85647123));
			push_perm(make_perm(15746823));
			
			push_point(make_point(6,1));
			push_point(make_point(3,1));
			push_point(make_point(m-15,4));
			push_point(make_point(10,m-2));
			push_point(make_point(5,(m-6)/2));
			push_point(make_point(-1,-1)); // to signify to use the permutation till the end
			break;

		case 3: // Done!
			push_perm(make_perm(34625718));
			push_perm(make_perm(42681357));
			push_perm(make_perm(86512347));
			push_perm(make_perm(51867342));
			push_perm(make_perm(61825437));
			push_perm(make_perm(71642538));
			
			push_point(make_point(m-1,m-2));
			push_point(make_point(m-6,m));
			push_point(make_point(2,5));
			push_point(make_point(m-10,3));
			push_point(make_point((m+1)/2,m-2));
			push_point(make_point(-1,-1)); // to signify to use the permutation till the end
			break;

		case 4: // Done!
			push_perm(make_perm(34261578));
			push_perm(make_perm(87642135));
			push_perm(make_perm(51867342));
			push_perm(make_perm(51342678));
			push_perm(make_perm(86753421));
			push_perm(make_perm(78563421));
			
			push_point(make_point(m-1,m-2));
			push_point(make_point(2,2));
			push_point(make_point(m-8,1));
			push_point(make_point(10,m-5));
			push_point(make_point(13,(m+2)/2));
			push_point(make_point(-1,-1)); // to signify to use the permutation till the end
			break;

		case 5: // Done!
			push_perm(make_perm(34261578));
			push_perm(make_perm(87642135));
			push_perm(make_perm(51324678));
			push_perm(make_perm(15234678));
			
			push_point(make_point(m-1,m-2));
			push_point(make_point(2,2));
			if (m%16 == 5)
				push_point(make_point(m-2,(m-5)/2));
			else
				push_point(make_point(m-2,(m-13)/2));
			push_point(make_point(-1,-1)); // to signify to use the permutation till the end
			break;

		case 6: // Done!
			push_perm(make_perm(34261578));
			push_perm(make_perm(87642135));
			push_perm(make_perm(54132678));
			push_perm(make_perm(52431678));
			push_perm(make_perm(85647123));
			push_perm(make_perm(12453678));
			
			push_point(make_point(6,1));
			push_point(make_point(3,1));
			push_point(make_point(m-10,1));
			push_point(make_point(10,m-2));
			push_point(make_point(3,(m+8)/2));
			push_point(make_point(-1,-1)); // to signify to use the permutation till the end
			break;

		case 7: // Done!
			push_perm(make_perm(34625718));
			push_perm(make_perm(42681357));
			push_perm(make_perm(86512347));
			push_perm(make_perm(51867342));
			push_perm(make_perm(61825437));
			push_perm(make_perm(61357284));
			
			push_point(make_point(m-1,m-2));
			push_point(make_point(m-6,m));
			push_point(make_point(2,5));
			push_point(make_point(m-6,3));
			push_point(make_point((m+1)/2,m-2));
			push_point(make_point(-1,-1)); // to signify to use the permutation till the end
			break;
	}
}

int degree(int **board,int x,int y) {
	int deg = 0;
	for(int k = 1;k <= 8;k++) {
		int nextx = x + moves[0][k - 1];
		int nexty = y + moves[1][k - 1];
		if(checkBounds(board,nextx,nexty) && board[m - (nexty-1) -1][nextx-1] == 0) {
			deg++;
		}
	}
	return deg;
}

/*
Note : x,y is with reference to the bottom left as the origin and at (0,0)
*/
void Tour(int **board) {
	int x = 1,y = 1; // Keep Everything 1-indexed
	point sw = switches[0];
	perm permutation = permutations[0];
	int t = 0;
	for(int i = 1;x != 0 && y != 0;i++) {
		board[m - (y-1) - 1][x-1] = i;
		if(x == sw.x && y == sw.y) {
			t++;
			sw = switches[t];
			permutation = permutations[t];
		}
		point p = get_next_square(board,x,y,permutation);
		x = p.x;
		y = p.y;
	}
}

point get_next_square(int **board,int x,int y,perm permutation) {
	int min = 9;
	int a = 0,b = 0;
	int key;

	for(int count = 1;count <= 8;count++) {
		int nextx = x +	moves[0][count - 1];
		int nexty = y + moves[1][count - 1];

		if(checkBounds(board,nextx,nexty) && board[m - (nexty-1) -1][nextx-1] == 0) {
			int deg = degree(board,nextx,nexty);

			if(deg < min) {
				min = deg;
				a = nextx;
				b = nexty;
				key = count;
			}

			if(deg == min) {
				for(int k = 1;permutation.vals[k - 1] != key && permutation.vals[k - 1] != count;k++) {
					if(permutation.vals[k - 1] == count) {
						a = nextx;
						b = nexty;
						key = count;
					}
				}
			}
		}
	}

	point p;
	p.x = a;
	p.y = b;
	return p;
}

int main() {
	initializeTable();

	cin >> m;
	int **board = (int **)malloc(m * sizeof(int *));
	for(int i = 0;i < m;i++)
		board[i] = (int *)malloc(m * sizeof(int));

	for(int i = 0;i < m;i++)
		for(int j = 0;j < m;j++)
			board[i][j] = 0;

	cout << count_zeros(board) << endl;
	Tour(board);
	cout << count_zeros(board) << endl;
	// print_board(board);

	return 0;
}
