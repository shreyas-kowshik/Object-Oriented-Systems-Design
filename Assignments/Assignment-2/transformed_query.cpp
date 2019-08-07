#include <bits/stdc++.h>

using namespace std;

int N = 5; // number of points
int INF = 1000000;

typedef struct point {
	int x;
	int y;
};

typedef struct tpair {
	/*
	Represents (a|b)
	*/
	int a;
	int b;
};

typedef struct tpoint {
	/*
	Represents a transformed point as ((a|b),(c|d))
	*/
	tpair tx;
	tpair ty;
};

tpoint from_point(point p) {
	// Returns a transformed point
	tpoint t;
	t.tx.a = p.x;
	t.tx.b = p.y;
	t.ty.a = p.y;
	t.ty.b = p.x;	
	
	return t;
}

bool isLess(tpair t1,tpair t2) {
	// Determines whether t1 < t2
	return ((t1.a < t2.a) || ((t1.a == t2.a) && (t1.b < t2.b)));
}

bool isEqual(tpair t1,tpair t2) {
	return (t1.a == t2.a) && (t1.b == t2.b);
}

bool isLessEq(tpair t1,tpair t2) {
	// Determines whether t1 < t2
	return ((t1.a < t2.a) || ((t1.a == t2.a))) || (isEqual(t1,t2));
}

bool isGreater(tpair t1,tpair t2) {
	// Determines whether t1 > t2
	return (!isLess(t1,t2) && !isEqual(t1,t2));
}

bool isGreaterEq(tpair t1,tpair t2) {
	return !isLess(t1,t2);
}

typedef struct Region {
	tpoint tpl;// Co-ordinates of the left and upper bounds
	tpoint tpr;// Co-ordinates of the right and lower bounds
};

