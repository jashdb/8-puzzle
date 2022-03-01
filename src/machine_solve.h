#ifndef _MACHINE_SOLVE_H_
#define _MACHINE_SOLVE_H_
#include"common_function.h"

state makeSubTree(state a, state root,int right_state[3][3],state Xmin,int* stop);
state makeTree(state root,int right_state[3][3]);
void road(state min,int right_state[3][3]);
#endif