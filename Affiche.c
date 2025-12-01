#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main (int argc, char **argv) {

    int n = atoi(argv[1]);

    while (n > 0)
    {
        printf("%s\n", argv[2]);
        sleep(1);
        n--;
    }
    return 0;

}