#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include"common_function.h"

void swap(int *x, int* y){
    int z=*x;
    *x=*y;
    *y=z;
}

//Kiểm tra nếu chuỗi check đã có vị trí trước n trùng giá trị phần tử check[n] hay không
int isdup(int check[9], int n){
    for(int i=0;i<n;i++){
        if (check[i]=check[n]) return 1;
    }
    return 0;
}

int isdupstate(int a[3][3],int b[3][3]){
    int count=0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(a[i][j]==b[i][j]) count+=1;
        }
    }
    if(count==9) return 1;
    else return 0;
}

void equal(int puzzle[3][3],int check [3][3]){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            puzzle[i][j]=check[i][j];
        }
    }
}

state createNode(int a[3][3]){
    state newNode=(state)malloc(sizeof(state_type));
    equal(newNode->table,a);
    newNode->X=0;
    newNode->t=0;
    newNode->cha=NULL;
    newNode->con[0]=NULL;
    newNode->con[1]=NULL;
    newNode->con[2]=NULL;
    return newNode;
}
void giaiphong(state node){
    if (node==NULL) return;
    state b=node;
    free(node);
    for(int i=0;i<3;i++){
        giaiphong(b->con[i]);
    }
}
int isfather(state father,state son){
    if(son==NULL) return 0;
    else{
        if (son->cha==father) return 1;
        else return(isfather(father,son->cha));
    }
}

void randomize(int puzzle[3][3]){
    int pick[]={0,1,2,3,4,5,6,7,8};
    int into[]={0,1,2,3,4,5,6,7,8};
    int output[9];
    int pickn, inton;
    int i=0;
    while(i<9){
        srand((int)time(0));
        pickn=rand()%(9-i);
        inton=rand()%(9-i);
        
        output[into[inton]]=pick[pickn];
        if (pickn!=(8-i)) pick[pickn]=pick[8-i];
        if (inton!=(8-i)) into[inton]=into[8-i];
        i+=1;
    }
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            puzzle[i][j]=output[i*3+j];
        }
    }

}
int isok(int puzzle[3][3]){
    int xau[8];
    int activate=0;
    int *act=&activate;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            int a=puzzle[i][j];
            if (a==0){
                *act=1;
                continue;
            }
            if(*act==0) xau[i*3+j]=a;
            else xau[i*3+j-1]=a;
        }
    }
    int s=0;
    for(int i=0;i<7;i++){
        for(int j=i+1;j<8;j++){
            if (xau[i]>xau[j]) s+=1;
        }
    }
    if (s%2==0) return 1;
    else return 0;
}
void vebang(int puzzle[3][3]){
    printf("\n");
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            printf("%3d",puzzle[i][j]);
        }
        printf("\n");
    }
}