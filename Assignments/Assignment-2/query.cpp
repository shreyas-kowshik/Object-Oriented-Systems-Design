#include <bits/stdc++.h>

using namespace std;

int N = 7; // number of points
int RANGE = 100;
int INF = 1000000;

typedef struct point {
	int x;
	int y;
};

vector<point> global_points;
vector<point> output_points;

typedef struct Region {
	int xl;// top left x co-ordinate
	int yl;// top left y co-ordinate
	int xr;// bottom right x co-ordinate
	int yr;// bottom right y co-ordinate
};

typedef struct node {
	point p;
	/*
	For non-leaf nodes, p stores the equation of the horizontal or vertical line with the other axis = 0
	For instance, a horizontal line y = 3 is stored as (0,3), a vertical line x = 2 is stored as (2,0)
	For leaf nodes, p stores the co-ordinates of the point
	*/
	int depth; // used to test whether to insert a horizontal or vertical line in the node
	struct node *left;
	struct node *right;

	Region region;	
};

node *root = NULL;

/* File Operations */
void write_nos_to_file() {
        // Points are written as x y ... (x y pairs seperated by a space)
        ofstream myfile;
        myfile.open("input.txt");

        for(int i = 0;i < N;i++) {
                myfile << rand()%RANGE + 1 << " " << rand()%RANGE + 1 << " "; // write as x y in file
        }
        myfile << "\n";
        myfile.close();
}

void print_ar(vector<point> arr) {
        // Points are written as x y ... (x y pairs seperated by a space)
        ofstream myfile;
        myfile.open("output.txt");
        for(int i = 0;i < arr.size();i++) {
                myfile << arr[i].x << " " << arr[i].y << " ";
        }
        myfile << "\n";
        myfile.close();
}

void read_nos() {
        //Opens a file and reads the numbers to the vector
        int x;
        ifstream infile;
        infile.open("input.txt");
        int i = 1;
        int px,py;

        while(infile >> x) {
                if(x == EOF) break;
                if(i % 2 == 0) {
                        py = x;
                        point tem;
                        tem.x = px;
                        tem.y = py;
                        global_points.push_back(tem);
                }
                else
                        px = x;
                i++;
        }
}
/*******************/

/* Utilities */
void print_array(vector<point> arr) {
	cout << "Printing array of points " << endl;
	for(int i = 0;i < arr.size();i++) {
		cout << arr[i].x << " " << arr[i].y << endl;
	}
}

bool x_compare(point p1, point p2)
{
   // comparator function for sorting two points, used in the qsort function to compare two points while sorting
   //point *p1 = (point *)vp1; 
   //point *p2 = (point *)vp2;

   if(p1.x < p2.x) return true; 
   if(p1.x == p2.x) return true;
   if(p1.x > p2.x) return false;
}

bool y_compare(point p1, point p2)
{
   // comparator function for sorting two points, used in the qsort function to compare two points while sorting
   //point *p1 = (point *)vp1; 
   //point *p2 = (point *)vp2;

   if(p1.y < p2.y) return true; 
   if(p1.y == p2.y) return true;
   if(p1.y > p2.y) return false;
}

int isLeaf(node *current) {
	if((current->left == NULL) && (current->right == NULL)) return 1;
	else return 0;
}

node* initNode(int x,int y,int depth) {
	point p;
	p.x = x;
	p.y = y;
	
	node *current = (node *)malloc(sizeof(node));
	current->p = p;
	current->depth = depth;
	current->left = NULL;
	current->right = NULL;

	return current;	
}

void inOrder(node *current) {
	if(current == NULL) return;
	inOrder(current->left);
	//if(isLeaf(current))
		cout << "In Region : " << current->p.x << " " << current->p.y << endl;
	inOrder(current->right);
}

void print_node(node *n) {
	cout << "Node : " << "x : " << n->p.x << " :: y : " << n->p.y << " :: depth : " << n->depth << endl;
	cout << "Region : xl : " << n->region.xl << " :: yl : " << n->region.yl << " :: xr : " << n->region.xr << " :: yr : " << n->region.yr << endl;
}

int checkNodeInRange(node *current,int xl,int yl,int xr,int yr) {
	int x = current->p.x;
	int y = current->p.y;
	
	if((x >= xl) && (x <= xr) && (y <= yl) && (y >= yr)) return 1;
	else return 0;
}

/***************/

// Build the tree
node* build_tree(vector<point> points,int i,int j,int depth) {
	// if(i > j) return NULL;
	if(i >= j) {
		// return a leaf node with the point co-ordinates
		node *current = initNode(points[i].x,points[i].y,depth);
		return current;
	}

	int mid = (i + j)/2;
	if(depth % 2 == 0) {
		// Add a vertical line
		// Sort points according to their x-coordinates
		sort(points.begin() + i,points.begin() +  j + 1, x_compare);	
	}
	else {
		// Add a horizontal line
		// Sort the points according to their y-coordinates
		sort(points.begin() + i,points.begin() +  j + 1, y_compare);	
	}

	node *left = build_tree(points,i,mid,depth + 1);
	node *right = build_tree(points,mid + 1,j,depth + 1);

	node *current;
	if(depth % 2 == 0)
		current = initNode(points[mid].x,0,depth);
	else
		current = initNode(0,points[mid].y,depth);
	current->left = left;
	current->right = right;

	return current;
}

