#include "pokerCheck.h"

void tCardArrRankChecker(t_card *arr) {
    bool sameSuit = true;
    bool sequence = true;
    int combination1 = 1;
    int combination2 = 1;
    for (int i = 1; i < 5; ++i) {
        if (arr[0].suit != arr[i].suit)
            sameSuit = false;
    }
    for (int i = 0; i < 4; ++i) {
        if (arr[i].rank + 1 != arr[i + 1].rank)
            sequence = false;
    }
    if (arr[4].rank==14&&arr[0].rank==2) {
        sequence=true;
        for (int i = 0; i < 3; ++i) {
            if (arr[i].rank + 1 != arr[i + 1].rank)
                sequence = false;
        }
    }
    if (arr[0].rank == 10 && sameSuit && sequence) {
        mx_printstr("Royal flush\n");
        return;
    } else if (sameSuit && sequence) {
        mx_printstr("Straight flush\n");
        return;
    } else if (sameSuit) {
        mx_printstr("Flush\n");
        return;
    } else if (sequence) {
        mx_printstr("Straight\n");
        return;
    }
    int i = -1;
    while (combination1 == 1 && i < 4) {
        i++;
        int j = i + 1;
        while (arr[i].rank == arr[j].rank && j < 5) {
            combination1++;
            j++;
        }
    }
    if (combination1 != 1 && i + combination1 < 4) {
        i += combination1;
        i--;
        while (combination2 == 1 && i < 4) {
            i++;
            int j = i + 1;
            while (arr[i].rank == arr[j].rank && j < 5) {
                combination2++;
                j++;
            }
        }
    }
    if (combination1 == 4) {
        mx_printstr("Four of a kind\n");
        return;
    } else if (combination1*combination2 == 6) {
        mx_printstr("Full house\n");
        return;
    } else if (combination1 * combination2 == 4) {
        mx_printstr("Two pair\n");
        return;
    } else if (combination1 == 3) {
        mx_printstr("Three of a kind\n");
        return;
    } else if (combination1 == 2) {
        mx_printstr("One pair\n");
        return;
    }
    mx_printstr("No pair\n");
}

t_card *tCardArr(char **argv) {
    t_card *arr = (t_card *) malloc(5 * sizeof(t_card));
    for (int i = 1; i < 6; ++i) {
        if (argv[i][0] == '1' && argv[i][1] == '0')
            arr[i - 1].rank = 10;
        else if (mx_isDigRank(argv[i][0]))
            arr[i - 1].rank = argv[i][0] - '0';
        else if (argv[i][0] == 'J')
            arr[i - 1].rank = 11;
        else if (argv[i][0] == 'Q')
            arr[i - 1].rank = 12;
        else if (argv[i][0] == 'K')
            arr[i - 1].rank = 13;
        else if (argv[i][0] == 'A')
            arr[i - 1].rank = 14;
        if (arr[i - 1].rank == 10)
            arr[i - 1].suit = argv[i][2];
        else
            arr[i - 1].suit = argv[i][1];
    }
    t_card tmp;
    for (int R = 4; R > 0; R--) {
        for (int i = 0; i < R; i++)
            if (arr[i].rank > arr[i + 1].rank) {
                tmp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = tmp;
            }
    }
    return arr;
}

bool checkIn(int argc, char **argv) {
    if (argc != 6) {
        mx_printerr("usage: ./race03 [card1] [card2] [card3] [card4] "
                    "[card5]\n");
        return false;
    }
    for (int i = 1; i < 5; ++i) {
        for (int j = i + 1; j < 6; ++j) {
            if (mx_strcmp(argv[i], argv[j]) == 0) {
                mx_printerr("Duplicate cards: ");
                mx_printerr(argv[i]);
                mx_printerr("\n");
                return false;
            }
        }
    }
    bool errSuit = false;
    bool errRank = false;
    char *errSuitChar = NULL;
    char *errRankChar = NULL;
    for (int i = 1; i < 6; ++i) {
        bool badRank = false;
        bool badSuit = false;
        int len = mx_strlen(argv[i]);
        if (len < 2) {
            mx_printerr("Invalid card: ");
            mx_printerr(argv[i]);
            mx_printerr("\n");
            return false;
        }
        int rankLen = 0;
        if (argv[i][0] == '1' && argv[i][1] == '0') {
            rankLen = 2;
        }
        if (rankLen == 0) {
            for (int j = 0; mx_isDigRank(argv[i][j]); ++j) {
                rankLen++;
            }
        }
        if (rankLen == 0) {
            for (int j = 0; mx_isAlphRank(argv[i][j]); ++j) {
                rankLen++;
            }
        }
        if (rankLen == 0 || rankLen > 2)
            badRank = true;
        if (rankLen == 2 && argv[i][0] != '1' && argv[i][1] != '0')
            badRank = true;
        int suitLen = 0;
        for (int j = rankLen; mx_isSuit(argv[i][j]); ++j) {
            suitLen++;
        }
        if (suitLen != 1)
            badSuit = true;
        if (suitLen + rankLen != len)
            badSuit = true;
        if (badSuit && badRank) {
            mx_printerr("Invalid card: ");
            mx_printerr(argv[i]);
            mx_printerr("\n");
            return false;
        }
        if (badRank && !errRank) {
            argv[i][rankLen] = '\0';
            errRankChar = argv[i];
            errRank = true;
        }
        if (badSuit && !errSuit) {
            errSuitChar = argv[i] + rankLen;
            errSuit = true;
        }
    }
    if (errSuit) {
        mx_printerr("Invalid card suit: ");
        mx_printerr(errSuitChar);
        mx_printerr("\n");
        return false;
    }
    if (errRank) {
        mx_printerr("Invalid card rank: ");
        mx_printerr(errRankChar);
        mx_printerr("\n");
        return false;
    }
    return true;
}

bool mx_isSuit(char c) {
    return c == 'H' || c == 'C' || c == 'S' || c == 'D';
}

bool mx_isDigRank(int c) {
    return (c >= '2' && c <= '9');
}

bool mx_isAlphRank(int c) {
    return c == 'J' || c == 'Q' || c == 'K' || c == 'A';
}
