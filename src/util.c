#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

bool string_in_list(char *str, char *list, char *delimiter) {
    char *current_element;
    bool result = false;

    current_element = strtok(list, ":");
    do {
        if (strcmp(str, current_element) == 0)
            result = true;

        current_element = strtok(NULL, ":");
    } while (current_element != NULL && !result);

    return result;
}