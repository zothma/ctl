#include <stdio.h>
#include <stdlib.h>

#include "config.h"

int main()
{
    config global_conf;
    get_config(&global_conf);

    free(&global_conf);
    return EXIT_SUCCESS;
}
