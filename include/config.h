#ifndef CTL_CONFIG_H
#define CTL_CONFIG_H

#define CONFIG_PATH "/.config/ctl.conf"
#define CONFIG_NOT_FOUND -1

typedef struct
{
    // volume
    char *cmd_volume_up;
    char *cmd_volume_down;
    char *cmd_volume_get;
} config;

int get_config(config *conf);

#endif