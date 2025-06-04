#define _CRT_SECURE_NO_WARNINGS

#include "search.h"

void searchMenu() {
    int choice;
    printf("\n=== IronFlow: Workout Search ===\n");
    printf("1. By user\n");
    printf("2. By muscle group\n");
    printf("3. By date\n");
    printf("Choice: ");
    scanf("%d", &choice);

    switch (choice) {
    case SEARCH_BY_USER: searchByUser(); break;
    case SEARCH_BY_MUSCLE_GROUP: searchByMuscleGroup(); break;
    case SEARCH_BY_DATE: searchByDate(); break;
    default: printf("Invalid selection.\n");
    }
}

void searchByUser() {
    char firstName[51];
    printf("Enter user's first name to search: ");
    scanf("%50s", firstName);

    Workout* result = findWorkout(firstName);
    if (result) {
        printf("Found: %s %s, Date: %s\n", result->name, result->surname, result->date);
    }
    else {
        printf("User not found.\n");
    }
}

void searchByMuscleGroup() {
    char group[51];
    printf("Enter muscle group to search: ");
    scanf("%50s", group);

    for (int i = 0; i < workoutCount; i++) {
        if (strcmp(workouts[i].muscleGroup, group) == 0) {
            printf("Muscle group: %s, User: %s %s\n", group, workouts[i].name, workouts[i].surname);
        }
    }
}

void searchByDate() {
    char date[51];
    printf("Enter workout date: ");
    scanf("%50s", date);

    for (int i = 0; i < workoutCount; i++) {
        if (strcmp(workouts[i].date, date) == 0) {
            printf("Date: %s, User: %s %s\n", date, workouts[i].name, workouts[i].surname);
        }
    }
}
