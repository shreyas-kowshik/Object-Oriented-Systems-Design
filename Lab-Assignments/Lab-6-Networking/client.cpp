// Client code in C to sort the array 
#include <arpa/inet.h> 
#include <stdio.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <unistd.h> 
#include <bits/stdc++.h>

using namespace std;

int N;
// Driver code 
int main(int argc, char* argv[]) 
{ 
	int sock; 
	struct sockaddr_in server; 
	
	int i, temp; 
	
     
	// Create socket 
	sock = socket(AF_INET, SOCK_STREAM, 0); 
	if (sock == -1) { 
		printf("Could not create socket"); 
	} 
	puts("Socket created"); 

	server.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	server.sin_family = AF_INET; 
	server.sin_port = htons(8881); 

	// Connect to remote server 
	if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0) { 
		perror("connect failed. Error"); 
		return 1; 
	} 

	puts("Connected\n"); 
     // Connection Done!
     
     cout<< "Enter number of elements in array : ";
	cin >> N;
	int number[N];
	int server_reply[N]; 
	int result = send(sock, &N, sizeof(int), 0); // send N over to the server
	if(result < 0) {
	     cout << "Failed to send message..." << endl;
	     exit(0);
	}
	for(int t = 0;t < N;t++) {
          cout << "Enter a[" << t << "] : ";
          cin >> number[t];
          int msg = number[t];
          int result = send(sock, &msg, sizeof(int), 0);
          if(result < 0) {
               cout << "Failed to send message..." << endl;
               exit(0);
          }
	}
	cout << "CLIENT OUT " << endl;
	
	// Receive a reply from the server 
	if (recv(sock, &server_reply, N * sizeof(int), 0) < 0) { 
		puts("recv failed"); 
		return 0; 
	} 

	puts("Sorted array received from the server :\n");
	for (i = 0; i < N; i++) { 
		printf("%d\n", server_reply[i]); 
	} 

	// close the socket 
	close(sock); 
	return 0; 
} 

