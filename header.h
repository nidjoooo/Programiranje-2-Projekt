#ifndef HEADER_H
#define HEADER_H

#define MAX_NAME_LENGTH 51
#define MAX_EXERCISE_NAME_LENGTH 51


typedef struct exercise {
    char name[MAX_EXERCISE_NAME_LENGTH];  
    int sets;                             
    int reps;                             
    float weight;                         
} EXERCISE;

typedef struct workoutEntry {
    char date[11];                        
    char muscleGroup[MAX_NAME_LENGTH];    
    EXERCISE exercises[10];              
    int numExercises;                     
    float duration;                       
    float progress;                      
} WORKOUT_ENTRY;

typedef struct workoutData {
    int totalEntries;                     
    WORKOUT_ENTRY* entries;               
} WORKOUT_DATA;

enum menu {
    addWorkout = 1,
    viewWorkouts = 2,
    deleteWorkout = 3,
    deleteFile = 4,
    close = 5
};

enum subMenu {
    viewByDate = 1,
    viewByMuscleGroup = 2,
    searchByExercise = 3,
    sortWorkouts = 4
};

void addWorkout(void);                   
void viewWorkouts(void);                 
void deleteWorkout(void);              
void deleteFile(void);                   
void sortWorkouts(void);                 
void searchByExercise(void);             
int exitProgram(void);                 

#endif
