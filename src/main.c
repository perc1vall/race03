#include <stdio.h>
#include "pokerCheck.h"

int main(int argc, char **argv) {
    if (!checkIn(argc, argv))
        return 0;
    t_card *arr = tCardArr(argv);
    tCardArrRankChecker(arr);
    return 0;
}
