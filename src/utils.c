#include <stdio.h>
#include <stdlib.h>

void error(char *str)
{
    dprintf(2, "%s\n", str);
    exit(1);
}