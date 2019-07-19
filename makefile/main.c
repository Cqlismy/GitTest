#include <stdio.h>
#include "a.h"

extern void fun2(void);
extern void fun3(void);

int main(int argc, char *argv[])
{
    fun2();
    fun3();
    printf("I am main.\n");
 
    return 0;
}
