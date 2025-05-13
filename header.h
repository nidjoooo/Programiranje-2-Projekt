#define _CRT_SECURE_NO_WARNINGS

#pragma once

#include <stdio.h>

typedef struct workout {
    char date[11];
    char muscleGroup[51];
    char exerciseName[51];
    int sets;
    int reps;
    float weight;
    float duration;
    float progress;
} WORKOUT;

enum MainMenu {
    ADD_WORKOUT = 1,
    DELETE_WORKOUT = 2,
    DELETE_FILE = 3,
    EXIT_PROGRAM = 4
};

void addWorkout(void);
void deleteWorkout(void);
void deleteFile(void);
int exitProgram(void);

