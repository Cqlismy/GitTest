#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
	int i;

	srand((int)time(0));

	for (i = 0; i < 10; i++)
		printf("%d : %d\n", i, rand());
	
	exit(EXIT_SUCCESS);
}
