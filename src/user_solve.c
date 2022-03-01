#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include"common_function.h"

void diy(int check[3][3]);
void confirm_change(int check[3][3]);

//Tạo bảng từ đầu vào
void diy(int check[3][3]){
    int xau[9];
    printf("Insert numbers from left to right, up to down:\n");
    for (int i=0;i<9;i++){
        do{
            printf("%d. ",i+1);
            scanf("%d",&xau[i]);
            if (xau[i]<0||xau[i]>8){
                printf("Numbers must be bigger than or equal to 0, smaller than or equal to 8\n");
            }
            if (isdup(xau,i)==1){
                printf("Duplicate number!\n");
            }
            printf("You choosed:");
            for(int j=0;j<=i;j++){
                printf("%d ",xau[j]);
            }
            printf("\n");
        } while(xau[i]<0||xau[i]>8||isdup(xau,i)==1);
    }
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            check[i][j]=xau[i*3+j];
        }
    }
    
    printf("Here is your table:");
    vebang(check);
    confirm_change(check);
}

//Kiểm tra nếu người dùng có muốn thay đổi bảng vừa tạo không
void confirm_change(int check[3][3]){
    char change;
    printf("Do you want to change? Y/N");
    fflush(stdin);
    scanf("%c",&change);
    if (change=='Y'||change=='y') diy(check);
    else if (change=='N'||change=='n') return;
    else confirm_change(check);
}

//Hàm đệ quy thực hiện di chuyển 
void move(int table[3][3],int *pter,int right_state[3][3]){
    if(isdupstate(table,right_state)){
        printf("\nCongratulation!! You solved the puzzle\n");
        return;
    }
    else{
        int x;
        do{
            printf("\nNext move? ");
            scanf("%d",pter);
            x=*pter;
            if(x<1||x>8) printf("\nInput has to be from 1 to 8");
        } while(x<1||x>8);
        
        int a1,a2,b1,b2;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                int a=table[i][j];
                if (a==0) a1=i,b1=j;
                else if (a==x) a2=i,b2=j;
                else continue;
            }
        }
        if (abs(a1-a2)+abs(b1-b2)!=1) printf("Sorry! You can't do this move");
        else{
            swap(&table[a1][b1],&table[a2][b2]);
            vebang(table);
        }
        move(table,pter,right_state);
    }
}

//Di chuyển các ô theo đầu vào của người dùng
void movemyself(int table[3][3],int right_state[3][3]){
    printf("This is the starting table:");
    vebang(table);
    printf("Which square you want to move? ");

    int x;
    move(table,&x,right_state);
}

//Xác nhận người dùng có nghĩ bảng này giải được hay ko
int confirm_solve(char query){
    printf("\nDo you think the table above can be solved? Y/N");
    fflush(stdin);
    scanf("%c",&query);
    if(query=='Y'||query=='y') return 1;
    else if(query=='N'||query=='n') return 0;
    else return confirm_solve(query);
}