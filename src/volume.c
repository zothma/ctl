#include <stdlib.h>
#include <libconfig.h>
#include <string.h>

#include "config.h"
#include "modules.h"

int volume_module_execute_action(config_t *config, char *action) {
    // char *command = malloc(sizeof(char*));
    // char **command = malloc(sizeof(char**));
    char *command;

    if (strcmp(action, "up") == 0) {
        get_config(config, "volume_up", &command);
    } else if (strcmp(action, "down") == 0) {
        get_config(config, "volume_down", &command);
    } else {
        return EXIT_FAILURE;
    }

    system(command);
    return EXIT_SUCCESS;
}