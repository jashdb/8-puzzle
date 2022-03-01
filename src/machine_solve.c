#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include"common_function.h"

state makeSubTree(state a, state root,int right_state[3][3],state Xmin,int* stop){//Xmin là cấu hình chuẩn đã tồn tại trên cây với thuộc tính X là nhỏ nhất, nếu Xmin chưa tồn tại thì sẽ có giá trị NULL
    if (*stop==1) return Xmin;
    if(a==NULL) return Xmin;//Kiểm tra cấu hình có tồn tại hay không
    if(root==NULL) root=a;//Kiểm tra đã có cây chưa
    if(isdupstate(right_state,a->table)){//Kiểm tra có phải cấu hình chuẩn không
        Xmin=a;
        *stop=1;
    }
    else{
        if(a->X==MAX) return Xmin;
        int a0,b0;
        int pos[4][2]={{-1,-1},{-1,-1},{-1,-1},{-1,-1}};//Tọa độ các ô xung quanh ô trống
        int value=-1;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if (a->table[i][j]==0){
                    a0=i;
                    b0=j;
                    break;
                }
            }
        }
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(abs(a0-i)+abs(b0-j)==1){
                    value+=1;
                    pos[value][0]=i;
                    pos[value][1]=j;
                }
            }
        }
        int SoCon=SOCONMAX;//Số trường hợp có thể di chuyển trong 1 lượt tối đa là 4, do vậy có tối đa 4 cấu hình con
        for(int i=0;i<4;i++){//Lọc để tìm đúng số trường hợp trong lượt này
            if(pos[i][0]==-1&&pos[i][1]==-1){
                SoCon-=1;
            }
        }
        for(int i=0;i<SoCon;i++){
            if (a->table[pos[i][0]][pos[i][1]]==a->t){//Kiểm tra xem cấu hình đang xét có bị lặp với cấu hình cha không
                swap(&pos[i][0],&pos[SoCon-1][0]);
                swap(&pos[i][1],&pos[SoCon-1][1]);
                SoCon-=1;
                break;
            }
        }
        int row[SoCon],col[SoCon],deltaS[SoCon];
        move_type* moves=(move_type*)malloc(sizeof(move_type)*SoCon);
        for(int i=0;i<SoCon;i++){
            moves[i].x=pos[i][0];
            moves[i].y=pos[i][1];
            moves[i].tile=a->table[moves[i].x][moves[i].y];
            row[i]=(moves[i].tile-1)/3;
            col[i]=(moves[i].tile-1)%3;
            moves[i].deltaS=(abs(a0-row[i])+abs(b0-col[i]))-(abs(moves[i].x-row[i])+abs(moves[i].y-col[i]));//Tính deltaS của từng trường hợp
        }
        
        for(int i=SoCon-2;i>=0;i--){
            for(int j=0;j<=i;j++){
                if(moves[j].deltaS>moves[j+1].deltaS){
                    swap(&moves[j].x,&moves[j+1].x);
                    swap(&moves[j].y,&moves[j+1].y);
                    swap(&moves[j].tile,&moves[j+1].tile);
                    swap(&moves[j].deltaS,&moves[j+1].deltaS);
                }
            }
        }
        for(int i=0;i<SoCon;i++){
            int con_table[3][3];
            equal(con_table,a->table);
            swap(&con_table[a0][b0],&con_table[moves[i].x][moves[i].y]);
            a->con[i]=createNode(con_table);
            a->con[i]->cha=a;
            a->con[i]->t=moves[i].tile;
            a->con[i]->X=(a->X)+1;
            Xmin= makeSubTree(a->con[i],root,right_state,Xmin,stop);
        }
        
    }
    return Xmin;
}

//Tạo cây từ root và trả về kết quả là con trỏ trỏ tới cấu hình chuẩn
state makeTree(state root,int right_state[3][3]){
    state Xmin=NULL;
    int dung=0;
    return makeSubTree(root,NULL,right_state,Xmin,&dung);
}

void road(state min,int right_state[3][3]){
    if(min==NULL) printf("\nNo road");
    else{
        int number=min->X+1;
        state step[number];
        state start=min;

        for(int i=0;i<number;i++){
            step[i]=start;
            start=start->cha;
        }

        printf("Step by step:\n");
        for(int j=number-1;j>=0;j--){
            vebang(step[j]->table);
        }

        printf("\nSummary:START");
        for(int j=number-2;j>=0;j--){
            printf("->%d",step[j]->t);
        }
        printf("->FINISH\n");
        printf("Takes %d step to solve\n",number-1);
    }
}