int checkLeftRegionInRange(node *current,int xl,int yl,int xr,int yr) {
	Region left_child_region;
	if(current->p.x == 0) { // if horizontal line
		left_child_region.xl = current->region.xl;
		left_child_region.xr = current->region.xr;
		left_child_region.yr = current->region.yr;
		left_child_region.yl = current->p.y;
	}
	else { // if vertical line
		left_child_region.xl = current->region.xl;
		left_child_region.xr = current->p.x;
		left_child_region.yr = current->region.yr;
		left_child_region.yl = current->region.yl;
	}

	current->left->region = left_child_region;
	
	if((left_child_region.xl >= xl) && (left_child_region.yl <= yl) && (left_child_region.xr <= xr) && (left_child_region.yr >= yr))
	return 1;
	else return 0;
}

int checkLeftRegionIntersectsRange(node *current,int xl,int yl,int xr,int yr) {
	Region left_child_region;
	if(current->p.x == 0) { // if horizontal line
		left_child_region.xl = current->region.xl;
		left_child_region.xr = current->region.xr;
		left_child_region.yr = current->region.yr;
		left_child_region.yl = current->p.y;
	}
	else { // if vertical line
		left_child_region.xl = current->region.xl;
		left_child_region.xr = current->p.x;
		left_child_region.yr = current->region.yr;
		left_child_region.yl = current->region.yl;
	}

	current->left->region = left_child_region;
	
	if((left_child_region.xl > xr) || (left_child_region.yl < yr) || (left_child_region.xr < xl) || (left_child_region.yr > yl))
	return 0;
	else return 1;
}

int checkRightRegionInRange(node *current,int xl,int yl,int xr,int yr) {
	Region right_child_region;
	if(current->p.x == 0) { // if horizontal line
		right_child_region.xl = current->region.xl;
		right_child_region.xr = current->region.xr;
		right_child_region.yr = current->p.y;
		right_child_region.yl = current->region.yl;
	}
	else { // if vertical line
		right_child_region.xl = current->p.x;
		right_child_region.xr = current->region.xr;
		right_child_region.yr = current->region.yr;
		right_child_region.yl = current->region.yl;
	}

	current->right->region = right_child_region;
	
	if((right_child_region.xl >= xl) && (right_child_region.yl <= yl) && (right_child_region.xr <= xr) && (right_child_region.yr >= yr))
	return 1;
	else return 0;
}

int checkRightRegionIntersectsRange(node *current,int xl,int yl,int xr,int yr) {
	Region right_child_region;
	if(current->p.x == 0) { // if horizontal line
		right_child_region.xl = current->region.xl;
		right_child_region.xr = current->region.xr;
		right_child_region.yr = current->p.y;
		right_child_region.yl = current->region.yl;
	}
	else { // if vertical line
		right_child_region.xl = current->p.x;
		right_child_region.xr = current->region.xr;
		right_child_region.yr = current->region.yr;
		right_child_region.yl = current->region.yl;
	}

	current->right->region = right_child_region;
	
	if((right_child_region.xl > xr) || (right_child_region.yl < yr) || (right_child_region.xr < xl) || (right_child_region.yr > yl))
	return 0;
	else return 1;
}

void query(node *current,int xl,int yl,int xr,int yr) {
	//cout << "In Query " << endl;
	if(isLeaf(current)) {
		if(checkNodeInRange(current,xl,yl,xr,yr)) {
			//print_node(current);
			cout << current->p.x << " " << current->p.y << endl;
			output_points.push_back(current->p);
		}
		return;	
	}		
	if(checkLeftRegionInRange(current,xl,yl,xr,yr)) {
		//cout << "1 " << endl;
		inOrder(current->left);
	}
	else if(checkLeftRegionIntersectsRange(current,xl,yl,xr,yr)) {
		//cout << "2 " << endl;
		//print_node(current);
		query(current->left,xl,yl,xr,yr);
	}	
	//print_node(current);
	if(checkRightRegionInRange(current,xl,yl,xr,yr)) {
		//cout << "3 " << endl;
		inOrder(current->right);
	}
	else if(checkRightRegionIntersectsRange(current,xl,yl,xr,yr)) {
		//cout << "4 " << endl;
		//print_node(current);
		query(current->right,xl,yl,xr,yr);
	}
	//cout << "Leaving Query " << endl;
	//print_node(current);
}

int main() {
	cout << "---Enter integer corresponding to the option---" << endl;
	cout << "1. Generate points randomly in Range - [0," << RANGE << "]" << endl;
	cout << "2. Manually type points" << endl;

	int choice;
	cin >> choice;
	
	if(choice == 1) {
		write_nos_to_file();
		read_nos();
	}
	else if(choice == 2) {
		cout << "Enter the number of points to provide values : ";
		cin >> N;
		for(int i = 0;i < N;i++) {
			point p;
			cout << "Enter point[" << i << "] : x : ";
			cin >> p.x;	
			cout << "Enter point[" << i << "] : y : ";
			cin >> p.y;
			global_points.push_back(p);
		}
	}

	int xl,xr,yl,yr;
	cout << "---Enter the query range for the rectangle---" << endl;
	cout << "Enter the x co-ordinate of the top left corner of the rectangle : ";
	cin >> xl;
	cout << "Enter the y co-ordinate of the top left corner of the rectangle : ";
	cin >> yl;
	cout << "Enter the x co-ordinate of the bottom right corner of the rectangle : ";
	cin >> xr;
	cout << "Enter the y co-ordinate of the bottom right corner of the rectangle : ";
	cin >> yr;
	
	print_array(global_points);
	root = build_tree(global_points,0,global_points.size() - 1,0);
	root->region.xl = -INF;
	root->region.yl = INF;
	root->region.xr = INF;
	root->region.yr = -INF;

	cout << "Points inside rectangle : " << endl;
	// Query
	query(root,xl,yl,xr,yr);	
	
	// write output points to file
	print_ar(output_points);
	
	return 0;
}
