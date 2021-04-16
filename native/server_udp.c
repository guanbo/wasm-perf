#include <stdlib.h>
#include <stdio.h>
#include <string.h> //for bzero()
#include <unistd.h> //for close()
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#define PortNumber 5555


int main(int argc, char **argv)
{
	struct sockaddr_in address;

    int sock, byte_recv, byte_sent;
    char buffer[50];
    socklen_t address_length = sizeof(address);
    
    sock = socket(PF_INET, SOCK_DGRAM, 0);

    if (sock < 0)
    {
	   printf("Error creating socket\n");
    }
    
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(PortNumber);
    address.sin_addr.s_addr = INADDR_ANY;
    
    printf("This is Server.\n");
    if(bind(sock, (struct sockaddr*)&address, sizeof(address)) == -1)
    {
	    printf("Bind error!\n");
		close(sock);
	}

	while (1)
	{
        byte_recv = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr*)&address, &address_length);
            
        if(byte_recv < 0)
            printf("Error recving packet\n");
            
        printf("%s\n", buffer);
            
        char buffer2[50] = "Welcome!";
        byte_sent = sendto(sock, buffer2, sizeof(buffer2), 0, (struct sockaddr *)&address, address_length);
        
        if (byte_sent < 0)
            printf("Error sending packet\n");
            
        printf("Client send completed.\n");
	}	
    
	close(sock);
	return 0;
}

