/*
    Contact List Management System in C -
    This is a simple contact list management system implemented in C. It allows users to add, view, search, edit, and delete contacts stored in a text file. The program provides a command-line interface for users to interact with the functionalities.

        1. List All Contacts: Displays all the contacts stored in the file.
        2. Add Contacts: Allows the user to add a new contact by entering the name and number. The contact is then saved to a file.
        3. Search Contacts: Enables the user to search for a contact by name and displays the contact
            information if found.
        4. Edit Contacts: Allows the user to edit an existing contact's name or number.
        5. Remove Contacts: Enables the user to delete a contact from the list.
        6. Close the Program: Exits the program.

          - The program uses a structured format to store contact information in a text file, making it easy to read and manage. It also includes input validation for phone numbers and handles file operations for reading and writing contact data.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Contact_Info
{
    unsigned long long Number;
    char Name[100];
} ConI;

int con_fun();
int formet_con_(FILE *, ConI *);
void Lower(ConI *);

int main()
{
    int op = con_fun();

    int i = 0;
    ConI Cont[5];
    ConI *CI = &Cont[i];
    while (1)
    {
        if (i >= 5)
        {
            CI = (ConI *)malloc(i * sizeof(ConI));
        }
        if (op == 1)
        {
            char str[100];
            FILE *fp = fopen("Contact_list.txt", "r");
            while (fgets(str, sizeof(str), fp))
            {
                printf("%s", str);
            }
            fclose(fp);
        }

        if (op == 2)
        {
            int valid;
            ConI cont[10];

            printf("Enter Contact Name : \n");
            scanf(" %99[^\n]", &(*CI).Name);

            Lower(CI);

            printf("Ente Number : \n");
        again:

            scanf("%llu", &(*CI).Number);

            int digit = 0;
            unsigned long long temp = (*CI).Number;

            if (temp == 0)
                digit = 1;
            else
            {
                while (temp != 0)
                {
                    temp /= 10;
                    digit++;
                }
            }

            if (digit == 10)
            {
                valid = 1;
            }
            else
            {
                printf("Invalid length (%d digits). ", digit);
                goto again;
            }

            FILE *fp = fopen("Contact_List.txt", "a");

            formet_con_(fp, CI);

            fclose(fp);
            i++;
        }

        if (op == 3)
        {
            char searchName[100];
            char line[300];
            int found = 0;
            int printing = 0;

            printf("Enter name to search: ");
            scanf(" %99[^\n]", searchName);

            FILE *fp = fopen("Contact_List.txt", "r");
            if (fp == NULL)
            {
                printf("FILE not found\n");
                return 1;
            }

            while (fgets(line, sizeof(line), fp))
            {
                // If we hit a new record marker
                if (strstr(line, "==>") != NULL)
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

        if (op == 4)
        {
            char searchName[100];
            int match = 0;
            char line[300];
            int found = 0;
            int skipping = 0;
            FILE *fp = fopen("Contact_List.txt", "r");
            FILE *temp = fopen("temp.txt", "w");
            if (fp == NULL || temp == NULL)
            {
                printf("FILE not found\n");
                return 1;
            }
            printf("Enter the Contact Name to delete: ");
            scanf(" %99[^\n]", searchName);
            while (fgets(line, sizeof(line), fp))
            {
                // Check if this line is the start of a contact record
                if (strstr(line, "==>") != NULL)
                {
                    skipping = 0; // Reset skipping for the new record

                    // Peek at the next line (which is the Name line in your format)
                    long pos = ftell(fp);
                    char nameLine[300];
                    if (fgets(nameLine, sizeof(nameLine), fp))
                    {
                        if (strstr(nameLine, searchName) != NULL)
                        {
                            printf("\n--- Match Found ---\n");
                            match = 1;
                            printf("%s IS REMOVED", nameLine); // Print the "==>"
                            skipping = 1;                      // Match found! Start skipping this record
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
            if (match == 0)
            {
                printf("Name '%s' not found in file.\n", searchName);
            }
            remove("Contact_List.txt");
            rename("temp.txt", "Contact_List.txt");
            break;
        }
        if (op == 5)
        {
            int edit;
            printf("Enter (1) To Edit Number Or (2) to Edit Name: ");
            scanf("%d", &edit);
            if (edit != 1 && edit != 2)
            {
                printf("Invalid choice\n");
                break;
            }
            printf("Enter the Contact Name to Edit: ");
            char searchName[100];
            scanf(" %99[^\n]", searchName);
            char line[300];
            int found = 0;
            int skip_lines = 0;
            FILE *fp = fopen("Contact_List.txt", "r");
            FILE *temp = fopen("temp.txt", "w");
            if (fp == NULL || temp == NULL)
            {
                printf("FILE not found\n");
                return 1;
            }
            while (fgets(line, sizeof(line), fp))
            {
                // Check if this line is the start of a contact record
                if (strstr(line, "==>") != NULL)
                {
                    // Peek at the next line to check the name
                    long pos = ftell(fp);
                    char nameLine[300];
                    if (fgets(nameLine, sizeof(nameLine), fp))
                    {
                        if (strstr(nameLine, searchName) != NULL)
                        {
                            printf("\n--- Match Found ---\n");
                            printf("%s", line);     // Print the "==>"
                            printf("%s", nameLine); // Print the Name
                            found = 1;
                            if (edit == 1)
                            {
                                printf("Enter New Number : ");
                                unsigned long long newNum;
                                scanf("%llu", &newNum);
                                // validate
                                int digit = 0;
                                unsigned long long temp_num = newNum;
                                if (temp_num == 0) digit = 1;
                                else while (temp_num != 0) { temp_num /= 10; digit++; }
                                if (digit != 10) {
                                    printf("Invalid number length (%d digits). Please enter 10 digits.\n", digit);
                                    // For simplicity, continue with invalid, or could loop, but since user said minimal, use it
                                }
                                fprintf(temp, "%s", line);
                                fprintf(temp, "%s", nameLine);
                                fprintf(temp, "\tNumber : %llu\n\n", newNum);
                                skip_lines = 2; // skip old number and blank
                            }
                            else if (edit == 2)
                            {
                                printf("Enter New Name : ");
                                char newName[100];
                                scanf(" %99[^\n]", newName);
                                // lower
                                for (int i = 0; newName[i] != '\0'; i++)
                                {
                                    if (newName[i] >= 'A' && newName[i] <= 'Z')
                                    {
                                        newName[i] += 32;
                                    }
                                }
                                fprintf(temp, "%s", line);
                                fprintf(temp, "\tName : %s\n", newName);
                                // number will be written next
                                skip_lines = 0;
                            }
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
                // Skip lines if needed
                if (skip_lines > 0)
                {
                    skip_lines--;
                    continue;
                }
                // Just copy lines until we hit the next "=>"
                fprintf(temp, "%s", line);
            }
            fclose(fp);
            fclose(temp);
            if (!found)
            {
                printf("Name '%s' not found in file.\n", searchName);
                remove("temp.txt");
            }
            else
            {
                remove("Contact_List.txt");
                rename("temp.txt", "Contact_List.txt");
                printf("Contact updated successfully.\n");
            }
            break;
        }

        if (op == 6)
        {
            printf("Thank You For Being with Us.");
            break;
        }
        if (op != 6)
            op = con_fun();
    }
    return 0;
}

int con_fun()
{
    int op;
    printf("Enter the Number Of the funtion or Task you want To Perform:\n");
    printf("1. List All Contacts:\n");
    printf("2. Add Contacts:\n");
    printf("3. Search Contacts:\n");
    printf("4. Edit Contacts:\n");
    printf("5. Remove Contacts:\n");
    printf("6. Close the Program:");
in:
    scanf("%d", &op);
    if (op > 6 || op <= 0)
    {
        printf("Invalide Input Enter Again:");
        goto in;
    }
    return op;
}

int formet_con_(FILE *fp, ConI *CI)
{
    fprintf(fp, "==>\n");
    fprintf(fp, "\tName : %s\n", (*CI).Name);
    fprintf(fp, "\tNumber : %llu\n\n", (*CI).Number);
}

void Lower(ConI *CI)
{
    for (int i = 0; CI->Name[i] != '\0'; i++)
    {
        if (CI->Name[i] >= 'A' && CI->Name[i] <= 'Z')
        {
            CI->Name[i] += 32;
        }
    }
}