# Contact List (AI Enhanced)

## Description
A robust contact management tool developed using a "Pair Programming" approach with GitHub Copilot. This project demonstrates the integration of manual validation logic with advanced AI-suggested file-stream techniques.

## Key Features
* **Data Integrity**: Includes a manual validation loop to ensure phone numbers are exactly 10 digits before saving.
* **String Normalization**: Features a `Lower()` function for case-insensitive searching, ensuring "Vayun" and "vayun" yield the same result.
* **Advanced Editing**: A sophisticated edit function that allows users to update specific fields (Name or Number) within an existing record.

## Technical Skills
* **File Navigation**: Advanced use of `ftell()` and `fseek()` to "peek" at data and navigate the file stream accurately.
* **Memory Management**: Implementation of dynamic memory allocation using `malloc()` for handling growing contact lists.
* **Cross-Platform Support**: Includes environment-aware code to handle terminal screen clearing on both Windows and Unix-based systems.

## Highlights
This project serves as a bridge between foundational C programming and modern development workflows, utilizing AI tools to implement complex CRUD (Create, Read, Update, Delete) operations safely.