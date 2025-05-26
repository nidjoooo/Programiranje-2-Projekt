#include "search.h"

extern Workout* workouts;
extern int workoutCount;

static void printWorkout(int index, const Workout* w) {
	printf("[%d] %s | %s | %s | %s | %d x %d x %.2fkg | %dmin\n",
		index + 1, w->user, w->date, w->muscleGroup,
		w->exercise, w->sets, w->reps, w->weight, w->duration);
}

void searchByUser() {
	char name[MAX_NAME_LENGTH];
	printf("Enter user name to search: ");
	if (!fgets(name, MAX_NAME_LENGTH, stdin)) return;
	strtok(name, "\n");

	qsort(workouts, workoutCount, sizeof(Workout), compareWorkoutsByUser);

	Workout key = { 0 };
	strncpy(key.user, name, MAX_NAME_LENGTH - 1);
	Workout* found = (Workout*)bsearch(&key, workouts, workoutCount, sizeof(Workout), compareWorkoutsByUser);

	int foundAny = 0;
	if (found) {
		int i = (int)(found - workouts);
		for (; i < workoutCount && strcmp(workouts[i].user, name) == 0; i++) {
			printWorkout(i, &workouts[i]);
			foundAny = 1;
		}
	}

	if (!foundAny) printf("No workouts found for user: %s\n", name);
}

void searchByMuscleGroup() {
	char muscle[50];
	printf("Enter muscle group to search: ");
	if (!fgets(muscle, sizeof(muscle), stdin)) return;
	strtok(muscle, "\n");

	qsort(workouts, workoutCount, sizeof(Workout), compareWorkoutsByMuscleGroup);

	Workout key = { 0 };
	strncpy(key.muscleGroup, muscle, sizeof(key.muscleGroup) - 1);
	Workout* found = (Workout*)bsearch(&key, workouts, workoutCount, sizeof(Workout), compareWorkoutsByMuscleGroup);

	int foundAny = 0;
	if (found) {
		int i = (int)(found - workouts);
		for (; i < workoutCount && strcmp(workouts[i].muscleGroup, muscle) == 0; i++) {
			printWorkout(i, &workouts[i]);
			foundAny = 1;
		}
	}

	if (!foundAny) printf("No workouts found for muscle group: %s\n", muscle);
}

void searchByDate() {
	char date[20];
	printf("Enter date to search: ");
	if (!fgets(date, sizeof(date), stdin)) return;
	strtok(date, "\n");

	qsort(workouts, workoutCount, sizeof(Workout), compareWorkoutsByDate);

	Workout key = { 0 };
	strncpy(key.date, date, sizeof(key.date) - 1);
	Workout* found = (Workout*)bsearch(&key, workouts, workoutCount, sizeof(Workout), compareWorkoutsByDate);

	int foundAny = 0;
	if (found) {
		int i = (int)(found - workouts);
		for (; i < workoutCount && strcmp(workouts[i].date, date) == 0; i++) {
			printWorkout(i, &workouts[i]);
			foundAny = 1;
		}
	}

	if (!foundAny) printf("No workouts found for date: %s\n", date);
}

void searchMenu() {
	while (1) {
		printf("\nSearch Menu:\n");
		printf("1. Search by User\n");
		printf("2. Search by Muscle Group\n");
		printf("3. Search by Date\n");
		printf("4. Return to Main Menu\n");
		printf("Choose option: ");

		int option;
		if (scanf("%d", &option) != 1) {
			while (getchar() != '\n');
			printf("Invalid input\n");
			continue;
		}
		while (getchar() != '\n');

		switch (option) {
		case SEARCH_BY_USER:
			searchByUser();
			break;
		case SEARCH_BY_MUSCLE_GROUP:
			searchByMuscleGroup();
			break;
		case SEARCH_BY_DATE:
			searchByDate();
			break;
		case 4:
			return;
		default:
			printf("Invalid option\n");
		}
	}
}
