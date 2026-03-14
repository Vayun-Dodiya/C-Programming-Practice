/*
    This code is still in under manegment !!!
    Deveploped & Designed By Vayun(just to practice FILE IO.)
    this projects is under management because of a feture is going to be added which will help to edit the details of the students
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int fun();

// TO store student's information 
typedef struct student_info{

    unsigned long long enroll;
    int sem;
    char name[50];
    char add[300];
    char div[3];
    
}stinfo;

void StuD(stinfo * sp); // to get information of the student

int format(FILE *,stinfo *,int); // transfers student's details to the file.txt


int main(){
    
    //can store details of 255 students.
    stinfo stud[255];
    stinfo * sp;
    int order;
    int i = 0;

    or : while(1){

        sp = &stud[i];

        fun(); // to print primary function of this program 

        scanf("%d",&order);//takes input of what user wants to perform

        //1. Add detail

        if(order == 1){
            //limts the program by 255
            if(i > 255){
                printf("You cannot add more students. List is full.\n");
                continue;
            }
            
            //student details input
            printf("\nEnter Your Student Details Below:- \n");
            StuD(&stud[i]);

            FILE * fp = fopen("file.txt","a");
            if(fp == NULL){
                printf("FILE not found");
            return 1;
            }

            //prints the detials in a specific pattern / order in a text file.
            format(fp,sp,i);
            
            fclose(fp);
        
            i++;
        }

        //2. View detail - By searching the name of the student.

        if(order == 2){

            char searchName[100];
            char line[90];
            int found = 0;

            printf("Enter name to search: ");
            scanf(" %[^\n]", searchName);

            FILE *fp = fopen("file.txt", "r");
            if(fp == NULL){
                printf("FILE not found\n");
                return 1;
            }
        
            while(fgets(line, sizeof(line), fp)){
            
                line[strcspn(line, "\n")] = '\0'; // Remove newline
            
                if(strstr(line, searchName) != NULL && found == 0){
                    found = 1;
                    printf("Match found: \n", line);
                    
                }
                if(found < 6 && found >= 1){
                    printf("%s\n",line);
                    found++;
                }
            }
        
            fclose(fp);

            //prints an error statement if the searched name is not in the file.
            if(!found)
                printf("Name '%s' not found in file.\n", searchName);
            
        }
        
        //3. Rnemove detail - similar like searching but it store every other details in a deffernt file (not including the searched value) and then restores that all details in the main file

        if(order == 3){
            int found = 0;
            char to_delete[111],word[111];
            char * td = &to_delete[0],*w = &word[0];
            int delete_note = 0;
            char remove_msg;

            //file open : - 
            FILE * fp = fopen("file.txt","r");
            if(fp == NULL){
                printf("FILE not found\n");
                return 1;
            }

            FILE * test = fopen("test.txt","w");
            if(test == NULL){
                printf("FILE not found\n");
                return 1;
            }


            printf("Enter The Student name Whose Details You want to Delete: ");
            scanf(" %[^\n]", &(*td));

            while(fgets(word, sizeof(word), fp)){

                strlwr(word);strlwr(to_delete);
                
                word[strcspn(word, "\n")] = '\0'; // Remove newline
                
                if(strstr(word, to_delete) != NULL && found == 0){
                    found = 1;
                    printf("Match found: \n", word);
                    delete_note = 1;
                }
                //prints a msg for the viewer that some details are deleted
                if((found < 6 && found >= 1)){
                    if(found == 1)
                        fprintf(test,"***Something is Deleted By The Operator***");
                    found++;
                }
                
                if(found == 0){
                    fprintf(test,"%s\n",word);
                }
                
                if(found == 6)
                    found = 0;
            }
            fclose(fp);
            fclose(test);

            //stores the info in the main file again with excluding the searched details or values which are going to be deleted.
            
            test = fopen("test.txt","r");
            if(test == NULL){
                printf("FILE not found\n");
                return 1;
            }

            fp = fopen("file.txt","w");
            if(fp == NULL){
                printf("FILE not found\n");
                return 1;
            }

            while(fgets(word, sizeof(word),test)){
                fprintf(fp,"%s",word);
            }

            fclose(fp);
            fclose(test);

            //check if the deletation is completed
            if(delete_note){
                printf("Target Deleted. ");
                printf("Want to Delete The Delete massage ? (y/n) : ");
                scanf(" %c", &remove_msg);
            }
            else
                printf("Target Not Found. ");
            
            if (remove_msg == 'y' || remove_msg == 'Y'){//asks if the operator wants to delete the msg which was placed after the value is deleted
            
                FILE * fp = fopen("file.txt","r");
                if(fp == NULL){
                    printf("FILE not found\n");
                    return 1;
                }

                FILE * test = fopen("test.txt","w");
                if(test == NULL){
                    printf("FILE not found\n");
                    return 1;
                }

                char to_delete[] = {"***Something is Deleted By The Operator***"};
                found = 0;

                while(fgets(word, sizeof(word), fp)){

                    strlwr(word);strlwr(to_delete);

                    word[strcspn(word, "\n")] = '\0'; // Remove newline

                    if(strstr(word, to_delete) != NULL && found == 0){
                        found = 1;
                        printf("Match found: \n", word);
                        delete_note = 1;
                    }
                    if((found < 3 && found >= 1)){
                        found++;
                    }
                    if(found == 0){
                        fprintf(test,"%s\n",word);
                    }
                    if(found == 3)
                        found = 0;
                }
                fclose(fp);
                fclose(test);

                test = fopen("test.txt","r");
                if(test == NULL){
                    printf("FILE not found\n");
                    return 1;
                }

                fp = fopen("file.txt","w");
                if(fp == NULL){
                    printf("FILE not found\n");
                    return 1;
                }

                while(fgets(word, sizeof(word),test)){
                    // printf("_%s,",word);
                    fprintf(fp,"%s",word);
                }

                fclose(fp);
                fclose(test);
            }
            
        }
        //exits the execution 
        if(order >= 4 || order <= 0){
            break;
        }

    }
    if(order >= 4 || order <= 0){return 0;}

    return 0;
    
}

void StuD(stinfo * sp){

    printf("\nEnter Student's Name : ");
    scanf(" %49[^\n]", sp->name); 

    printf("Enter Your Permenent Address : ");
    scanf(" %49[^\n]", sp->add);

    printf("Enter Division : ");
    scanf(" %2s", &(*sp).div);

    printf("Enter Semester : ");
    re_enter : scanf("%d", &(*sp).sem);

    if((*sp).sem > 8){
        printf("Invalid Semester !!");
        printf("\nEnter Correct Semester : ");
        goto re_enter;
    }

    printf("Enter Your Enrollment No. : ");
    scanf("%llu",&(*sp).enroll);
}

int format(FILE * fp,stinfo * st,int i){
    fprintf(fp,"\n=>\n");
    fprintf(fp,"\tStudent's Name : %s\n",(*st).name);
    fprintf(fp,"\tAddress : %s\n",(*st).add);
    fprintf(fp,"\tDivision : %s\n",(*st).div);
    fprintf(fp,"\tSemester : %d\n",(*st).sem);
    fprintf(fp,"\tEnrollment No. %llu\n",(*st).enroll);
    return 0;
}

int fun() {
    printf("\nHello there ! Welcome to our To-Do-List !!!\n");
    printf("1.Enter (1) to Add Student Details.\n");    
    printf("2.Enter (2) to View Student Details.\n");
    printf("3.Enter (3) to Remove Student details.\n");
    printf("4.Enter (4) to EXIT : ");
    return 0;
}