# Student Report System

## Description
A C-based management system designed to practice and implement advanced File I/O operations. This project provides a structured way to store, search, and manage student records within a persistent text database.

## Key Features
* **Record-Based Logic**: Uses a specific marker (`=>`) to define the start of a record, ensuring data integrity during search and deletion operations.
* **Safe Deletion**: Implements a temporary file-swapping method to completely remove records rather than leaving "ghost" entries or placeholders.
* **Detailed Search**: Allows users to find and display full student profiles by searching for specific names.

## Technical Skills
* **Data Structures**: Utilizes `typedef struct` to organize student data (Name, Enrollment, Semester, etc.).
* **File Handling**: Proficient use of `fopen`, `fprintf`, `fgets`, and `fclose` for database persistence.
* **System Operations**: Employs `remove()` and `rename()` for robust file management.
* **Pointer Manipulation**: Uses struct pointers to pass data efficiently between functions.

## Highlights
The project successfully addresses common pitfalls in C file handling by moving away from fragile line-counting methods to a dynamic record-matching system.