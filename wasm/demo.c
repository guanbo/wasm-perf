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

	gettimeofday(&start,NULL);

    int in = open(argv[1], O_RDONLY);
    if (in < 0) {
        fprintf(stderr, "error opening input %s: %s\n", argv[1], strerror(errno));
        exit(1);
    }

    for (size_t i = 0; i < 100000; i++)
    {
        n = read(in, buf, BUFSIZ);
        if (n < 0) {
            fprintf(stderr, "read error: %s\n", strerror(errno));
            exit(1);
        }
    }
    
	gettimeofday(&end, NULL);
	
	runtime = 1000000 * (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec);
    throughput = (sizeof(buf) * 8000.0 / runtime);
    
	printf("Time latency : %ld (us)\n", runtime);
    printf("Throughput : %5.4lf Kbps\n", throughput);

    return EXIT_SUCCESS;
}