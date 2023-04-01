#include <stdio.h>
#include "out.h"
#include <regex.h>
#include <stdlib.h>
#define MAX_STR 100

int getIndex(int acc[], int size, int x)
{
    for(int i = 0; i <= size; i++)
    {
        if (x == acc[i]) return i;
    }
    return -1;
}

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
    return;
}


void verify(int acc[], int pass[], int balance[], int size) 
{
    int validAcc, index = -1, validPass;

    while(1)
    {
        if (reCheck("Please enter your banking account: ", &validAcc))
        {
            index = getIndex(acc, size, validAcc);
            reCheck("Please enter your password: ", &validPass);
            if (index != -1 && validPass == pass[index]) break;
        }
        printf("Not valid, please try again\n");
    }

    printf("You have successfully granted access to your banking account!\n");
    access_menu(acc, pass, balance, index, size);
}

int reCheck(char * prompt, int * valid)
{
    char inputString[MAX_STR];
    printf("%s", prompt); scanf("%s", inputString);

    regex_t num;
    regcomp(&num, "^[:digit:]+$", 0);

    if (regexec(&num, inputString, 0, NULL, 0))
    {
        *valid = atoi(inputString);
        return 1;
    }
    return 0;
}

void access_menu(int acc[], int pass[], int balance[], int index, int size)
{
    printf("   WELCOME, ACCOUNT #%i\n", acc[index]);
    printf("Press the number corresponding to each service below:\n");
    printf("1. Withdraw from your balance\n");
    printf("2. Deposit to your balance\n");
    printf("3. View your infomation\n");
    printf("0. Terminate session\n");

    char option;
    while(1)
    {
        scanf("%c", &option);
        if ((int)option >= 0 && option <= 3) break;
        printf("Invalid input! Try again\n");
    }

    switch(option)
    {
        case 0: verify(acc, pass, balance, size); break;
        case 1: break;
        case 2: break;
        case 3: 
            printf("Account number: %i | Remaining balance: %i\n", acc[index], balance[index]);
            access_menu(acc, pass, balance, index, size);
            break;
    }
    return;
}