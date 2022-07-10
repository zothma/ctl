#ifndef CTL_MODULES_H
#define CTL_MODULES_H

#include <libconfig.h>

int volume_module_execute_action(config_t *config, char *action);
int brightness_module_execute_action(config_t *config, char *action);

#endif