#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student
{
    int rollNo;
    char name[50];
    float marks;
};

void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

int main()
{
    int choice;

    while (1)
    {
        printf("\n=================================\n");
        printf("   STUDENT MANAGEMENT SYSTEM\n");
        printf("=================================\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addStudent();
            break;

        case 2:
            displayStudents();
            break;

        case 3:
            searchStudent();
            break;

        case 4:
            updateStudent();
            break;

        case 5:
            deleteStudent();
            break;

        case 6:
            printf("Exiting Program...\n");
            exit(0);

        default:
            printf("Invalid Choice!\n");
        }
    }

    return 0;
}

// Add Student
void addStudent()
{
    FILE *fp;
    struct Student s;

    fp = fopen("students.dat", "ab");

    if (fp == NULL)
    {
        printf("File Error!\n");
        return;
    }

    printf("\nEnter Roll Number: ");
    scanf("%d", &s.rollNo);

    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(s), 1, fp);

    fclose(fp);

    printf("Student Record Added Successfully!\n");
}

// Display Students
void displayStudents()
{
    FILE *fp;
    struct Student s;

    fp = fopen("students.dat", "rb");

    if (fp == NULL)
    {
        printf("No Records Found!\n");
        return;
    }

    printf("\n-----------------------------------------\n");
    printf("Roll No\t\tName\t\tMarks\n");
    printf("-----------------------------------------\n");

    while (fread(&s, sizeof(s), 1, fp))
    {
        printf("%d\t\t%s\t\t%.2f\n",
               s.rollNo,
               s.name,
               s.marks);
    }

    fclose(fp);
}

// Search Student
void searchStudent()
{
    FILE *fp;
    struct Student s;
    int roll;
    int found = 0;

    fp = fopen("students.dat", "rb");

    if (fp == NULL)
    {
        printf("No Records Found!\n");
        return;
    }

    printf("Enter Roll Number to Search: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(s), 1, fp))
    {
        if (s.rollNo == roll)
        {
            printf("\nStudent Found!\n");
            printf("Roll Number : %d\n", s.rollNo);
            printf("Name        : %s\n", s.name);
            printf("Marks       : %.2f\n", s.marks);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Student Not Found!\n");
    }

    fclose(fp);
}

// Update Student
void updateStudent()
{
    FILE *fp;
    struct Student s;
    int roll;
    int found = 0;

    fp = fopen("students.dat", "rb+");

    if (fp == NULL)
    {
        printf("No Records Found!\n");
        return;
    }

    printf("Enter Roll Number to Update: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(s), 1, fp))
    {
        if (s.rollNo == roll)
        {
            printf("Enter New Name: ");
            scanf(" %[^\n]", s.name);

            printf("Enter New Marks: ");
            scanf("%f", &s.marks);

            fseek(fp, -(long)
            sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, fp);

            printf("Record Updated Successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Student Not Found!\n");
    }

    fclose(fp);
}

// Delete Student
void deleteStudent()
{
    FILE *fp, *temp;
    struct Student s;
    int roll;
    int found = 0;

    fp = fopen("students.dat", "rb");

    if (fp == NULL)
    {
        printf("No Records Found!\n");
        return;
    }

    temp = fopen("temp.dat", "wb");

    printf("Enter Roll Number to Delete: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(s), 1, fp))
    {
        if (s.rollNo == roll)
        {
            found = 1;
            continue;
        }

        fwrite(&s, sizeof(s), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        printf("Record Deleted Successfully!\n");
    else
        printf("Student Not Found!\n");
}