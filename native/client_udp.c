#include <stdlib.h>
#include <stdio.h>
#include <string.h> //for bzero()
#include <unistd.h> //for close()
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <arpa/inet.h>
#define Server_PortNumber 5555
#define Server_Address "127.0.0.1"


int main(int argc, char **argv)
{
	struct sockaddr_in address;
	int sock, byte_sent, byte_recv;
	struct timeval start;
	struct timeval end;
	long int runtime = 0;
	float throughput = 0;
	char buffer[100];
	printf("This is Client. Please input string:\n");
	fgets(buffer, sizeof buffer, stdin);
	sock = socket(PF_INET, SOCK_DGRAM, 0);
	if (sock < 0)   
	{
			printf("Error creating socket\n");
	}
	
	bzero(&address, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(Server_PortNumber);
	address.sin_addr.s_addr = inet_addr(Server_Address);
	
	socklen_t address_length = sizeof(address);
	
	gettimeofday(&start,NULL);
	
	byte_sent = sendto(sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&address, address_length);

	if (byte_sent < 0)
		printf("Error sending packet\n");
	
	byte_recv = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr*)&address, &address_length);
	printf("%s\n",buffer);
	
	if (byte_recv < 0)
		printf("Receive Failed\n");
	
	gettimeofday(&end, NULL);
	
	runtime = 1000000 * (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec);
    throughput = (sizeof(buffer) * 8000.0 / runtime);
    
	printf("Server IP: %s\n", Server_Address);
	printf("Time latency : %ld (us)\n", runtime);
    printf("Throughput : %5.4lf Kbps\n", throughput);
    
	close(sock);
	return 0;
}

