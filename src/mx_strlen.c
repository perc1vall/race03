#include "pokerCheck.h"

int mx_strlen(const char *s) {
    if (s == NULL)
        return 0;
    char *tmp = (char *) s;
    while (*tmp) tmp++;
    return (int) (tmp - s);
}
