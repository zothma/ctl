#include <libconfig.h>
#include <stdio.h>
#include <stdlib.h>

#include "config.h"

int main() {
    int result;
    config_t user_config;

    result = load_config(&user_config);
    if (result == CONFIG_NOT_FOUND) {
        printf("The config file could not be found");
    } else if (result == CONFIG_INACCESSIBLE) {
        printf("The config file could not be used");
    }

    return EXIT_SUCCESS;
}
