#include <stdio.h>

#define LENGTH 100

int main(int argc, char *argv[])
{
    FILE *fd;
    char str[LENGTH];
    
    fd = open("hello.txt", "w+");
    if (fd) {
        fputs("hello.txt", fd);
        fclose(fd);
    }
    
    fgets(str, LENGTH, fd);
    printf("str:%s\n", str);
    fclose(fd);

    return 0;
}
