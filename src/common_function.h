#ifndef _COMMON_FUNCTION_H_
#define _COMMON_FUNCTION_H_
#define MAX 30
#define SOCONMAX 4

typedef struct _state_type{
    int table[3][3];
    int X,t;
    struct _state_type* con[3];
    struct _state_type *cha;
} state_type;

typedef state_type* state;

typedef struct _move_type{//Cấu trúc lưu trữ thông tin về ô có thể di chuyển: số trong ô, tọa độ (x,y) và deltaS
    int x,y;
    int tile;
    int deltaS;
} move_type;

void swap(int *x, int* y);
int isdup(int check[9], int n);
int isdupstate(int a[3][3],int b[3][3]);
void equal(int puzzle[3][3],int check [3][3]);

state createNode(int a[3][3]);
void giaiphong(state node);
int isfather(state father,state son);

void randomize(int puzzle[3][3]);
int isok(int puzzle[3][3]);
void vebang(int puzzle[3][3]);
#endif