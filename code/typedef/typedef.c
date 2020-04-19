#include <stdio.h>
#include <string.h>

typedef char String[20];

int main(int argc, char *argv[])
{
	String str1;

	memcpy(str1, "Hello World.", strlen("Hello World."));

	printf("str1 = %s\n", str1);

	return 0;
}
