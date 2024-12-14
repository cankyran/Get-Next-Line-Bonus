#include <stdio.h>
#include "get_next_line.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int fd = open("1char.txt", O_RDONLY);
    close(fd);
    char *str = get_next_line(fd);
    printf("SELAM: %s\n", str);
    free(str);
    str = get_next_line(fd);
    if (str)
        printf("SELAM VAR %s\n", str);
    else
        printf("SELAM YOk");
}