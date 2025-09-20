#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ------------------ ADD FUNCTION ------------------
// Adds a new patient to the file
void add()
{
    struct patient
    {
        char name[20];        // Patient's name
        int age;              // Patient's age
        long long int phone;  // Patient's phone number
        char disease[60];     // Patient's disease
    } p;

    printf("Adding a new patient\n");

    printf("Enter the name: ");  
    scanf("%s", p.name); // Single-word names only

    printf("Enter the age: ");
    scanf("%d", &p.age);

    printf("Enter the mobile number: ");
    scanf("%lld", &p.phone);

    printf("Enter the disease: ");
    scanf("%s", p.disease); // Single-word disease

    FILE *fp = fopen("patients.txt", "a"); // Open file in append mode
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    fprintf(fp, "%s %d %lld %s\n", p.name, p.age, p.phone, p.disease);
    fclose(fp);
    printf("Patient added successfully!\n");
}

// ------------------ DISCHARGE FUNCTION ------------------
// Removes a patient from the file
void discharge()
{
    char patient_name[30];
    printf("Enter the name of the patient to discharge: ");
    scanf("%s", patient_name);

    FILE *fp = fopen("patients.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (fp == NULL || temp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    char pname[30], disease[50];
    int age;
    long long int phone;
    int found = 0;

    while (fscanf(fp, "%s %d %lld %s", pname, &age, &phone, disease) == 4)
    {
        if (strcmp(pname, patient_name) == 0)
        {
            found = 1;
            printf("Patient discharged successfully!\n");
            continue; // Skip writing this patient to temp
        }
        fprintf(temp, "%s %d %lld %s\n", pname, age, phone, disease);
    }

    fclose(fp);
    fclose(temp);

    remove("patients.txt");
    rename("temp.txt", "patients.txt");

    if (!found)
        printf("Patient not found!\n");
}

// ------------------ SEARCH FUNCTION ------------------
// Searches for a patient by name
void search()
{
    char patientname[30];
    printf("Enter the patient name to search: ");
    scanf("%s", patientname);

    FILE *fp = fopen("patients.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    char pname[30], disease[50];
    int age;
    long long int phone;
    int found = 0;

    while (fscanf(fp, "%s %d %lld %s", pname, &age, &phone, disease) == 4)
    {
        if (strcmp(pname, patientname) == 0)
        {
            found = 1;
            printf("\n--- Patient Found ---\n");
            printf("Name: %s\nAge: %d\nMobile: %lld\nDisease: %s\n", pname, age, phone, disease);
            break;
        }
    }

    fclose(fp);

    if (!found)
        printf("Patient not found!\n");
}

// ------------------ UPDATE FUNCTION ------------------
// Updates a patient's details
void update()
{
    char patienttname[30];
    printf("Enter the name of the patient to update: ");
    scanf("%s", patienttname);

    FILE *fp = fopen("patients.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (fp == NULL || temp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    char pname[30], disease[50];
    int age;
    long long int phone;
    int found = 0;

    while (fscanf(fp, "%s %d %lld %s", pname, &age, &phone, disease) == 4)
    {
        if (strcmp(pname, patienttname) == 0)
        {
            found = 1;
            printf("Enter the new details:\n");

            printf("New Name: ");
            scanf("%s", pname); 
            printf("New Age: ");
            scanf("%d", &age);   
            printf("New Mobile: ");
            scanf("%lld", &phone); 
            printf("New Disease: ");
            scanf("%s", disease);  

            printf("Patient details updated successfully!\n");
        }

        fprintf(temp, "%s %d %lld %s\n", pname, age, phone, disease);
    }

    fclose(fp);
    fclose(temp);

    remove("patients.txt");
    rename("temp.txt", "patients.txt");

    if (!found)
        printf("Patient not found!\n");
}

// ------------------ SHOW MENU FUNCTION ------------------
// Displays menu options and calls functions
void showmenu()
{
    int choice;
    while (1)
    {
        printf("\n==============================\n");
        printf(" Welcome to Hospital Management System \n");
        printf("==============================\n\n");

        printf("-------- SHOW MENU ---------\n");
        printf("1) Add a patient "); // -> Calls add() function\n
        printf("2) Discharge\n");//-> Calls discharge() function
        printf("3) Update\n");//           -> Calls update() function
        printf("4) Search a patient\n");// -> Calls search() function\n
        printf("5) Exit \n");//     -> Exits the program

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            add();
            break;
        case 2:
            discharge();
            break;
        case 3:
            update();
            break;
        case 4:
            search();
            break;
        case 5:
            printf("Exiting...\nThank you for using the Hospital Management System!\n");
            exit(0);
        default:
            printf("Invalid choice! Please try again.\n");
        }
    }
}

// ------------------ LOGIN FUNCTION ------------------
// Simple login with max 3 attempts
int login()
{
    char name[20], password[20];
    int attempts = 0;

    while (attempts < 3)
    {
        printf("Enter user name: ");
        scanf("%s", name);
        printf("Enter user password: ");
        scanf("%s", password);

        if (strcmp(name, "Toton") == 0 && strcmp(password, "900295") == 0)
        {
            printf("Login Successfully!\n");
            return 1;
        }
        else
        {
            printf("Incorrect! Please try again.\n");
            attempts++;
        }
    }

    printf("Can't login. Access denied.\n");
    return 0;
}

// ------------------ MAIN FUNCTION ------------------
int main()
{
    if (login())
    {
        showmenu(); // Show menu after successful login
    }
    return 0;
}
