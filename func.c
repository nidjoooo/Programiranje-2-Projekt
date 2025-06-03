#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "header.h"

Workout* workouts = NULL;
int workoutCount = 0;

void loadFromFile() {
    FILE* file = fopen("ironflow.bin", "rb");
    if (!file) {
        return;
    }

    if (fread(&workoutCount, sizeof(int), 1, file) != 1) {
        fclose(file);
        return;
    }

    if (workoutCount <= 0) {
        fclose(file);
        workouts = NULL;
        return;
    }

    workouts = malloc(sizeof(Workout) * workoutCount);
    if (!workouts) {
        fclose(file);
        return;
    }

    if (fread(workouts, sizeof(Workout), workoutCount, file) != (size_t)workoutCount) {
        free(workouts);
        workouts = NULL;
        workoutCount = 0;
    }

    fclose(file);
}

void saveToFile() {
    FILE* file = fopen("ironflow.bin", "wb");
    if (!file) {
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
    
    getchar(); 
    printf("Enter date: ");
    fgets(newEntry->date, sizeof(newEntry->date), stdin);
    newEntry->date[strcspn(newEntry->date, "\n")] = 0;
    
    printf("Enter target muscle group: ");
    fgets(newEntry->muscleGroup, sizeof(newEntry->muscleGroup), stdin);
    newEntry->muscleGroup[strcspn(newEntry->muscleGroup, "\n")] = 0;
    
    printf("Total number of exercises performed: ");
    scanf("%d", &newEntry->allExercise);
    
    getchar(); 
    printf("Most challenging exercise: ");
    fgets(newEntry->hardestExercise, sizeof(newEntry->hardestExercise), stdin);
    newEntry->hardestExercise[strcspn(newEntry->hardestExercise, "\n")] = 0;
    
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

void editWorkout(int index) {
    Workout* entry = &workouts[index];

    printf("Updating workout #%d:\n", index + 1);

    printf("Enter first name: ");
    scanf("%50s", entry->name);

    printf("Enter last name: ");
    scanf("%50s", entry->surname);

    printf("Enter age: ");
    scanf("%u", &entry->age);

    printf("Enter weight (kg): ");
    scanf("%f", &entry->weight);

    printf("Enter height (cm): ");
    scanf("%f", &entry->height);

    printf("Enter date: ");
    scanf("%50s", entry->date);

    printf("Enter target muscle group: ");
    scanf("%50s", entry->muscleGroup);

    printf("Total number of exercises performed: ");
    scanf("%d", &entry->allExercise);
    getchar(); 

    printf("Most challenging exercise: ");
    fgets(entry->hardestExercise, sizeof(entry->hardestExercise), stdin);
    entry->hardestExercise[strcspn(entry->hardestExercise, "\n")] = '\0'; 

    printf("Number of sets: ");
    scanf("%d", &entry->sets);

    printf("Number of reps: ");
    scanf("%d", &entry->reps);

    printf("Weight used in exercise (kg): ");
    scanf("%f", &entry->weightExercise);

    printf("Progress rating (1-10): ");
    scanf("%d", &entry->progress);
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

    editWorkout(index - 1);
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
