#include "pokerCheck.h"

int mx_strcmp(const char *s1, const char *s2) {
    if (s1 == NULL || s2 == NULL)
        return 0;
    char *tmps1 = (char *) s1;
    char *tmps2 = (char *) s2;
    while (*tmps1 && *tmps2 && *tmps1 == *tmps2) {
        tmps1++;
        tmps2++;
    }
    return *tmps1 - *tmps2;
}
