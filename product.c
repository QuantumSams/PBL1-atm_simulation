#include <stdio.h>
#include "out.h"

void ATM(void);

int main(void)
{
    ATM();
}

void ATM(void)
{
    int acc[] = {33, 22, 11, 88, 99};
    int pass[] = {98, 87, 10, 21, 32};
    int balance[] = {1, 0, 2, 4, 5};
    int size = (sizeof(acc) / sizeof(acc[0]));

    verify(acc, pass, balance, size - 1);
}