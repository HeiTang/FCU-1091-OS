#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 4444
#define IP_ADDRESS "127.0.0.1"

int main(){

	int clientSocket, checkConnect;
	struct sockaddr_in serverAddr;
	char buffer[1024];

	/*create socket*/
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(clientSocket < 0){
		printf("[-]Error in creating Client Socket.\n");
		exit(1);
	}
	printf("[+]Client Socket is created.\n");
	/*create socket*/

	memset(&serverAddr, '\0', sizeof(serverAddr));//initial

	/*set serversocket struct IPv4, Port, Ip ...*/
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr(IP_ADDRESS);
	/*set serversocket struct IPv4, Port, Ip ...*/

	/*connect*/
	checkConnect = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(checkConnect < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Connected to Server.\n");
	/*connect*/

	while(1){
		printf("Client : ");
		scanf("%s", &buffer[0]);
		/*send data to server*/
		send(clientSocket, buffer, strlen(buffer),0);
		/*send data to server*/
		if(strcmp(buffer, ":exit") == 0){
			close(clientSocket);
			printf("[-]Disconnected from server.\n");
			exit(1);
		}

		if(recv(clientSocket, buffer, 1024, 0) < 0){
			printf("[-]Error in receiving data.\n");
		}else{
			printf("Server : %s\n", buffer);
		}
	}

	return 0;
}
