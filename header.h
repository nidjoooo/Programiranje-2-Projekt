#define _CRT_SECURE_NO_WARNINGS

#pragma once

#include <stdio.h>

// Struktura za trening
typedef struct workout {
    char date[11];             // DD/MM/YYYY
    char muscleGroup[51];      // npr. Push, Pull, Legs
    char exerciseName[51];     // npr. Bench press
    int sets;                  // broj serija
    int reps;                  // broj ponavljanja
    float weight;              // tezina u kg
    float duration;            // trajanje treninga u minutama
    float progress;            // subjektivni napredak (1-100)
} WORKOUT;

// Enum za glavni izbornik
enum MainMenu {
    ADD_WORKOUT = 1,
    DELETE_WORKOUT = 2,
    DELETE_FILE = 3,
    EXIT_PROGRAM = 4
};

// Deklaracije funkcija
void addWorkout(void);
void deleteWorkout(void);
void deleteFile(void);
int exitProgram(void);
