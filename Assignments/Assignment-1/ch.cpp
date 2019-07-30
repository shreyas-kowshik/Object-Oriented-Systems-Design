#include <bits/stdc++.h>
#include <graphics.h>

using namespace std;

typedef struct Point {
	int x;
	int y;
};

void plotPoints(vector<Point>);

vector<Point> global_points;
Point global_bottom; // the bottom most point for Graham scan
int N = 100; // number of points to be generated
int RANGE = 250; // the points will be generated with co-ordinates in the range : [1,RANGE-1]
int DELAY_TIME = 100; // the number of miliseconds to wait between two steps, used for displaying/animation

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
			Point tem;
			tem.x = px;
			tem.y = py;
			global_points.push_back(tem);
		}
		else
			px = x;
		i++;
	}
}

void write_nos_to_file() {
        ofstream myfile;
        myfile.open("input.txt");
	
        for(int i = 0;i < N;i++) {
                myfile << rand()%RANGE + 1 << " " << rand()%RANGE + 1 << " ";// write as x y in file
        }
        myfile << "\n";
        myfile.close();
}

void print_ar(vector<Point>& arr) {
        ofstream myfile;
        myfile.open("output.txt");
        for(int i = 0;i < arr.size();i++) {
                myfile << arr[i].x << " " << arr[i].y << " " ;
        }
        myfile << "\n";
        myfile.close();
}

int orientation(Point p,Point q,Point r) {
	int res = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
	
	if(res == 0) return 0;// p,q,r are colinear
	if(res > 0) return 1;//p,q,r are clockwise oriented
	else return 2;//p,q,r are counter-clockwise oriented
}


int orientation_(Point p,Point q,Point r) {
	int res = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
	
	if(res == 0) return 0;// p,q,r are colinear
	if(res > 0) return -1;//p,q,r are clockwise oriented
	else return 1;//p,q,r are counter-clockwise oriented
}

double dist(Point p1,Point p2) {
	return sqrt(pow((p1.x - p2.x),2) + pow((p1.y,p2.y),2));
}

int compare(const void *vp1, const void *vp2) 
{ 
   Point *p1 = (Point *)vp1; 
   Point *p2 = (Point *)vp2; 
  
   // Find orientation 
   int o = orientation(global_bottom, *p1, *p2); 
   if (o == 0) 
     return (dist(global_bottom, *p2) >= dist(global_bottom, *p1))? -1 : 1;// if angles are same, consider the farther point 
  
   return (o == 2)? -1: 1; 
}

double norm(Point p) {
	return sqrt(pow(p.x,2) + pow(p.y,2));
}

double getAngle(Point p,Point q,Point r) {
	if(((p.x == q.x) && (p.y == q.y)) || ((q.x == r.x) && (q.y == r.y)) || ((p.x == r.x) && (p.y == r.y))) return -100000; 
	// Returns the angle pqr between three points p,q,r
	double dot = (r.x - q.x)*(q.x - p.x) + (r.y - q.y)*(q.y - p.y);
	Point r_q;
	r_q.x = r.x - q.x;
	r_q.y = r.y - q.y;
	double norm_r_q = norm(r_q);
	Point q_p;
	q_p.x = q.x - p.x;
	q_p.y = q.y - p.y;
	double norm_q_p = norm(q_p);

	double theta = acos(dot/(1.0 * norm_r_q * norm_q_p));
	return 3.14 - theta;
}

Point nextToTop(stack<Point> S) {
	Point p = S.top();
	S.pop();
	Point out = S.top();
	S.push(p);
	return out;
}

void swap(Point &p1,Point &p2) {
	Point t = p1;
	p1 = p2;
	p2 = t;
}

void print_points(vector<Point> points) {
	cout << "---Printing Points---" << endl;
	for(int i = 0;i < points.size();i++) {
		cout << points[i].x << " " << points[i].y << endl;
	}
}

