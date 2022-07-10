#include <libconfig.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"

enum category { VOLUME, NONE };
typedef enum category category;

void usage(const char *progname, FILE *stream);
category detect_category(char *user_param);
void parse_arguments(int argc, char *argv[]);

void usage(const char *progname, FILE *stream) {
    fprintf(stream, "Usage : %s <category> <option> [<value>]\n", progname);
    fprintf(stream, "        %s (-h | --help)\n\n", progname);
    fprintf(stream, "Possible categories :\n");
    fprintf(stream, "    v, volume [up | down]\n");
}

category detect_category(char *user_param) {
    // Checks what category_name refers to
    const int NB_CATEGORY = 1;
    char category_names[][20] = {"v:volume"};
    char *current_name;
    category category_list[] = {VOLUME};
    category result = NONE;

    for (int i = 0; i < NB_CATEGORY; i++) {
        // We compare category_name to each existing category name (separated by
        // ':') until we find the corresponding one
        current_name = strtok(category_names[i], ":");

        do {
            if (strcmp(current_name, user_param) == 0)
                result = category_list[i];

            current_name = strtok(NULL, ":");
        } while (current_name != NULL && result == NONE);
    }

    return result;
}

void parse_arguments(int argc, char *argv[]) {
    const char *progname = basename(argv[0]);
    category cat;

    if (argc == 1) {
        usage(progname, stderr);
        exit(EXIT_FAILURE);
    }

    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        usage(progname, stdout);
        exit(EXIT_SUCCESS);
    }

    cat = detect_category(argv[1]);
}

int main(int argc, char *argv[]) {
    int result;
    config_t user_config;

    parse_arguments(argc, argv);

    result = load_config(&user_config);
    if (result == CONFIG_NOT_FOUND) {
        printf("The config file could not be found");
    } else if (result == CONFIG_INACCESSIBLE) {
        printf("The config file could not be used");
    }

    return EXIT_SUCCESS;
}
