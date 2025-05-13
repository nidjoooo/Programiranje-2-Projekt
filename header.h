#ifndef HEADER_H
#define HEADER_H

#define MAX_NAME_LENGTH 51
#define MAX_EXERCISE_NAME_LENGTH 51

// Definicija struktura za pohranu podataka
typedef struct exercise {
    char name[MAX_EXERCISE_NAME_LENGTH];  // Ime vježbe
    int sets;                             // Broj serija
    int reps;                             // Broj ponavljanja
    float weight;                         // Težina
} EXERCISE;

typedef struct workoutEntry {
    char date[11];                        // Datum treninga (DD/MM/YYYY)
    char muscleGroup[MAX_NAME_LENGTH];    // Ciljna mišićna skupina (push/pull/legs)
    EXERCISE exercises[10];               // Niz vježbi (do 10 vježbi po treningu)
    int numExercises;                     // Broj vježbi na treningu
    float duration;                       // Trajanje treninga u minutama
    float progress;                       // Osobni napredak (postotak ili neki drugi indikator)
} WORKOUT_ENTRY;

// Definicije za rad sa datotekama
typedef struct workoutData {
    int totalEntries;                     // Ukupno unesenih treninga
    WORKOUT_ENTRY* entries;               // Dinamički niz treninga
} WORKOUT_DATA;

// Enum za izbornik
enum menu {
    addWorkout = 1,
    viewWorkouts = 2,
    deleteWorkout = 3,
    deleteFile = 4,
    close = 5
};

// Enum za podizbornik (ako postoji)
enum subMenu {
    viewByDate = 1,
    viewByMuscleGroup = 2,
    searchByExercise = 3,
    sortWorkouts = 4
};

// Deklaracije funkcija
void addWorkout(void);                   // Funkcija za unos novog treninga
void viewWorkouts(void);                 // Funkcija za pregled svih treninga
void deleteWorkout(void);                // Funkcija za brisanje određenog treninga
void deleteFile(void);                   // Funkcija za brisanje cijele datoteke
void sortWorkouts(void);                 // Funkcija za sortiranje treninga (npr. po datumu)
void searchByExercise(void);             // Funkcija za pretragu treninga prema vježbi
int exitProgram(void);                   // Funkcija za izlazak iz programa

#endif // HEADER_H
