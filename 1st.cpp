#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ADMIN_PASSWORD "admin$123"
#define ANNUAL_FEES 175000
#define FILE_PATH "C:\\Users\\cb131\\OneDrive\\Desktop\\Students.csv"

struct Student {
    int rollnumber;
    char name[100];
    char phone[100];
    float percentage;
    float feesPaid;
    char password[20];
    struct Student *next;
};

struct Student *insert(struct Student *head, int rollnumber, const char *name, const char *phone, float percentage, float feesPaid, const char *password);
void displayStudent(struct Student *student);
void updateStudent(struct Student *head);
struct Student *deleteStudent(struct Student *head, int rollnumber);
void studentLogin(struct Student *head);
int adminLogin();
void saveToFile(struct Student *head);
struct Student *loadFromFile();
void displayAllStudents(struct Student *head);

struct Student *insert(struct Student *head, int rollnumber, const char *name, const char *phone, float percentage, float feesPaid, const char *password) {
    struct Student *student = (struct Student *)malloc(sizeof(struct Student));
    if (student == NULL) {
        printf("Memory allocation failed!\n");
        return head;
    }

    student->rollnumber = rollnumber;
    strcpy(student->name, name);
    strcpy(student->phone, phone);
    student->percentage = percentage;
    student->feesPaid = feesPaid;
    strcpy(student->password, password);
    student->next = head;
    head = student;

    saveToFile(head);
    return head;
}

void displayStudent(struct Student *student) {
    printf("+------------+----------------------+------------+------------+-------------+------------+-------------+\n");
    printf("| Roll No.   | Name                 | Phone      | Percentage | Fees Paid   | Fees Due   | Password    |\n");
    printf("+------------+----------------------+------------+------------+-------------+------------+-------------+\n");
    float due = ANNUAL_FEES - student->feesPaid;
    fprintf(stdout, "| %-10d | %-20s | %-10s | %-9.2f%% | ?%-10.2f | ?%-9.2f | %-11s |\n",
            student->rollnumber, student->name, student->phone,
            student->percentage, student->feesPaid, due > 0 ? due : 0.0, student->password);
    printf("+------------+----------------------+------------+------------+-------------+------------+-------------+\n");
}

void updateStudent(struct Student *head) {
    int roll;
    printf("\nEnter Roll Number to Update: ");
    scanf("%d", &roll);

    struct Student *temp = head;
    while (temp != NULL) {
        if (temp->rollnumber == roll) {
            printf("Updating details for Roll Number %d\n", roll);
            printf("Enter New Name: ");
            scanf(" %[^\n]s", temp->name);
            printf("Enter New Phone: ");
            scanf("%s", temp->phone);
            printf("Enter New Percentage: ");
            scanf("%f", &temp->percentage);
            printf("Enter Additional Fees Paid: ");
            float newFees;
            scanf("%f", &newFees);
            temp->feesPaid += newFees;
            printf("Student details updated successfully!\n");
            saveToFile(head);
            return;
        }
        temp = temp->next;
    }
    printf("Student with Roll Number %d not found!\n", roll);
}

struct Student *deleteStudent(struct Student *head, int rollnumber) {
    struct Student *temp = head, *prev = NULL;

    if (temp != NULL && temp->rollnumber == rollnumber) {
        head = temp->next;
        free(temp);
        printf("Student with Roll Number %d deleted successfully!\n", rollnumber);
        saveToFile(head);
        return head;
    }

    while (temp != NULL && temp->rollnumber != rollnumber) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Student with Roll Number %d not found!\n", rollnumber);
        return head;
    }

    prev->next = temp->next;
    free(temp);
    printf("Student with Roll Number %d deleted successfully!\n", rollnumber);
    saveToFile(head);
    return head;
}

void studentLogin(struct Student *head) {
    int roll;
    char password[20];

    printf("\n======== STUDENT LOGIN ========\n");
    printf("Enter Roll Number: ");
    scanf("%d", &roll);
    printf("Enter Password: ");
    scanf("%s", password);

    struct Student *temp = head;
    while (temp != NULL) {
        if (temp->rollnumber == roll && strcmp(temp->password, password) == 0) {
            printf("\nLogin successful!\n");
            displayStudent(temp);
            return;
        }
        temp = temp->next;
    }
    printf("Invalid Roll Number or Password!\n");
}

int adminLogin() {
    char password[20];
    printf("\n======== ADMIN LOGIN ========\n");
    printf("Enter Admin Password: ");
    scanf("%s", password);

    if (strcmp(password, ADMIN_PASSWORD) == 0) {
        printf("Admin Login successful!\n");
        return 1;
    } else {
        printf("Incorrect password! Access denied.\n");
        return 0;
    }
}

