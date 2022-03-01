#ifndef _USER_SOLVE_H_
#define _USER_SOLVE_H_
#include"common_function.h"

void diy(int check[3][3]);
void confirm_change(int check[3][3]);
void move(int table[3][3],int *pter,int right_state[3][3]);
void movemyself(int table[3][3],int right_state[3][3]);
int confirm_solve(char query);

#endif