#include <libconfig.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>

#include "config.h"

void usage(char *progname, FILE *stream) {
    fprintf(stream, "Usage : %s <category> <option> [<value>]\n", progname);
    fprintf(stream, "        %s (-h | --help)\n\n", progname);
    fprintf(stream, "Possible categories :\n");
    fprintf(stream, "    v, volume [up | down]\n");
}

int main(int argc, char *argv[]) {
    int result;
    config_t user_config;

    // Check the user options
    if (argc == 1) {
        usage(basename(argv[0]), stderr);
    }

    result = load_config(&user_config);
    if (result == CONFIG_NOT_FOUND) {
        printf("The config file could not be found");
    } else if (result == CONFIG_INACCESSIBLE) {
        printf("The config file could not be used");
    }

    return EXIT_SUCCESS;
}
