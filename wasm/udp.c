/**
 * Copyright 2021 AutoCore
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h> //for bzero()
#include <unistd.h> //for close()
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <arpa/inet.h>

int main(int argc, char const *argv[])
{
	int sock, byte_sent, byte_recv;
	struct timeval start;
	struct timeval end;
	long int runtime = 0;
	float throughput = 0;
	char buffer[100] = "abc123";

  if (argc != 2) {
      fprintf(stderr, "usage: %s socket_fd\n", argv[0]);
      exit(1);
  }

  printf("====%s\n", argv[1]);
  sock = atoi(argv[1]);fileno();open();

  gettimeofday(&start,NULL);
	
  byte_sent = send(sock, buffer, sizeof(buffer), 0);
	if (byte_sent < 0)
    perror("socket error====\n");
		// printf("Error sending packet: %d\n", byte_sent);
	
	byte_recv = recv(sock, buffer, sizeof(buffer), 0);
	printf("%s\n",buffer);
	
	if (byte_recv < 0)
		printf("Receive Failed: %d\n",byte_recv);
	
	gettimeofday(&end, NULL);
	
	runtime = 1000000 * (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec);
  throughput = (sizeof(buffer) * 8000.0 / runtime);
    
	printf("Time latency : %ld (us)\n", runtime);
  printf("Throughput : %5.4lf Kbps\n", throughput);

  return 0;
}