void saveToFile(struct Student *head) {
    FILE *file = fopen(FILE_PATH, "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fprintf(file, "Roll No.,Name,Phone,Percentage,Fees Paid,Fees Due,Password\n");

    struct Student *temp = head;
    while (temp != NULL) {
        float due = ANNUAL_FEES - temp->feesPaid;
        due = due > 0 ? due : 0;
        fprintf(file, "%d,%s,%s,%.2f,%.2f,%.2f,%s\n",
                temp->rollnumber, temp->name, temp->phone, temp->percentage, temp->feesPaid, due, temp->password);
        temp = temp->next;
    }
    fclose(file);
}

struct Student *loadFromFile() {
    FILE *file = fopen(FILE_PATH, "r");
    if (file == NULL) {
        printf("No existing data found. Starting fresh.\n");
        return NULL;
    }

    struct Student *head = NULL;
    char line[512];
    fgets(line, sizeof(line), file); // Skip header

    while (fgets(line, sizeof(line), file)) {
        struct Student *student = (struct Student *)malloc(sizeof(struct Student));
        sscanf(line, "%d,%99[^,],%99[^,],%f,%f,%*f,%19s", 
               &student->rollnumber, student->name, student->phone, &student->percentage, &student->feesPaid, student->password);

        student->next = head;
        head = student;
    }

    fclose(file);
    return head;
}

void displayAllStudents(struct Student *head) {
    if (head == NULL) {
        printf("No student records available.\n");
        return;
    }
    printf("+------------+----------------------+------------+------------+-------------+------------+-------------+\n");
    printf("| Roll No.   | Name                 | Phone      | Percentage | Fees Paid   | Fees Due   | Password    |\n");
    printf("+------------+----------------------+------------+------------+-------------+------------+-------------+\n");

    struct Student *temp = head;
    while (temp != NULL) {
        float due = ANNUAL_FEES - temp->feesPaid;
        fprintf(stdout, "| %-10d | %-20s | %-10s | %-9.2f%% | ?%-10.2f | ?%-9.2f | %-11s |\n",
                temp->rollnumber, temp->name, temp->phone,
                temp->percentage, temp->feesPaid, due > 0 ? due : 0.0, temp->password);
        temp = temp->next;
    }
    printf("+------------+----------------------+------------+------------+-------------+------------+-------------+\n");
}

// MAIN FUNCTION
int main() {
    struct Student *head = loadFromFile();
    int choice, roll;
    char name[100], phone[100], password[20];
    float percentage, feesPaid;

    while (1) {
        printf("\n===========================================\n");
        printf("        STUDENT MANAGEMENT SYSTEM         \n");
        printf("===========================================\n");
        printf("1. Admin Login\n2. Student Login\n3. Exit\nChoose: ");
        scanf("%d", &choice);

        if (choice == 1) {
            if (!adminLogin()) continue;

            while (1) {
                printf("\n===========================================\n");
                printf("               ADMIN MENU                  \n");
                printf("===========================================\n");
                printf("1. Insert Student\n2. Display Students\n3. Update Student\n4. Delete Student\n5. Logout\nChoose: ");
                scanf("%d", &choice);

                switch (choice) {
                    case 1:
                        printf("Enter Roll Number: ");
                        scanf("%d", &roll);
                        printf("Enter Name: ");
                        scanf(" %[^\n]s", name);
                        printf("Enter Phone: ");
                        scanf("%s", phone);
                        printf("Enter Percentage: ");
                        scanf("%f", &percentage);
                        printf("Enter Fees Paid: ");
                        scanf("%f", &feesPaid);
                        printf("Set Student Password: ");
                        scanf("%s", password);
                        head = insert(head, roll, name, phone, percentage, feesPaid, password);
                        printf("Student added successfully & auto-saved!\n");
                        break;

                    case 2:
                        displayAllStudents(head);
                        break;

                    case 3:
                        updateStudent(head);
                        break;

                    case 4:
                        printf("Enter Roll Number to Delete: ");
                        scanf("%d", &roll);
                        head = deleteStudent(head, roll);
                        break;

                    case 5:
                        printf("Logging out...\n");
                        goto mainMenu;

                    default:
                        printf("Invalid choice! Please try again.\n");
                }
            }
        } 
        else if (choice == 2) {
            studentLogin(head);
        } 
        else if (choice == 3) {
            printf("Exiting...\n");
            return 0;
        } 
        else {
            printf("Invalid choice! Please try again.\n");
        }

    mainMenu:
        continue;
    }
