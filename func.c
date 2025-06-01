#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "header.h"

void loadFromFile() {
    FILE* file = fopen("ironflow.bin", "ab+");
    if (!file) {
        printf("File does not exist yet. Starting without loaded data.\n");
        return;
    }

    fread(&workoutCount, sizeof(int), 1, file);
    workouts = malloc(sizeof(Workout) * workoutCount);
    if (!workouts) {
        perror("Memory allocation failed");
        fclose(file);
        return;
    }

    fread(workouts, sizeof(Workout), workoutCount, file);
    fclose(file);
}

void saveToFile() {
    FILE* file = fopen("ironflow.bin", "ab+");
    if (!file) {
        perror("Failed to open file for writing");
        return;
    }

    fwrite(&workoutCount, sizeof(int), 1, file);
    fwrite(workouts, sizeof(Workout), workoutCount, file);
    fclose(file);
}

void freeWorkouts() {
    free(workouts);
    workouts = NULL;
    workoutCount = 0;
}

void addWorkout() {
    workouts = (Workout*)realloc(workouts, (workoutCount + 1) * sizeof(Workout));
    if (!workouts) {
        perror("Failed to expand memory");
        return;
    }

    Workout* newEntry = &workouts[workoutCount];

    printf("Enter first name: ");
    scanf("%50s", newEntry->name);
    printf("Enter last name: ");
    scanf("%50s", newEntry->surname);
    printf("Enter age: ");
    scanf("%u", &newEntry->age);
    printf("Enter weight (kg): ");
    scanf("%f", &newEntry->weight);
    printf("Enter height (cm): ");
    scanf("%f", &newEntry->height);
    printf("Enter date: ");
    scanf("%50s", newEntry->date);
    printf("Enter target muscle group: ");
    scanf("%50s", newEntry->muscleGroup);
    printf("Total number of exercises performed: ");
    scanf("%d", &newEntry->allExercise);
    printf("Most challenging exercise: ");
    scanf("%50s", newEntry->hardestExercise);
    printf("Number of sets: ");
    scanf("%d", &newEntry->sets);
    printf("Number of reps: ");
    scanf("%d", &newEntry->reps);
    printf("Weight used in exercise (kg): ");
    scanf("%f", &newEntry->weightExercise);
    printf("Progress rating (1-10): ");
    scanf("%d", &newEntry->progress);

    workoutCount++;
    saveToFile();
}

void listWorkouts() {
    if (!workoutCount) {
        printf("No workouts recorded.\n");
        return;
    }

    for (int i = 0; i < workoutCount; i++) {
        Workout w = workouts[i];
        printf("\nWorkout #%d\n", i + 1);
        printf("First name: %s\n", w.name);
        printf("Last name: %s\n", w.surname);
        printf("Age: %u\n", w.age);
        printf("Weight: %.2f kg\n", w.weight);
        printf("Height: %.2f cm\n", w.height);
        printf("Date: %s\n", w.date);
        printf("Muscle group: %s\n", w.muscleGroup);
        printf("Total exercises: %d\n", w.allExercise);
        printf("Most challenging exercise: %s\n", w.hardestExercise);
        printf("Sets: %d\n", w.sets);
        printf("Reps: %d\n", w.reps);
        printf("Weight used: %.2f kg\n", w.weightExercise);
        printf("Progress: %d/10\n", w.progress);
    }
}

void updateWorkout() {
    int index;
    listWorkouts();
    printf("\nEnter the workout number to update: ");
    scanf("%d", &index);

    if (index < 1 || index > workoutCount) {
        printf("Invalid selection.\n");
        return;
    }

    index--;
    printf("Updating record...\n");
    addWorkout();  
    workouts[index] = workouts[workoutCount - 1];
    workoutCount--;
    saveToFile();
}

void deleteWorkout() {
    int index;
    listWorkouts();
    printf("\nEnter the workout number to delete: ");
    scanf("%d", &index);

    if (index < 1 || index > workoutCount) {
        printf("Invalid selection.\n");
        return;
    }

    index--;
    for (int i = index; i < workoutCount - 1; i++) {
        workouts[i] = workouts[i + 1];
    }

    workoutCount--;
    workouts = (Workout*)realloc(workouts, workoutCount * sizeof(Workout));
    saveToFile();
}
