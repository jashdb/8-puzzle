#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include"common_function.h"
#include"user_solve.h"
#include"machine_solve.h"
int right_state[3][3]={{1,2,3},{4,5,6},{7,8,0}};

int main(){
    int menu1,menu2,menu3;
    int puzzle[3][3];
    do{
        printf("----MENU----\n1.Play a game\n2.Guess a table\nYour choice?\n------------");
        scanf("%d",&menu1);
        switch(menu1){
            case 1:
                do{
                    randomize(puzzle);
                } while(isok(puzzle)==0);

                movemyself(puzzle,right_state);
                break;

            case 2:
                do{
                    printf("----Do you want to make your own puzzle or let your table be machine-created?----\n1. Make my own table\n2. Create a random table\n------------");
                    scanf("%d",&menu2);
                    switch(menu2){
                        case 1:
                            int check[3][3];
                            diy(check);
                            equal(puzzle, check);
                            break;
                        case 2:
                            randomize(puzzle);
                            vebang(puzzle);
                            break;
                    }
                } while(menu2!=1&&menu2!=2);

                int solvable=isok(puzzle);
                char query;
                if(solvable==confirm_solve(query)) printf("\nCongrats! You are correct!");
                else printf("\nSorry :( Your answer is not correct\n");

                if(solvable==1){
                    do{
                        printf("\n----So the table above can be solved. What would you like to do?----\n1. Let the machine do the solving\n2. Solve it myself\nYour choice? ");
                        scanf("%d",&menu3);
                        switch(menu3){
                            case 1:{
                                state root=createNode(puzzle);
                                state a=makeTree(root,right_state);
                                road(a,right_state);
                                giaiphong(root);
                                break;
                            }
                            case 2:
                                movemyself(puzzle,right_state);
                                break;
                        }
                    } while(menu3!=1&&menu3!=2);
                }
        }
    } while(menu1!=1&&menu1!=2);
}