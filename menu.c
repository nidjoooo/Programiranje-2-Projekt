#define _CRT_SECURE_NO_WARNINGS

#include "header.h"
#include "search.h"

void showMainMenu() {
    int choice;
    do {
        printf("\n==== IronFlow Workout Tracker ====\n");
        printf("1. Add workout\n");
        printf("2. List all workouts\n");
        printf("3. Update a workout\n");
        printf("4. Delete a workout\n");
        printf("5. Search workouts\n");
        printf("6. Sort workouts\n");
        printf("7. Rename data file\n");
        printf("8. Remove data file\n");
        printf("9. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case MENU_ADD:
            addWorkout();
            break;
        case MENU_LIST:
            listWorkouts();
            break;
        case MENU_UPDATE:
            updateWorkout();
            break;
        case MENU_DELETE:
            deleteWorkout();
            break;
        case MENU_SEARCH:
            searchMenu();
            break;
        case MENU_SORT:
            sortWorkouts();
            saveToFile();
            break;
        case MENU_RENAME_FILE: {
            char oldName[100], newName[100];
            FILE* fileCheck = NULL;

            printf("\n--- Rename Data File ---\n");
            printf("Enter current file name (e.g. ironflow.bin): ");
            scanf("%99s", oldName);

            fileCheck = fopen(oldName, "rb");
            if (!fileCheck) {
                printf("Error: File '%s' does not exist or cannot be opened.\n", oldName);
                break;
            }
            fclose(fileCheck);

            printf("Enter new file name: ");
            scanf("%99s", newName);
            fileCheck = fopen(newName, "rb");
            if (fileCheck) {
                fclose(fileCheck);
                char answer;
                printf("File '%s' already exists. Overwrite? (y/n): ", newName);
                scanf(" %c", &answer);
                if (answer != 'y' && answer != 'Y') {
                    printf("Rename cancelled.\n");
                    break;
                }
                if (remove(newName) != 0) {
                    printf("Error deleting existing file: %s\n", strerror(errno));
                    break;
                }
            }

            if (rename(oldName, newName) == 0) {
                printf("File renamed successfully to '%s'.\n", newName);
            }
            else {
                printf("Error renaming file: %s\n", strerror(errno));
            }
            break;
        }
        case MENU_REMOVE_FILE: {
            char filename[100];
            printf("\n--- Remove Data File ---\n");
            printf("Enter file name to remove (e.g. ironflow.bin): ");
            scanf("%99s", filename);

            FILE* fileCheck = fopen(filename, "rb");
            if (!fileCheck) {
                printf("Error: File '%s' does not exist or cannot be opened.\n", filename);
                break;
            }
            fclose(fileCheck);

            if (remove(filename) == 0) {
                printf("File '%s' removed successfully.\n", filename);
            }
            else {
                printf("Error removing file '%s': %s\n", filename, strerror(errno));
            }
            break;
        }
        case MENU_EXIT:
            saveToFile();
            freeWorkouts();
            printf("Thank you for using IronFlow!\n");
            break;
        default:
            printf("Invalid input. Please try again.\n");
            break;
        }
    } while (choice != MENU_EXIT);
}
