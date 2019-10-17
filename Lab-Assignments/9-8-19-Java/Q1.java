import java.util.Scanner; 

public class Q1 {
     public void printHW() {
          System.out.println("Hello World");
     }
     
     public void sumOfTenTerms(double x) {
          double sum = 0.0;
          double e = 2.71828;
          double t = Math.pow(e,x);
          for(int i = 1;i <= 10;i++) {
               int fact = 1;
               for(int j = i - 1;j >= 1;j--) {
                    fact *= j; // compute factorial
               }
               sum += (Math.pow(x,i - 1)/((double)fact));
          }
          
          System.out.print("e^x = ");
          System.out.println(sum);
     }
     
     public static int gcd(int a,int b) {
          if (a == 0) 
               return b; 
          if (b == 0) 
               return a; 
          
          if (a == b) 
               return a; 
    
          if (a > b) 
               return gcd(a-b, b); 
          return gcd(a, b-a); 
     }
     
     public void palindrome(String s) {
          String reversed = "";
          for (int i = s.length() - 1; i >= 0; i-- )
               reversed = reversed + s.charAt(i);
          
          int is_palindrome = 1;
          for(int i = 0;i < s.length();i++) {
               if(s.charAt(i) != reversed.charAt(i)) {
                    is_palindrome = 0;
                    break;
               }
          }
          
          if(is_palindrome == 1)
               System.out.println("Palindrome!");
          else
               System.out.println("Not A Palindrome!");
     }
     
     public boolean isPrime(int n) {
          for(int i = 2;i < n;i++) {
               if((n % i) == 0) return false;
          }
          return true;
     }
     
     public void primeTillN(int n) {
          System.out.println("Printing prime numbers till n");
          for(int i = 2;i <= n;i++) {
               if(isPrime(i)) System.out.println(i);
          }
     }
     
     public void relPrime(int n) {
          for(int i = 2;i <= n;i++) {
               if(gcd(n,i) == 1) System.out.println(i);
          }
     }
     
     public static void main(String[] args) {
          Scanner in = new Scanner(System.in);
          
          System.out.println("---Menu---");
          System.out.println("1.Print hello world");     
          System.out.println("2.Sum of first 10 terms of e^x");
          System.out.println("3.Check palindrome");
          System.out.println("4.Number of primes till n");
          System.out.println("5.Number of primes relative to n");
          System.out.print("Enter choice : ");
          
          int choice = in.nextInt();
          in.nextLine();
          
          Q1 q = new Q1();
          
          if(choice == 1) {
               q.printHW();
          }
          if(choice == 2) {
               System.out.print("Enter x : ");
               double x = in.nextDouble();
               q.sumOfTenTerms(x);
          }
          if(choice == 3) {
               System.out.print("Enter string : ");
               String s = in.nextLine();
               q.palindrome(s);
          }
          if(choice == 4) {
               System.out.print("Enter n : ");
               int n = in.nextInt();
               q.primeTillN(n);    
          }
          if(choice == 5) {
               System.out.print("Enter n : ");
               int n = in.nextInt();
               q.relPrime(n);
          }
     }
}
