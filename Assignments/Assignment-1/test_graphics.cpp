// C code to illustrate using 
// graphics in linux enviornment 
#include<stdio.h> 
#include<stdlib.h> 
#include<graphics.h> 

int main() 
{ 
    int gd = DETECT, gm; 
    initgraph(&gd, &gm, NULL); 

    setcolor(RED); 
    circle(50, 50, 1); 
  
    setcolor(GREEN);
    circle(100, 50, 1); 

    delay(500000); 
    closegraph(); 
    return 0; 
} 
