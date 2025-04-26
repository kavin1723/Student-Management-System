#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

void addStudent(Student **students, int *count) {
    if (*count >= MAX_STUDENTS) {
        printf("Error: Maximum student limit reached.\n");
        return;
    }

    // Allocate memory for a new student
    *students = realloc(*students, (*count + 1) * sizeof(Student));
    if (*students == NULL) {
        printf("Error: Memory allocation failed.\n");
        exit(1);
    }

    Student *newStudent = &(*students)[*count];
    printf("Enter student ID: ");
    scanf("%d", &newStudent->id);
    getchar(); // Clear newline
    printf("Enter student name: ");
    fgets(newStudent->name, MAX_NAME, stdin);
    newStudent->name[strcspn(newStudent->name, "\n")] = '\0'; // Remove newline
    printf("Enter student grade: ");
    scanf("%f", &newStudent->grade);

    (*count)++;
    printf("Student added successfully!\n");
}

void displayStudents(Student *students, int count) {
    if (count == 0) {
        printf("No students to display.\n");
        return;
    }

    printf("\nStudent Records:\n");
    printf("ID\tName\t\tGrade\n");
    printf("--------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%d\t%-15s\t%.2f\n", students[i].id, students[i].name, students[i].grade);
    }
}

Student* searchStudent(Student *students, int count, int id) {
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            return &students[i];
        }
    }
    return NULL;
}

void updateStudent(Student *students, int count) {
    int id;
    printf("Enter student ID to update: ");
    scanf("%d", &id);

    Student *student = searchStudent(students, count, id);
    if (student == NULL) {
        printf("Student not found.\n");
        return;
    }

    getchar(); // Clear newline
    printf("Enter new name: ");
    fgets(student->name, MAX_NAME, stdin);
    student->name[strcspn(student->name, "\n")] = '\0';
    printf("Enter new grade: ");
    scanf("%f", &student->grade);

    printf("Student updated successfully!\n");
}

void deleteStudent(Student **students, int *count) {
    int id;
    printf("Enter student ID to delete: ");
    scanf("%d", &id);

    int index = -1;
    for (int i = 0; i < *count; i++) {
        if ((*students)[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Student not found.\n");
        return;
    }

    // Shift elements to remove student
    for (int i = index; i < *count - 1; i++) {
        (*students)[i] = (*students)[i + 1];
    }

    (*count)--;
    *students = realloc(*students, (*count) * sizeof(Student));
    printf("Student deleted successfully!\n");
}

void saveToFile(Student *students, int count) {
    FILE *file = fopen("students.dat", "wb");
    if (file == NULL) {
        printf("Error: Could not open file.\n");
        return;
    }

    fwrite(&count, sizeof(int), 1, file);
    fwrite(students, sizeof(Student), count, file);
    fclose(file);
    printf("Data saved to file.\n");
}

void loadFromFile(Student **students, int *count) {
    FILE *file = fopen("students.dat", "rb");
    if (file == NULL) {
        printf("No existing data file found.\n");
        return;
    }

    fread(count, sizeof(int), 1, file);
    *students = malloc(*count * sizeof(Student));
    if (*students == NULL) {
        printf("Error: Memory allocation failed.\n");
        fclose(file);
        exit(1);
    }

    fread(*students, sizeof(Student), *count, file);
    fclose(file);
    printf("Data loaded from file.\n");
}