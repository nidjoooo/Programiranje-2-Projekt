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
            printf("Enter current file name: ");
            scanf("%99s", oldName);
            printf("Enter new file name: ");
            scanf("%99s", newName);

            if (rename(oldName, newName) == 0) {
                printf("File renamed successfully to '%s'.\n", newName);
            }
            else {
                printf("Error renaming file: %s\n", strerror(errno));
            }
            break;
        }
        case MENU_REMOVE_FILE:
            if (remove("ironflow.bin") == 0)
                printf("File removed successfully.\n");
            else
                perror("Error removing file");
            break;
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
