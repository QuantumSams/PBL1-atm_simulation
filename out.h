#ifndef OUT_H_
#define OUT_H_

int getIndex(int acc[], int size, int x);
void swap(int *a, int *b);
int reCheck(char * prompt, int * valid);
void verify(int acc[], int pass[], int balance[], int size);
void access_menu(int acc[], int pass[], int balance[], int index, int size);
#endif