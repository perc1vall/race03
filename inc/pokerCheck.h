#ifndef RACE03_POKERCHECK_H
#define RACE03_POKERCHECK_H

#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_card {
    int rank;
    char suit;
} t_card;

void tCardArrRankChecker(t_card *arr);

t_card *tCardArr(char **argv);

int mx_strcmp(const char *s1, const char *s2);

void mx_printerr(const char *s);

bool mx_isDigRank(int c);

bool mx_isAlphRank(int c);

bool mx_isSuit(char c);

int mx_strlen(const char *s);

void mx_printstr(const char *s);

bool checkIn(int argc, char **argv);

#endif
