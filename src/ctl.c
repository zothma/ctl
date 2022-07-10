#include <libconfig.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "config.h"
#include "util.h"

void usage(const char *progname, FILE *stream);
category detect_category(char *user_param);
void parse_arguments(int argc, char *argv[], category *cat);

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
    category category_list[] = {VOLUME};
    category result = NONE;

    for (int i = 0; i < NB_CATEGORY; i++) {
        if (string_in_list(user_param, category_names[i], ":"))
            result = category_list[i];
    }

    return result;
}

void parse_arguments(int argc, char *argv[], category *cat) {
    const char *progname = basename(argv[0]);
    bool valid_option;

    if (argc == 1) {
        usage(progname, stderr);
        exit(EXIT_FAILURE);
    }

    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        usage(progname, stdout);
        exit(EXIT_SUCCESS);
    }

    *cat = detect_category(argv[1]);
    if (argc == 2 && *cat != NONE) {
        fprintf(stderr, "Missing option for category '%s'. Use -h to get help\n", argv[1]);
        exit(EXIT_FAILURE);
    }


    switch (*cat) {
    case VOLUME:
        char volume_options[] = "up:down";
        valid_option = string_in_list(argv[2], volume_options, ":");
        break;

    default:
        fprintf(stderr, "Unrecognized category '%s'. Use -h to get help\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    if (!valid_option) {
        fprintf(stderr, "Unrecognized option '%s' for category '%s'. Use -h to get help\n", argv[2], argv[1]);
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    int result;
    config_t user_config;
    category cat = NONE;

    parse_arguments(argc, argv, &cat);

    result = load_config(&user_config);
    if (result == CONFIG_NOT_FOUND) {
        printf("The config file could not be found");
    } else if (result == CONFIG_INACCESSIBLE) {
        printf("The config file could not be used");
    }

    execute_module(&user_config, cat, argv);

    return EXIT_SUCCESS;
}