typedef struct node {
	tpoint tp;
	int flag; // 1 - horizontal line, 2 - vertical line, 3 - leaf
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

/* Utilities */
void print_array(vector<tpoint> arr) {
	cout << "Printing array of points " << endl;
	for(int i = 0;i < arr.size();i++) {
		cout << arr[i].tx.a << " " << arr[i].tx.b << endl;
	}
}

bool x_compare(tpoint p1, tpoint p2)
{
   // comparator function for sorting two points, used in the qsort function to compare two points while sorting
   if(isLess(p1.tx,p2.tx)) return true; 
   else return false;
}

bool y_compare(tpoint p1, tpoint p2)
{
   // comparator function for sorting two points, used in the qsort function to compare two points while sorting
   if(isLess(p1.ty,p2.ty)) return true; 
   else return false;
}

int isLeaf(node *current) {
	if((current->left == NULL) && (current->right == NULL)) return 1;
	else return 0;
}

node* initNode(int x,int y,int depth) {
	point p;
	p.x = x;
	p.y = y;
	tpoint tp = from_point(p);

	node *current = (node *)malloc(sizeof(node));
	current->tp = tp;
	current->depth = depth;
	current->left = NULL;
	current->right = NULL;

	return current;	
}

void inOrder(node *current) {
	if(current == NULL) return;
	inOrder(current->left);
	//if(isLeaf(current))
		//cout << "In Region : " << current->p.x << " " << current->p.y << endl;
	//if(isLeaf(current))
	cout << current->tp.tx.a << " " << current->tp.tx.b << endl;
	inOrder(current->right);
}


void print_node(node *n) {
	cout << "Node : " << "x : " << n->tp.tx.a << " :: y : " << n->tp.tx.b << " :: depth : " << n->depth << endl;
	//cout << "Region : xl : " << n->region.xl << " :: yl : " << n->region.yl << " :: xr : " << n->region.xr << " :: yr : " << n->region.yr << endl;
}


int checkNodeInRange(node *current,tpoint tpl,tpoint tpr) {
	tpair tx = current->tp.tx;
	tpair ty = current->tp.ty;
	
	if(isGreaterEq(tx,tpl.tx) && isLessEq(tx,tpr.tx) && isLessEq(ty,tpl.ty) && isGreaterEq(ty,tpr.ty)) return 1;
	else return 0;
}

/***************/

// Build the tree
node* build_tree(vector<tpoint> points,int i,int j,int depth) {
	// if(i > j) return NULL;
	if(i >= j) {
		// return a leaf node with the point co-ordinates
		node *current = initNode(points[i].tx.a,points[i].tx.b,depth);
		current->flag = 3;
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
	if(depth % 2 == 0) {
		current = initNode(points[mid].tx.a,0,depth);
		current->flag = 1;
	}
	else {
		current = initNode(0,points[mid].tx.b,depth);
		current->flag = 2;
	}
	current->left = left;
	current->right = right;

	return current;
}

int checkLeftRegionInRange(node *current,tpoint tpl,tpoint tpr) {
	Region left_child_region;
	if(current->flag == 2) { // if horizontal line
		left_child_region.tpl.tx = current->region.tpl.tx;
		left_child_region.tpr.tx = current->region.tpr.tx;
		left_child_region.tpr.ty = current->region.tpr.ty;
		left_child_region.tpl.ty = current->tp.ty;
	}
	else { // if vertical line
		left_child_region.tpl.tx = current->region.tpl.tx;
		left_child_region.tpr.tx = current->tp.tx;
		left_child_region.tpr.ty = current->region.tpr.ty;
		left_child_region.tpl.ty = current->region.tpl.ty;
	}

	current->left->region = left_child_region;
	
	if(isGreaterEq(left_child_region.tpl.tx,tpl.tx) && isLessEq(left_child_region.tpl.ty,tpl.ty) && isLessEq(left_child_region.tpr.tx,tpr.tx) && isGreaterEq(left_child_region.tpr.ty,tpr.ty))
	return 1;
	else return 0;
}

int checkLeftRegionIntersectsRange(node *current,tpoint tpl,tpoint tpr) {
	Region left_child_region;
	if(current->flag == 2) { // if horizontal line
		left_child_region.tpl.tx = current->region.tpl.tx;
		left_child_region.tpr.tx = current->region.tpr.tx;
		left_child_region.tpr.ty = current->region.tpr.ty;
		left_child_region.tpl.ty = current->tp.ty;
	}
	else { // if vertical line
		left_child_region.tpl.tx = current->region.tpl.tx;
		left_child_region.tpr.tx = current->tp.tx;
		left_child_region.tpr.ty = current->region.tpr.ty;
		left_child_region.tpl.ty = current->region.tpl.ty;
	}

	current->left->region = left_child_region;
	
	if(isGreater(left_child_region.tpl.tx,tpr.tx) || isLess(left_child_region.tpl.ty,tpr.ty) || isLess(left_child_region.tpr.tx,tpl.tx) || isGreater(left_child_region.tpr.ty,tpl.ty))
	return 0;
	else return 1;
}

int checkRightRegionInRange(node *current,tpoint tpl,tpoint tpr) {
	Region right_child_region;
	if(current->flag == 2) { // if horizontal line
		right_child_region.tpl.tx = current->region.tpl.tx;
		right_child_region.tpr.tx = current->region.tpr.tx;
		right_child_region.tpr.ty = current->tp.ty;
		right_child_region.tpl.ty = current->region.tpl.ty;
	}
	else { // if vertical line
		right_child_region.tpl.tx = current->tp.tx;
		right_child_region.tpr.tx = current->region.tpr.tx;
		right_child_region.tpr.ty = current->region.tpr.ty;
		right_child_region.tpl.ty = current->region.tpl.ty;
	}

	current->right->region = right_child_region;

	if(isGreaterEq(right_child_region.tpl.tx,tpl.tx) && isLessEq(right_child_region.tpl.ty,tpl.ty) && isLessEq(right_child_region.tpr.tx,tpr.tx) && isGreaterEq(right_child_region.tpr.ty,tpr.ty))
	return 1;
	else return 0;
}

int checkRightRegionIntersectsRange(node *current,tpoint tpl,tpoint tpr) {
	Region right_child_region;
	if(current->flag == 2) { // if horizontal line
		right_child_region.tpl.tx = current->region.tpl.tx;
		right_child_region.tpr.tx = current->region.tpr.tx;
		right_child_region.tpr.ty = current->tp.ty;
		right_child_region.tpl.ty = current->region.tpl.ty;
	}
	else { // if vertical line
		right_child_region.tpl.tx = current->tp.tx;
		right_child_region.tpr.tx = current->region.tpr.tx;
		right_child_region.tpr.ty = current->region.tpr.ty;
		right_child_region.tpl.ty = current->region.tpl.ty;
	}

	current->right->region = right_child_region;

	if(isGreater(right_child_region.tpl.tx,tpr.tx) || isLess(right_child_region.tpl.ty,tpr.ty) || isLess(right_child_region.tpr.tx,tpl.tx) || isGreater(right_child_region.tpr.ty,tpl.ty))
	return 0;
	else return 1;
}

void query(node *current,tpoint tpl,tpoint tpr) {
	//cout << "In Query " << endl;
	if(isLeaf(current)) {
		if(checkNodeInRange(current,tpl,tpr)) {
			//print_node(current);
			cout << "In Region : " << current->tp.tx.a << " " << current->tp.tx.b << endl;
		}
		return;
	}
	if(checkLeftRegionInRange(current,tpl,tpr)) {
		//cout << "1 " << endl;
		inOrder(current->left);
	}
	else if(checkLeftRegionIntersectsRange(current,tpl,tpr)) {
		//cout << "2 " << endl;
		//print_node(current);
		query(current->left,tpl,tpr);
	}	
	//print_node(current);
	if(checkRightRegionInRange(current,tpl,tpr)) {
		//cout << "3 " << endl;
		inOrder(current->right);
	}
	else if(checkRightRegionIntersectsRange(current,tpl,tpr)) {
		//cout << "4 " << endl;
		//print_node(current);
		query(current->right,tpl,tpr);
	}
	//cout << "Leaving Query " << endl;
	//print_node(current);
}

int main() {
	int x[10] = {2,4,6,8,10,12,15,13,7,5};
	int y[10] = {3,7,9,11,13,15,1,2,5,6};

	int xl = 4,xr = 8,yl = 13,yr = 3;
	// Transform the range
	tpoint tpl;
	tpl.tx.a = xl;tpl.tx.b = -INF;
	tpl.ty.a = yl;tpl.ty.b = INF;

	tpoint tpr;
	tpr.tx.a = xr;tpr.tx.b = INF;
	tpr.ty.a = yr;tpr.ty.b = -INF;

	cout << "R : " << " xl : " << xl << " :: yl : " << yl << " :: xr : " << xr << " :: yr : " << yr << endl; 
	vector<tpoint> points;
	for(int i = N-1;i >= 0;i--) {
		point p;
		p.x = x[i];
		p.y = y[i];
		tpoint tp;
		tp = from_point(p);
		points.push_back(tp);
	}
		
	print_array(points);
	root = build_tree(points,0,points.size() - 1,0);
	cout << "Inorder traversal " << endl;
	inOrder(root);
	cout << "Inorder " << endl;
	//inOrder(root);
	/*
	root->region.xl = -INF;
	root->region.yl = INF;
	root->region.xr = INF;
	root->region.yr = -INF;

	cout << root->p.x << " " << root->p.y << endl;
	cout << "Inorder : " << endl;
	//inOrder(root);
	*/
	// Query
	query(root,tpl,tpr);	
	return 0;
}
