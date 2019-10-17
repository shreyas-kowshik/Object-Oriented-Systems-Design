// Server code in C to sort the array 
#include <arpa/inet.h> 
#include <stdio.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <unistd.h> 
#include <bits/stdc++.h>

using namespace std;
void bubble_sort(int[], int); 

// Driver code 
int main(int argc, char* argv[]) 
{ 
	int socket_desc, client_sock, c, read_size; 
	struct sockaddr_in server, client; 
	
	int N; // number of elements in the array
	int message[10], i;
	int *arr;// array to sort 

	// Create socket 
	socket_desc = socket(AF_INET, SOCK_STREAM, 0); 
	if (socket_desc == -1) { 
		printf("Could not create socket"); 
	} 
	puts("Socket created"); 

	// Prepare the sockaddr_in structure 
	server.sin_family = AF_INET; 
	server.sin_addr.s_addr = INADDR_ANY; 
	server.sin_port = htons(8881); 

	// Bind the socket 
	if (bind(socket_desc, (struct sockaddr*)&server, sizeof(server)) < 0) { 

		// print the error message 
		perror("bind failed. Error"); 
		return 1; 
	} 
	puts("bind done"); 

	// lsiten to the socket 
	listen(socket_desc, 3); 

	puts("Waiting for incoming connections..."); 
	c = sizeof(struct sockaddr_in); 

	// accept connection from an incoming client 
	client_sock = accept(socket_desc, (struct sockaddr*)&client, (socklen_t*)&c); 

	if (client_sock < 0) { 
		perror("accept failed"); 
		return 1; 
	} 

	puts("Connection accepted"); 
     // Connection Done!
     
     bool first_msg = true;
     int index = 0;
	// Receive a message from client 
	while ((read_size = recv(client_sock, &message, sizeof(int), 0)) > 0) { 
          if (first_msg) {
               cout << message[0] << endl;
               N = message[0];
               arr = (int *)malloc(N * sizeof(int));
               first_msg = false;
               index = 0;
          }
          else {
               
               arr[index] = message[0];
               index++;
          }
          if(index == N) break;
	} 
     // All elements have been received in the array
     bubble_sort(arr, N);
     
	write(client_sock, arr, N * sizeof(int)); 
	
	if (read_size == 0) { 
		puts("Client disconnected"); 
	} 
	else if (read_size == -1) { 
		perror("recv failed"); 
	} 

	return 0; 
} 

// Function to sort the array 
void bubble_sort(int list[], int n) 
{ 
	int c, d, t; 

	for (c = 0; c < (n - 1); c++) { 
		for (d = 0; d < n - c - 1; d++) { 
			if (list[d] > list[d + 1]) { 

				/* Swapping */
				t = list[d]; 
				list[d] = list[d + 1]; 
				list[d + 1] = t; 
			} 
		} 
	} 
} 

