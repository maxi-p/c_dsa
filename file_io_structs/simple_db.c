#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100
#define DATABASE_FILE "database.sql"

typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    int age;
} Record;

// Function to create a new record
void createRecord(FILE *file) {
    Record record;
    
    printf("Enter ID: ");
    scanf("%d", &record.id);

    getchar(); // To consume newline character left by scanf
    printf("Enter Name: ");
    fgets(record.name, MAX_NAME_LENGTH, stdin);
    record.name[strcspn(record.name, "\n")] = 0;  // Remove newline from string
    
    printf("Enter Age: ");
    scanf("%d", &record.age);

    fseek(file, 0, SEEK_END);
    fwrite(&record, sizeof(Record), 1, file);
    printf("Record added successfully!\n");

    fseek(file, 0, SEEK_SET);

    while (fread(&record, sizeof(Record), 1, file)) {
        printf("%d %s %d\n", record.id, record.name, record.age);
    }
}

// Function to read all records
void readRecords(FILE *file) {
    Record record;
    fseek(file, 0, SEEK_SET);
    
    printf("Database Records:\n");
    while (fread(&record, sizeof(Record), 1, file)) {
        printf("ID: %d, Name: %s, Age: %d\n", record.id, record.name, record.age);
    }
}

// Function to update a record
void updateRecord(FILE *file) {
    int id;
    printf("Enter ID of the record to update: ");
    scanf("%d", &id);

    Record record;
    fseek(file, 0, SEEK_SET);
    int found = 0;

    while (fread(&record, sizeof(Record), 1, file)) {
        if (record.id == id) {
            found = 1;
            printf("Updating Record - ID: %d\n", record.id);
            getchar(); // To consume newline character left by scanf
            printf("Enter new Name: ");
            fgets(record.name, MAX_NAME_LENGTH, stdin);
            record.name[strcspn(record.name, "\n")] = 0; // Remove newline from string
            
            printf("Enter new Age: ");
            scanf("%d", &record.age);

            // Set file pointer to the record's position to update it
            fseek(file, -sizeof(Record), SEEK_CUR);
            fwrite(&record, sizeof(Record), 1, file);
            printf("Record updated successfully!\n");
            break;
        }
    }
    
    if (!found) {
        printf("Record with ID %d not found!\n", id);
    }
}

// Function to delete a record
FILE* deleteRecord(FILE *file) {
    int id;
    printf("Enter ID of the record to delete: ");
    scanf("%d", &id);

    FILE *tempFile = fopen("temp.txt", "wb+");
    if (tempFile == NULL) {
        printf("Unable to create temporary file.\n");
        return NULL;
    }

    Record record;
    fseek(file, 0, SEEK_SET);
    int found = 0;

    while (fread(&record, sizeof(Record), 1, file)) {
        printf("record: %d, %s, %d\n", record.id, record.name, record.age);
        if (record.id != id) {
            printf("copyting to tempfile\n");
            fwrite(&record, sizeof(Record), 1, tempFile);
        } else {
            printf("FOund\n");
            found = 1;
        }
    }

    printf("Testing the temp file: \n");
    fseek(tempFile, 0, SEEK_SET);

    while (fread(&record, sizeof(Record), 1, tempFile)) {
        printf("ID: %d, Name: %s, Age: %d\n", record.id, record.name, record.age);
    }

    fclose(file);
    fclose(tempFile);

    remove(DATABASE_FILE);  // Remove the original database file
    rename("temp.txt", DATABASE_FILE);  // Rename temp file to the original database file

    file = fopen(DATABASE_FILE, "rb+");

    if (found) {
        printf("Record with ID %d deleted successfully!\n", id);
    } else {
        printf("Record with ID %d not found!\n", id);
    }

    return file;
}

// Main function to simulate the database
int main() {
    FILE *file;
    file = fopen(DATABASE_FILE, "rb+");
    if (file == NULL) {
        file = fopen(DATABASE_FILE, "wb+");
    }

    if (file == NULL) {
        printf("Unable to open the database file.\n");
        return 1;
    }

    int choice;
    while (1) {
        printf("\nSimple Database Menu:\n");
        printf("1. Create a new record\n");
        printf("2. Read all records\n");
        printf("3. Update a record\n");
        printf("4. Delete a record\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createRecord(file);
                break;
            case 2:
                readRecords(file);
                break;
            case 3:
                updateRecord(file);
                break;
            case 4:
                file = deleteRecord(file);
                file = fopen(DATABASE_FILE, "rb+");  // Reopen after deletion
                if (file == NULL) {
                    printf("Unable to open the database file.\n");
                    return 1;
                }
                break;
            case 5:
                fclose(file);
                printf("Exiting the program.\n");
                return 0;
            default:
                printf("Invalid choice, please try again.\n");
        }
    }

    return 0;
}
