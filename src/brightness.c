#include <stdlib.h>
#include <libconfig.h>
#include <string.h>

#include "config.h"
#include "modules.h"

int brightness_module_execute_action(config_t *config, char *action) {
    char *command;

    if (strcmp(action, "up") == 0) {
        get_config(config, "brightness_up", &command);
    } else if (strcmp(action, "down") == 0) {
        get_config(config, "brightness_down", &command);
    } else {
        return EXIT_FAILURE;
    }

    system(command);
    return EXIT_SUCCESS;
}