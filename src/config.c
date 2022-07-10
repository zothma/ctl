#include <libconfig.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "config.h"

int load_config(config_t *result) {
    char *homedir, *confpath;
    FILE *conffile;

    // Get the config file name and check if it exists
    if ((homedir = getenv("HOME")) == NULL) {
        homedir = getpwuid(getuid())->pw_dir;
    }

    const int CONFPATH_LENGTH = strlen(CONFIG_PATH) + strlen(homedir) + 1;
    confpath = malloc(sizeof(char) * (CONFPATH_LENGTH));
    strcpy(confpath, homedir);
    strcat(confpath, CONFIG_PATH);

    if (access(confpath, F_OK) != 0) {
        free(confpath);
        return CONFIG_NOT_FOUND;
    }

    // Try and open the config file
    conffile = fopen(confpath, "r");
    if (conffile == NULL) {
        free(confpath);
        return CONFIG_INACCESSIBLE;
    }

    // Loading the configuration
    config_init(result);
    config_read(result, conffile);

    free(confpath);
    fclose(conffile);
    return EXIT_SUCCESS;
}