#include <stdio.h>

typedef struct pNode pNode;

struct pNode {
	int num;
	pNode *pNext;
};

int main(int argc, char *argv[])
{
	pNode first,second;
	
	first.num = 1;
	first.pNext = &second;

	second.num = 2;
	second.pNext = NULL;

	printf("first.num = %d\n", first.num);
	printf("second.num = %d\n", (first.pNext)->num);

	return 0;
}