int tangent(vector<Point> v,Point p){
}

int getMaxAnglePoint(vector<Point> hull,Point pk_1,Point pk) {
	// Returns the point p with the largest angle pk_1,pk,p from the hull
	int l=0;
	int r = hull.size();
	int l_before = orientation_(pk, hull[0], hull[hull.size()-1]);
	int l_after = orientation_(pk, hull[0], hull[(l + 1) % hull.size()]);
	while (l < r){
		int c = ((l + r)>>1);
		int c_before = orientation_(pk, hull[c], hull[(c - 1) % hull.size()]);
		int c_after = orientation_(pk, hull[c], hull[(c + 1) % hull.size()]);
		int c_side = orientation_(pk, hull[l], hull[c]);
		if (c_before != 1 and c_after != 1)
			return c;
		else if ((c_side == -1) and (l_after == 1 or l_before == l_after) or (c_side == 1 and c_before == 1))
			r = c;
		else
			l = c + 1 ;
		l_before = -c_after; 
		l_after = orientation_(pk, hull[l], hull[(l + 1) % hull.size()]);
	}
	return l;

	/*
	double max_angle = -100000;
	int id = -1;
	for(int i = 0;i < hull.size();i++) {
		double theta = getAngle(pk_1,pk,hull[i]);
		if (theta >= max_angle) {
			max_angle = theta;
			id = i;
		}
	}
	return id;
	*/
}

void plotPoint(Point p) {
	circle(p.x,p.y,2);
}

void plotPoints(vector<Point> points) {
    	setcolor(GREEN);	
	for(int i = 0;i < points.size();i++) {
		circle(points[i].x, points[i].y, 1);
	}		
}

void plotPolygon(vector<Point> vertices) {
	for(int i = 0;i < vertices.size() - 1;i++) {
		line(vertices[i].x,vertices[i].y,vertices[i+1].x,vertices[i+1].y);	
	}
	line(vertices[0].x,vertices[0].y,vertices[vertices.size() - 1].x,vertices[vertices.size() - 1].y);
}

vector<Point> GrahamScan(vector<Point> points) {
	stack<Point> S;
	
	Point bottom;
	int min_y = 100000,min_x = 100000;
	int min_id;

	for(int i = 0;i < points.size();i++) {
		if(points[i].y < min_y) {
			min_y = points[i].y;
			min_x = points[i].x;
			bottom.x = min_x;
			bottom.y = min_y;
			min_id = i;
		}

		if(points[i].y == min_y) {
			if(points[i].x <= min_x) {
				bottom.x = min_x;
				bottom.y = min_y;
				min_id = i;
			}
		}
	}

	//bring bottom-most point to start of array
	swap(points[0],points[min_id]);	

	global_bottom = points[0]; 
        qsort(&points[1], points.size() - 1, sizeof(Point), compare);

	// We now have to remove points with the same angles
	int s = 1;// to store the final set of points
	vector<Point> m_points;// m_points -> modified points
	m_points.push_back(global_bottom);
	
	for(int i = 1;i < points.size();i++) {
		while(i < points.size() - 1 && orientation(global_bottom,points[i],points[i+1]) == 0) {	
			if(i == points.size() - 2) {
				i++;
				break;
			}
			
			i++;
		}

		m_points.push_back(points[i]);	
		//points[s] = points[i];
		//s++;
	}

	
	if(m_points.size() < 3) {
		return m_points;
	}
	
	S.push(m_points[0]);
	S.push(m_points[1]);
	S.push(m_points[2]);

	for(int i = 3;i < m_points.size();i++) {
		while(orientation(nextToTop(S),S.top(),m_points[i]) != 2) {
			S.pop();
		}
		S.push(m_points[i]);
	}

	vector<Point> hull;
	while(!S.empty()) {
		hull.push_back(S.top());
		S.pop();
	}

	reverse(hull.begin(),hull.end());
	return hull;
}

