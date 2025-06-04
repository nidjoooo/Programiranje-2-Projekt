#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "header.h"

Workout* workouts = NULL;
int workoutCount = 0;

static int compareByName(const void* a, const void* b) {
    const Workout* wa = (const Workout*)a;
    const Workout* wb = (const Workout*)b;
    return strcmp(wa->name, wb->name);
}

inline void clearInputBuffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

void sortWorkouts() {
    if (workoutCount > 1) {
        qsort(workouts, workoutCount, sizeof(Workout), compareByName);
    }
}

Workout* findWorkout(const char* name) {
    Workout key;
    strcpy(key.name, name);
    return (Workout*)bsearch(&key, workouts, workoutCount, sizeof(Workout), compareByName);
}

void loadFromFile() {
    FILE* file = fopen("ironflow.bin", "rb");
    if (!file) {
        return;
    }

    rewind(file); 

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
    sortWorkouts();
}

void saveToFile() {
    FILE* file = fopen("ironflow.bin", "wb");
    if (!file) {
        perror("Error saving file");
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
    workouts = realloc(workouts, (workoutCount + 1) * sizeof(Workout));
    if (!workouts) {
        perror("Memory reallocation failed");
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

    clearInputBuffer();
    printf("Enter date: ");
    fgets(newEntry->date, sizeof(newEntry->date), stdin);
    newEntry->date[strcspn(newEntry->date, "\n")] = 0;

    printf("Enter target muscle group: ");
    fgets(newEntry->muscleGroup, sizeof(newEntry->muscleGroup), stdin);
    newEntry->muscleGroup[strcspn(newEntry->muscleGroup, "\n")] = 0;

    printf("Total number of exercises performed: ");
    scanf("%d", &newEntry->allExercise);

    clearInputBuffer();
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
    sortWorkouts();
    saveToFile();
}

static void recursiveList(int index) {
    if (index >= workoutCount) return;
    recursiveList(index + 1);

    Workout w = workouts[index];
    printf("\nWorkout #%d\n", index + 1);
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

void listWorkouts() {
    recursiveList(0);
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
    workouts = realloc(workouts, workoutCount * sizeof(Workout));
    saveToFile();
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

    Workout* entry = &workouts[index - 1];

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

    getchar();
    printf("Enter date: ");
    fgets(entry->date, sizeof(entry->date), stdin);
    entry->date[strcspn(entry->date, "\n")] = 0;

    printf("Enter target muscle group: ");
    fgets(entry->muscleGroup, sizeof(entry->muscleGroup), stdin);
    entry->muscleGroup[strcspn(entry->muscleGroup, "\n")] = 0;

    printf("Total number of exercises performed: ");
    scanf("%d", &entry->allExercise);

    getchar();
    printf("Most challenging exercise: ");
    fgets(entry->hardestExercise, sizeof(entry->hardestExercise), stdin);
    entry->hardestExercise[strcspn(entry->hardestExercise, "\n")] = 0;

    printf("Number of sets: ");
    scanf("%d", &entry->sets);

    printf("Number of reps: ");
    scanf("%d", &entry->reps);

    printf("Weight used in exercise (kg): ");
    scanf("%f", &entry->weightExercise);

    printf("Progress rating (1-10): ");
    scanf("%d", &entry->progress);

    saveToFile();
    printf("Workout #%d updated successfully.\n", index);
}
