#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define myrandom(x) (rand()%x)

int main(int argc, char *argv[])
{
	int i;

	srand(time(0));

	for (i = 0; i < 10; i++)
		printf("%d : %d\n", i, myrandom(1000));

	exit(EXIT_SUCCESS);
}
