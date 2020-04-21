#include <stdio.h>
#include <stdlib.h>

#define myrandom(x) (rand()%x)

int main(int argc, char *argv[])
{
	int j, r, nloops;
	unsigned int seed, range;

	if (argc != 4) {
		fprintf(stderr, "Usage: %s <seed> <nloops> <range>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	seed = atoi(argv[1]);
	nloops = atoi(argv[2]);
	range = atoi(argv[3]);

	srand(seed);
	for (j = 0; j < nloops; j++) {
		r = myrandom(range);
		printf("%d : %d\n", j, r);
	}

	exit(EXIT_SUCCESS);
}
