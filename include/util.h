#ifndef CTL_UTIL_H
#define CTL_UTIL_H

#include <stdbool.h>

enum category { VOLUME, NONE };
typedef enum category category;

bool string_in_list(char *str, char *list, char *delimiter);
void execute_module(config_t *config, category cat, char *argv[]);

#endif