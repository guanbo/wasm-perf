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
	int sock;
	char str[10];

	sock = socket(PF_INET, SOCK_DGRAM, 0);
	if (sock < 0)   
	{
			printf("Error creating socket\n");
	}
	
	bzero(&address, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(Server_PortNumber);
	address.sin_addr.s_addr = inet_addr(Server_Address);
	
	snprintf(str, sizeof(str), "%d", sock);
	printf("socket fd: %s\n", str);

	// char *args[]={"/Users/guanbo/repo/wasm-micro-runtime/product-mini/platforms/darwin/build/iwasm", "/Users/guanbo/repo/wasm-perf/wasm/udp.wasm", str, NULL};
	// execvp(args[0], args);
	while (1)
	{
		sleep(3);
	}
    
	return 0;
}

