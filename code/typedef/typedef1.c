#include <stdio.h>

typedef int Num[];

int main(int argc, char *argv[])
{
	Num n = {1, 2, 3};
	Num m = {1, 2, 3, 4};
	int i;

	for(i = 0; i < 3; i++)
		printf("n[%d] = %d\n", i, n[i]);
	
	for(i = 0; i < 4; i++)
		printf("m[%d] = %d\n", i, m[i]);

	return 0;
}
