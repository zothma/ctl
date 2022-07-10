#ifndef CTL_CONFIG_H
#define CTL_CONFIG_H

#define CONFIG_PATH "/.config/ctl.conf"
#define CONFIG_NOT_FOUND -1
#define CONFIG_INACCESSIBLE -2

int load_config(config_t *conf);
void get_config(config_t *config, char *path, char **result);

#endif