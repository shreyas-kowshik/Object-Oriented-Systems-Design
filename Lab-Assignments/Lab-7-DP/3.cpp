#include<iostream> 
#include <bits/stdc++.h>
using namespace std; 

int W;

typedef struct item {
     int weight,value;
};

vector<item> items;

/*** Utility functions ***/
void read_nos() {
	//Opens a file and reads the numbers to the vector
	int x;
	ifstream infile;
	infile.open("input2.txt");
	bool first = true;
	int i = 0;
	item git;
	while(infile >> x) {
		if(first) {
		     W = x;
		     first = false;
		}
		else {
		     item it;
		     if((i%2)==0) {
		          item it;
		          git = it;
		          git.value = x;
		     }
		     else {
		          git.weight = x;
		          items.push_back(git);
		     }
		     i++;
		}
	}
}

bool compare(item a,item b) 
{ 
    double ra = a.value/a.weight;
    double rb = b.value/b.weight;

    return (rb < ra); 
} 

void print_items(vector<item> items) {
     for(int i = 0;i < items.size();i++) {
          cout << items[i].weight << " " << items[i].value << endl;
     }
}

int main() {
     read_nos();
     print_items(items);
     
     int max_val = -1;
     for(int i = 0;i < items.size();i++) {
          if(items[i].value > max_val) {
               max_val = items[i].value;
          }
     }
     
     sort(items.begin(),items.end(), compare);
     
     // do modified greedy knapsack now
     int k = 0;
     int w = W;
     int sum = 0;
     while(items[k].weight <= w) {
          sum += items[k].value;
          w = w - items[k].weight;
          k++;
     }
     
     int sol = max(sum,max_val);
     cout << "Max Val : " << sol << endl;
     return 0;
}
