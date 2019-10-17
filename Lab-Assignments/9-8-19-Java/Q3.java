import java.util.*;
import java.lang.*;
import java.io.*;

public class Q3 {
     public static void main(String[] args) {
          Scanner in = new Scanner(System.in);
          
          int rows = 0;
          int columns = 0;
          int n = 7;
          int[][] Mat = {{0,1,1,1,1,1,1},
                         {1,0,0,0,1,0,0},
                         {1,0,0,0,1,0,0},
                         {1,0,0,0,1,0,0},
                         {1,1,1,1,0,1,1},
                         {1,0,0,0,1,0,0},
                         {1,0,0,0,1,0,0}};
          // Mat = new int[n][n];
          
          // Mat = {{0,1},{1,0}};
          /*
          // Read from file
          try {
               Scanner sc = new Scanner(new BufferedReader(new FileReader("input.txt")));
               // pre-read in the number of rows/columns
               while(sc.hasNextLine())
               {
                   String[] line = sc.nextLine().trim().split(" ");
                   rows++;
                   columns = 0;
                   for(int i = 0;i < line.length;i++) {
                         columns++;
                   }
               }
               
               int i = 0;
               Mat = new int[rows][columns];
               while(sc.hasNextLine())
               {
                   String[] line = sc.nextLine().trim().split(" ");
                   for(int j = 0;i < line.length;j++) {
                         Mat[i][j] = Integer.parseInt(line[j]);
                         System.out.print(Mat[i][j]);
                         System.out.print(" ");
                   }
                   
                   i++;
               }
               System.out.println();
               
               System.out.println(rows);
               System.out.println(columns);
               
               
               for(int k = 0;k < rows;i++) {
                    for(int j = 0;j < columns;j++) {
                         System.out.print(Mat[k][j]);
                         System.out.print(" ");
                    }
                    System.out.println();
               }
               
          }
          
          catch(Exception e) {
               System.out.println("Error in reading file...");
          }
          */
          
          // check if matrix is symmetric, then it is adjacent
          for(int i = 0;i < n;i++) {
               for(int j = i;j < n;j++) {
                    if(Mat[i][j] != Mat[j][i]) {
                         System.out.println("Cannot be an adjency matrix");
                         System.exit(1);
                    }
               }
          }
          
          int visited[] = new int[n];
          for(int i = 0;i < n;i++) visited[i] = 0;
          
          for(int u = 0;u < n;u++) {
               if(visited[u] == 1) continue;
               
               int flag = 0;
               for(int v = 0;v < n;v++) {
                    if(u == v) continue;
                    
                    if(visited[v] == 1) continue;
                    
                    if(Mat[u][v] == 1) {
                         visited[u] = 1;
                         visited[v] = 1;
                         
                         if(flag == 0) {
                              System.out.println(u);
                              System.out.println(v);
                              flag = 1;
                         }
                         break;
                   }
               }
          }
     }
}
