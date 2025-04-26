#include <stdio.h>
#include <stdlib.h>
#include "student.h"

int main() {
    Student *students = NULL;
    int count = 0;
    int choice;

    // Load existing data
    loadFromFile(&students, &count);

    while (1) {
        printf("\nStudent Record System\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Save and Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent(&students, &count);
                break;
            case 2:
                displayStudents(students, count);
                break;
            case 3: {
                int id;
                printf("Enter student ID to search: ");
                scanf("%d", &id);
                Student *student = searchStudent(students, count, id);
                if (student) {
                    printf("ID: %d, Name: %s, Grade: %.2f\n", student->id, student->name, student->grade);
                } else {
                    printf("Student not found.\n");
                }
                break;
            }
            case 4:
                updateStudent(students, count);
                break;
            case 5:
                deleteStudent(&students, &count);
                break;
            case 6:
                saveToFile(students, count);
                free(students);
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}