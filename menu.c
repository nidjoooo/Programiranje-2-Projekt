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
        printf("6. Exit\n");
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
