#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    char roll[20];
    char name[50];
    int marks;
};

void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

int main() {
    int choice;

    while(1) {
        printf("\n====================================");
        printf("\n STUDENT RECORD MANAGEMENT SYSTEM");
        printf("\n====================================");

        printf("\n1. Add Student");
        printf("\n2. Display Students");
        printf("\n3. Search Student");
        printf("\n4. Update Student");
        printf("\n5. Delete Student");
        printf("\n6. Exit");

        printf("\n\nEnter your choice: ");
        scanf("%d",&choice);

        switch(choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6:
                printf("\nThank You!\n");
                exit(0);
            default:
                printf("\nInvalid Choice!\n");
        }
    }
    return 0;
}

void addStudent() {
    FILE *fp;
    struct Student s;

    fp = fopen("students.dat","ab");
    if(fp == NULL) {
        printf("\nFile Error!\n");
        return;
    }

    printf("\nEnter Roll Number: ");
    scanf("%s",s.roll);

    getchar(); // clear newline

    printf("Enter Name: ");
    fgets(s.name,sizeof(s.name),stdin);
    s.name[strcspn(s.name,"\n")] = '\0';  // remove newline

    printf("Enter Marks: ");
    scanf("%d",&s.marks);

    fwrite(&s,sizeof(s),1,fp);
    fclose(fp);

    printf("\nStudent Added Successfully!\n");
}

void displayStudents() {
    FILE *fp;
    struct Student s;

    fp = fopen("students.dat","rb");
    if(fp == NULL) {
        printf("\nNo Records Found!\n");
        return;
    }

    printf("\n----------------------------------------------------");
    printf("\n%-15s %-25s %-10s","Roll No","Name","Marks");
    printf("\n----------------------------------------------------");

    while(fread(&s,sizeof(s),1,fp)) {
        printf("\n%-15s %-25s %-10d",s.roll,s.name,s.marks);
    }

    printf("\n----------------------------------------------------\n");
    fclose(fp);
}

void searchStudent() {
    FILE *fp;
    struct Student s;
    char roll[20];
    int found = 0;

    fp = fopen("students.dat","rb");
    if(fp == NULL) {
        printf("\nNo Records Found!\n");
        return;
    }

    printf("\nEnter Roll Number to Search: ");
    scanf("%s",roll);

    while(fread(&s,sizeof(s),1,fp)) {
        if(strcmp(s.roll,roll) == 0) {
            printf("\n\nStudent Found!");
            printf("\n------------------------");
            printf("\nRoll Number : %s",s.roll);
            printf("\nName        : %s",s.name);
            printf("\nMarks       : %d",s.marks);
            found = 1;
            break;
        }
    }

    if(!found) printf("\nStudent Not Found!");
    fclose(fp);
}

void updateStudent() {
    FILE *fp,*temp;
    struct Student s;
    char roll[20];
    int found = 0;

    fp = fopen("students.dat","rb");
    temp = fopen("temp.dat","wb");

    if(fp == NULL || temp == NULL) {
        printf("\nFile Error!\n");
        return;
    }

    printf("\nEnter Roll Number to Update: ");
    scanf("%s",roll);

    while(fread(&s,sizeof(s),1,fp)) {
        if(strcmp(s.roll,roll) == 0) {
            getchar(); // clear newline
            printf("Enter New Name: ");
            fgets(s.name,sizeof(s.name),stdin);
            s.name[strcspn(s.name,"\n")] = '\0';
            printf("Enter New Marks: ");
            scanf("%d",&s.marks);
            found = 1;
        }
        fwrite(&s,sizeof(s),1,temp);
    }

    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat","students.dat");

    if(found) printf("\nRecord Updated Successfully!");
    else printf("\nStudent Not Found!");
}

void deleteStudent() {
    FILE *fp,*temp;
    struct Student s;
    char roll[20];
    int found = 0;

    fp = fopen("students.dat","rb");
    temp = fopen("temp.dat","wb");

    if(fp == NULL || temp == NULL) {
        printf("\nFile Error!\n");
        return;
    }

    printf("\nEnter Roll Number to Delete: ");
    scanf("%s",roll);

    while(fread(&s,sizeof(s),1,fp)) {
        if(strcmp(s.roll,roll) == 0) {
            found = 1;
            continue; // skip writing this record
        }
        fwrite(&s,sizeof(s),1,temp);
    }

    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat","students.dat");

    if(found) printf("\nStudent Deleted Successfully!");
    else printf("\nStudent Not Found!");
}
