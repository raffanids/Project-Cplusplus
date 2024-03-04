#include "randomNumber.h"

#include <ctime>

// don't forget to set srand(time(0));

int randomNumber(int max) // generating random nunber in range of [1 - (int) max]
{
    int n = (rand() % max) + 1;
    return n;
}

int rollDice()
{
    int dice1, dice2;
    dice1 = randomNumber(6);
    dice2 = randomNumber(6);

    return dice1 + dice2;
}

