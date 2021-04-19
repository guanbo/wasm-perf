#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>

int main(int argc, char **argv) {
    ssize_t n, m;
    char buf[BUFSIZ*2];
	struct timeval start;
	struct timeval end;
	long int runtime = 0;
	float throughput = 0;
    int buffer_size = 64;

    if (argc != 3) {
        fprintf(stderr, "usage: %s file buffer_size\n", argv[0]);
        exit(1);
    }

    int in = open(argv[1], O_RDONLY);
    if (in < 0) {
        fprintf(stderr, "error opening input %s: %s\n", argv[1], strerror(errno));
        exit(1);
    }
    buffer_size = atoi(argv[2]);

    for (size_t i = 0; i < 10; i++)
    {
        n = read(in, buf, buffer_size);
        if (n < 0) {
            fprintf(stderr, "read error: %s\n", strerror(errno));
            exit(1);
        }
    }

	gettimeofday(&start,NULL);

    for (size_t i = 0; i < 100000; i++)
    {
        n = read(in, buf, buffer_size);
        if (n < 0) {
            fprintf(stderr, "read error: %s\n", strerror(errno));
            exit(1);
        }
    }
    
	gettimeofday(&end, NULL);
	
	runtime = 1000000 * (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec);
    throughput = (sizeof(buf) * 8000.0 / runtime);
    
    // printf("Size: %d(byte)\n", buffer_size);
	// printf("Time latency : %ld (us)\n", runtime);
    // printf("Throughput : %5.4lf Kbps\n", throughput);
    printf("%ld, %5.4lf\n", runtime, throughput);

    return EXIT_SUCCESS;
}