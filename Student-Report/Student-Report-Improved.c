/*
this is a simple C program that allows users to manage student details. It provides functionalities to add, view, and remove student information. The program uses a structure to store student details and file handling to save and retrieve data from a text file.
Key features of the program include:
    1. Adding Student Details: Users can input student information such as name, address, division, semester, and enrollment number. The details are then saved to a text file in a specific format.
    2. Viewing Student Details: Users can search for a student by name, and if found, the program displays the corresponding details from the text file.
    3. Removing Student Details: Users can delete a student's information by searching for their name
         The program reads the existing data from the text file, removes the matching record, and updates the file accordingly.
    4. User Interface: The program provides a simple command-line interface for users to interact with the functionalities.

    - By Vayun Dodiya 
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int fun();

typedef struct student_info
{

    unsigned long long enroll;
    int sem;
    char name[50];
    char add[300];
    char div[3];

} stinfo;

void StuD(stinfo *sp);

int format(FILE *, stinfo *, int);

int main()
{

    stinfo stud[255];
    stinfo *sp;
    int order;
    int i = 0;

or:
    while (1)
    {

        sp = &stud[i];

        fun();

        scanf("%d", &order);

        if (order == 1)
        {
            if (i > 255)
            {
                printf("You cannot add more students. List is full.\n");
                continue;
            }

            printf("\nEnter Your Student Details Below:- \n");
            StuD(&stud[i]);

            FILE *fp = fopen("file.txt", "a");
            if (fp == NULL)
            {
                printf("FILE not found");
                return 1;
            }

            format(fp, sp, i);

            fclose(fp);

            i++;
        }

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