vector<Point> Chans(vector<Point> points,int m,int H) {
	int n = points.size();
	int subset_size =  n/m;
	vector<vector<Point> > hulls; // stores convex hulls for each subset
	
	for(int i = 0;i < m;i++) {
		int up_lim;
		if(i == m - 1)
			up_lim = points.size();
		else
			up_lim = (i + 1) * subset_size;

		vector<Point> sub_points;
		for(int j = i * subset_size;j < up_lim;j++) {
			sub_points.push_back(points[j]);
		}
		
		vector<Point> hull = GrahamScan(sub_points);
		hulls.push_back(hull);
	}

	Point p0;
	p0.x = 0;
	p0.y = 100000; // Equivalent to -infinity in our range, as points are only upto RANGE = 300
	
	Point p1;
	vector<Point> convex_hull; // stores the points for the final convex hull
	int hull_id = -1, max_x = -1,point_id = -1;

	for(int i = 0;i < hulls.size();i++) {
		for(int j = 0;j < hulls[i].size();j++) {
			if(hulls[i][j].x > max_x) {
				max_x = hulls[i][j].x;
				hull_id = i;
				point_id = j;
				p1.x = hulls[i][j].x;
				p1.y = hulls[i][j].y;
			}
		}
	}

	convex_hull.push_back(p1);
	
	setcolor(RED);
	for(int i = 0;i < hulls.size();i++) {
		plotPolygon(hulls[i]);
	}
	
	Point pk,pk_1;
	pk.x = p1.x;
	pk.y = p1.y;
	pk_1.x = p0.x;
	pk_1.y = p0.y;


	for(int k = 0;k < H;k++) {
		vector<Point> max_angle_points;
		for(int i = 0;i < hulls.size();i++) {
			int p_id = getMaxAnglePoint(hulls[i],pk_1,pk);
			max_angle_points.push_back(hulls[i][p_id]);
		}
		delay(DELAY_TIME);	
		
		double max_angle = -1000000.0;
		Point next_point;
		for(int i = 0;i < max_angle_points.size();i++) {
			double theta = getAngle(pk_1,pk,max_angle_points[i]);
			if (theta >= max_angle) {
				max_angle = theta;
				next_point.x = max_angle_points[i].x;
				next_point.y = max_angle_points[i].y;
			}
		}

		delay(DELAY_TIME);
		if(next_point.x == p1.x && next_point.y == p1.y) {
			return convex_hull;
		}
		else {
			convex_hull.push_back(next_point);
			pk_1.x = pk.x;
			pk_1.y = pk.y;
			pk.x = next_point.x;
			pk.y = next_point.y;							
		}
		setcolor(WHITE);
		line(pk_1.x,pk_1.y,pk.x,pk.y);
	}
	
	vector<Point> empty_hull;
	return empty_hull;
}

int min(int a,int b) {
	if(a >= b) return b;
	else return a;
}

int main() {
	int gd = DETECT, gm;
    	initgraph(&gd, &gm, NULL);
	
	write_nos_to_file();	
	read_nos();
	
	vector<Point> hull;
	int t = 1;
	while(true) {
		cleardevice();
		plotPoints(global_points);
		int H = (int)(pow(2,pow(2,t)));
		H = min(H,global_points.size());
		cout << endl << "--------------Trial-------------" << endl;
		cout << "m = H = " << H << endl << endl << endl;
		if (H > global_points.size()) break;
		hull = Chans(global_points,H,H);
		if(hull.size() < 1) {
			cout << "Convex Hull not found, trying for different m and H..." << endl;
			t++;
			continue;
		}
		setcolor(YELLOW);
		plotPolygon(hull);
		break;
	}
	
	setcolor(YELLOW);
	plotPolygon(hull);
	cout << "Hull Found!" << endl << "Press any key to exit the program..." << endl;
	getch();
    	closegraph();
	print_ar(hull);	
	return 0;
}
