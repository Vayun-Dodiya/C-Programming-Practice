/*
    This code is still in under manegment !!!
    Deveploped & Designed By Vayun(just to practice FILE IO.)
    this projects is under management because of a feture is going to be added which will help to edit the details of the students
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int fun();

// TO store student's information
typedef struct student_info
{

    unsigned long long enroll;
    int sem;
    char name[50];
    char add[300];
    char div[3];

} stinfo;

void StuD(stinfo *sp); // to get information of the student

int format(FILE *, stinfo *, int); // transfers student's details to the file.txt

int main()
{

    // can store details of 255 students.
    stinfo stud[255];
    stinfo *sp;
    int order;
    int i = 0;

or:
    while (1)
    {

        sp = &stud[i];

        fun(); // to print primary function of this program

        scanf("%d", &order); // takes input of what user wants to perform

        // 1. Add detail

        if (order == 1)
        {
            // limts the program by 255
            if (i > 255)
            {
                printf("You cannot add more students. List is full.\n");
                continue;
            }

            // student details input
            printf("\nEnter Your Student Details Below:- \n");
            StuD(&stud[i]);

            FILE *fp = fopen("file.txt", "a");
            if (fp == NULL)
            {
                printf("FILE not found");
                return 1;
            }

            // prints the detials in a specific pattern / order in a text file.
            format(fp, sp, i);

            fclose(fp);

            i++;
        }

        // 2. View detail - By searching the name of the student.

        if (order == 2)
        {
            char searchName[100];
            char line[300];
            int found = 0;
            int printing = 0;

            printf("Enter name to search: ");
            scanf(" %99[^\n]", searchName);

            FILE *fp = fopen("file.txt", "r");
            if (fp == NULL)
            {
                printf("FILE not found\n");
                return 1;
            }

            while (fgets(line, sizeof(line), fp))
            {
                // If we hit a new record marker
                if (strstr(line, "=>") != NULL)
                {
                    printing = 0; // Stop printing the previous record

                    // Peek at the next line to check the name
                    long pos = ftell(fp);
                    char nameLine[300];
                    if (fgets(nameLine, sizeof(nameLine), fp))
                    {
                        if (strstr(nameLine, searchName) != NULL)
                        {
                            printf("\n--- Match Found ---\n");
                            printf("%s", line);     // Print the "=>"
                            printf("%s", nameLine); // Print the Name
                            printing = 1;           // Start printing the rest of this record
                            found = 1;
                        }
                    }
                    continue;
                }

                // Keep printing lines until we hit the next "=>"
                if (printing)
                {
                    printf("%s", line);
                }
            }

            fclose(fp);

            if (!found)
                printf("Name '%s' not found in file.\n", searchName);
        }

        // 3. Rnemove detail - similar like searching but it store every other details in a deffernt file (not including the searched value) and then restores that all details in the main file

        if (order == 3)
        {
            char searchName[100];
            char line[300];
            int found = 0;
            int skipping = 0;

            FILE *fp = fopen("file.txt", "r");
            FILE *temp = fopen("temp.txt", "w");

            if (fp == NULL || temp == NULL)
            {
                printf("Error: Could not access database.\n");
                if (fp)
                    fclose(fp);
                return 1;
            }

            printf("Enter the Student Name to delete: ");
            scanf(" %99[^\n]", searchName);

            while (fgets(line, sizeof(line), fp))
            {
                // Check if this line is the start of a student record
                if (strstr(line, "=>") != NULL)
                {
                    skipping = 0; // Reset skipping for the new record

                    // Peek at the next line (which is the Name line in your format)
                    long pos = ftell(fp);
                    char nameLine[300];
                    if (fgets(nameLine, sizeof(nameLine), fp))
                    {
                        if (strstr(nameLine, searchName) != NULL)
                        {
                            skipping = 1; // Match found! Start skipping this record
                            found = 1;
                        }
                        else
                        {
                            // Not a match, write both the marker and the name line
                            fprintf(temp, "%s", line);
                            fprintf(temp, "%s", nameLine);
                        }
                    }
                    continue;
                }

                // Only write the line if we aren't currently skipping a matched record
                if (!skipping)
                {
                    fprintf(temp, "%s", line);
                }
            }

            fclose(fp);
            fclose(temp);

            // Swap files: Delete old, rename new
            remove("file.txt");
            rename("temp.txt", "file.txt");

            if (found)
            {
                printf("\nSuccessfully deleted student: %s\n", searchName);
                i--; // Keep your array counter in sync
            }
            else
            {
                printf("\nStudent '%s' not found.\n", searchName);
            }
        }
        // exits the execution
        if (order >= 4 || order <= 0)
        {
            break;
        }
    }
    if (order >= 4 || order <= 0)
    {
        return 0;
    }

    return 0;
}

void StuD(stinfo *sp)
{

    printf("\nEnter Student's Name : ");
    scanf(" %49[^\n]", sp->name);

    printf("Enter Your Permenent Address : ");
    scanf(" %49[^\n]", sp->add);

    printf("Enter Division : ");
    scanf(" %2s", &(*sp).div);

    printf("Enter Semester : ");
re_enter:
    scanf("%d", &(*sp).sem);

    if ((*sp).sem > 8)
    {
        printf("Invalid Semester !!");
        printf("\nEnter Correct Semester : ");
        goto re_enter;
    }

    printf("Enter Your Enrollment No. : ");
    scanf("%llu", &(*sp).enroll);
}

int format(FILE *fp, stinfo *st, int i)
{
    fprintf(fp, "\n=>\n");
    fprintf(fp, "\tStudent's Name : %s\n", (*st).name);
    fprintf(fp, "\tAddress : %s\n", (*st).add);
    fprintf(fp, "\tDivision : %s\n", (*st).div);
    fprintf(fp, "\tSemester : %d\n", (*st).sem);
    fprintf(fp, "\tEnrollment No. %llu\n", (*st).enroll);
    return 0;
}

int fun()
{
    printf("\nHello there ! Welcome to our To-Do-List !!!\n");
    printf("1.Enter (1) to Add Student Details.\n");
    printf("2.Enter (2) to View Student Details.\n");
    printf("3.Enter (3) to Remove Student details.\n");
    printf("4.Enter (4) to EXIT : ");
    return 0;
}