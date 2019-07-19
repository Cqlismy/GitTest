#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define LENGTH 100

int main(int argc, char *argv[])
{
    int fd,len;
    char str[LENGTH];

    fd = open("hello.txt", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd) {
        write(fd, "hello.txt", strlen("Hello World"));
        close(fd);
    }

    fd = open("hello.txt", O_RDWR);
    len = read(fd, str, LENGTH);
    str[len] = '\0';
    printf("str:%s\n", str);
    close(fd);
    
    return 0;
}
