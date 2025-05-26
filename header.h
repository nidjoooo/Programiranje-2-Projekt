#ifndef HEADER_H
#define HEADER_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_NAME_LENGTH 100
#define MAX_EXERCISE_LENGTH 100

typedef struct {
	char date[20];
	char muscleGroup[50];
	char exercise[MAX_EXERCISE_LENGTH];
	int sets;
	int reps;
	float weight;
	int duration;
	char user[MAX_NAME_LENGTH];
} Workout;

typedef enum {
	MENU_ADD = 1,
	MENU_LIST,
	MENU_UPDATE,
	MENU_DELETE,
	MENU_SEARCH,
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

void showMenu();

#endif

