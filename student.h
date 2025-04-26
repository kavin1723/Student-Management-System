#ifndef STUDENT_H
#define STUDENT_H

#define MAX_NAME 50
#define MAX_STUDENTS 100

typedef struct {
    int id;
    char name[MAX_NAME];
    float grade;
} Student;

// Function prototypes
void addStudent(Student **students, int *count);
void displayStudents(Student *students, int count);
Student* searchStudent(Student *students, int count, int id);
void updateStudent(Student *students, int count);
void deleteStudent(Student **students, int *count);
void saveToFile(Student *students, int count);
void loadFromFile(Student **students, int *count);

#endif