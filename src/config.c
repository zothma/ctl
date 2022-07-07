#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>

#include "config.h"

int get_config(config *result)
{
    // First, get the config file name and check if it exists
    char *homedir, *confpath;
    if ((homedir = getenv("HOME")) == NULL)
    {
        homedir = getpwuid(getuid())->pw_dir;
    }

    confpath = malloc(sizeof(char) * (strlen(CONFIG_PATH) + strlen(homedir) + 1));
    strcpy(confpath, homedir);
    strcat(confpath, CONFIG_PATH);

    if (access(confpath, F_OK) != 0)
    {
        free(confpath);
        return CONFIG_NOT_FOUND;
    }

    result = malloc(sizeof(config));

    free(confpath);
    return 0;
}