#include<stdio.h>
#include<string.h>

int fun();
int show(char list[][50],int size);

int main(){

    int choice,j,Task_count = 0;
    int addc = 0,Task_to_delete;
    char list[5][50] = {"","","","",""};
    int size = sizeof(list) / sizeof(list[0]);

    while(1){

        fun();
        scanf("%d",&choice);

        if(choice == 1){
            if (Task_count == 0) {
                printf("Task List is Empty!\n");
                continue;
            }
            show(list,size);

            printf("\nEnter The Number of Task you want to Delete : ");
            scanf("%d",&Task_to_delete);
            
            if(Task_to_delete < 1 || Task_to_delete > Task_count){
                printf("Invalid Number !");
                continue;
            }
            for(int k = Task_to_delete - 1; k < 5;k++){

                if(k != 4)
                    strcpy(list[k],list[k + 1]);

                else
                    list[k][0] = '\0';
            }
            Task_count--;
            show(list,size);
        }

        if (choice == 2) {

            if (Task_count >= 5) {
                printf("Task List is Full!\n");
                continue;
            }

            printf("Enter your task no.%d: ", Task_count + 1);
            scanf(" %49[^\n]", list[Task_count]);  

            printf("Task Added successfully!\n");
            Task_count++;
        }

        if(choice == 3){
            show(list,size);
        }
        if(choice == 4){
            char confirm;
            printf("Are you sure you want to exit? (y/n): ");
            scanf(" %c", &confirm);
            if(confirm == 'y' || confirm == 'Y') break;
            else continue;
        }
        
        if(choice != 3){
            printf("\033[2J\033[H");
        }
    }
    return 0;
}

int show(char list[][50], int size){
    for(int i = 0; i < size; i++){
        if(strlen(list[i]) > 0)
            printf("%d. %s\n", i + 1, list[i]);
    }
    return 0;
}

int fun() {
    printf("\nHello there ! Welcome to our To-Do-List !!!\n");
    printf("1.Enter (1) to Delete a Task from the list.\n");    
    printf("2.Enter (2) to add a Task to the list.\n");
    printf("3.Enter (3) to Show the list of work.\n");
    printf("4.Enter (4) to EXIT : ");
    return 0;
}
