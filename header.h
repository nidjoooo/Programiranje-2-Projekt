#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct {
    char name[51];
    char surname[51];
    unsigned int age;
    float weight;
    float height;
    char date[51];
    char muscleGroup[51];
    int allExercise;
    char hardestExercise[51];
    unsigned int sets;
    unsigned int reps;
    float weightExercise;
    unsigned int progress;
} Workout;

typedef enum {
    MENU_ADD = 1,
    MENU_LIST,
    MENU_UPDATE,
    MENU_DELETE,
    MENU_SEARCH,
    MENU_SORT,
    MENU_RENAME_FILE,
    MENU_REMOVE_FILE,
    MENU_EXIT
} MenuOptions;

typedef enum {
    SEARCH_BY_USER = 1,
    SEARCH_BY_MUSCLE_GROUP,
    SEARCH_BY_DATE
} SearchOptions;

extern Workout* workouts;
extern int workoutCount;

void loadFromFile();
void saveToFile();
void freeWorkouts();

void addWorkout();
void listWorkouts();
void updateWorkout();
void deleteWorkout();
void sortWorkouts();
Workout* findWorkout(const char* name);

inline void clearInputBuffer();

#endif
