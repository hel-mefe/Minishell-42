#include "parsing.h"

void    get_err(char *err, int is_exit)
{
    size_t  i;

    i = -1;
    while (err[++i])
        write(2, &err[i], 1);
    if (is_exit)
        exit(EXIT_FAILURE);
}