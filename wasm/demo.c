#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>

int main(int argc, char **argv) {
    ssize_t n, m;
    char buf[BUFSIZ];
	struct timeval start;
	struct timeval end;
	long int runtime = 0;
	float throughput = 0;

    if (argc != 2) {
        fprintf(stderr, "usage: %s file\n", argv[0]);
        exit(1);
    }

	gettimeofday(&start,NULL);

    int in = open(argv[1], O_RDONLY);
    if (in < 0) {
        fprintf(stderr, "error opening input %s: %s\n", argv[1], strerror(errno));
        exit(1);
    }

    while ((n = read(in, buf, BUFSIZ)) > 0) {
    }

    if (n < 0) {
        fprintf(stderr, "read error: %s\n", strerror(errno));
        exit(1);
    }
	gettimeofday(&end, NULL);
	
	runtime = 1000000 * (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec);
    throughput = (sizeof(buf) * 8000.0 / runtime);
    
	printf("Time latency : %ld (us)\n", runtime);
    printf("Throughput : %5.4lf Kbps\n", throughput);

    return EXIT_SUCCESS;
}