#define _CRT_SECURE_NO_WARNINGS
#include "header.h"

#define FILE_NAME "workouts.dat"

static Workout* workouts = NULL;
static int workoutCount = 0;

Workout* getWorkouts() { return workouts; }
int getWorkoutCount() { return workoutCount; }

void freeWorkouts() {
	if (workouts != NULL) {
		free(workouts);
		workouts = NULL;
		workoutCount = 0;
	}
}

void loadFromFile() {
	FILE* file = fopen(FILE_NAME, "rb");
	if (!file) {
		perror("Error opening file for reading");
		return;
	}

	fseek(file, 0, SEEK_END);
	long size = ftell(file);
	rewind(file);

	if (size == 0) {
		fclose(file);
		return;
	}

	workoutCount = (int)(size / sizeof(Workout));
	workouts = (Workout*)malloc(sizeof(Workout) * workoutCount);
	if (!workouts) {
		perror("Memory allocation failed");
		fclose(file);
		return;
	}

	size_t readCount = fread(workouts, sizeof(Workout), workoutCount, file);
	if (readCount != workoutCount) {
		perror("Reading file failed");
		freeWorkouts();
	}

	fclose(file);
}

void saveToFile() {
	FILE* file = fopen(FILE_NAME, "wb");
	if (!file) {
		perror("Error opening file for writing");
		return;
	}

	size_t writeCount = fwrite(workouts, sizeof(Workout), workoutCount, file);
	if (writeCount != workoutCount) {
		perror("Writing file failed");
	}

	fclose(file);
}

inline static void clearInputBuffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

void addWorkout() {
	Workout* temp = realloc(workouts, sizeof(Workout) * (workoutCount + 1));
	if (!temp) {
		perror("Memory allocation failed");
		return;
	}
	workouts = temp;

	Workout* w = &workouts[workoutCount];

	printf("Enter user: ");
	if (!fgets(w->user, MAX_NAME_LENGTH, stdin)) return;
	strtok(w->user, "\n");

	printf("Enter date: ");
	if (!fgets(w->date, sizeof(w->date), stdin)) return;
	strtok(w->date, "\n");

	printf("Enter muscle group: ");
	if (!fgets(w->muscleGroup, sizeof(w->muscleGroup), stdin)) return;
	strtok(w->muscleGroup, "\n");

	printf("Enter exercise: ");
	if (!fgets(w->exercise, sizeof(w->exercise), stdin)) return;
	strtok(w->exercise, "\n");

	printf("Enter sets: ");
	if (scanf("%d", &w->sets) != 1) { clearInputBuffer(); return; }
	printf("Enter reps: ");
	if (scanf("%d", &w->reps) != 1) { clearInputBuffer(); return; }
	printf("Enter weight (kg): ");
	if (scanf("%f", &w->weight) != 1) { clearInputBuffer(); return; }
	printf("Enter duration (min): ");
	if (scanf("%d", &w->duration) != 1) { clearInputBuffer(); return; }
	clearInputBuffer();

	workoutCount++;
}

void listWorkouts() {
	if (workoutCount == 0) {
		printf("No workouts recorded.\n");
		return;
	}
	for (int i = 0; i < workoutCount; i++) {
		Workout* w = &workouts[i];
		printf("[%d] %s | %s | %s | %s | %d x %d x %.2fkg | %dmin\n",
			i + 1, w->user, w->date, w->muscleGroup, w->exercise,
			w->sets, w->reps, w->weight, w->duration);
	}
}

void updateWorkout() {
	listWorkouts();
	printf("Enter workout number to update: ");
	int index;
	if (scanf("%d", &index) != 1) {
		clearInputBuffer();
		return;
	}
	clearInputBuffer();

	index--;
	if (index < 0 || index >= workoutCount) {
		printf("Invalid workout number.\n");
		return;
	}

	Workout* w = &workouts[index];
	char buffer[MAX_NAME_LENGTH];

	printf("Update user [%s]: ", w->user);
	if (fgets(buffer, MAX_NAME_LENGTH, stdin)) {
		if (buffer[0] != '\n') {
			strtok(buffer, "\n");
			strcpy(w->user, buffer);
		}
	}

	printf("Update date [%s]: ", w->date);
	if (fgets(buffer, sizeof(w->date), stdin)) {
		if (buffer[0] != '\n') {
			strtok(buffer, "\n");
			strcpy(w->date, buffer);
		}
	}

	printf("Update muscle group [%s]: ", w->muscleGroup);
	if (fgets(buffer, sizeof(w->muscleGroup), stdin)) {
		if (buffer[0] != '\n') {
			strtok(buffer, "\n");
			strcpy(w->muscleGroup, buffer);
		}
	}

	printf("Update exercise [%s]: ", w->exercise);
	if (fgets(buffer, sizeof(w->exercise), stdin)) {
		if (buffer[0] != '\n') {
			strtok(buffer, "\n");
			strcpy(w->exercise, buffer);
		}
	}

	printf("Update sets [%d]: ", w->sets);
	if (fgets(buffer, sizeof(buffer), stdin)) {
		if (buffer[0] != '\n') w->sets = atoi(buffer);
	}

	printf("Update reps [%d]: ", w->reps);
	if (fgets(buffer, sizeof(buffer), stdin)) {
		if (buffer[0] != '\n') w->reps = atoi(buffer);
	}

	printf("Update weight [%.2f]: ", w->weight);
	if (fgets(buffer, sizeof(buffer), stdin)) {
		if (buffer[0] != '\n') w->weight = (float)atof(buffer);
	}

	printf("Update duration [%d]: ", w->duration);
	if (fgets(buffer, sizeof(buffer), stdin)) {
		if (buffer[0] != '\n') w->duration = atoi(buffer);
	}
}

void deleteWorkout() {
	listWorkouts();
	printf("Enter workout number to delete: ");
	int index;
	if (scanf("%d", &index) != 1) {
		clearInputBuffer();
		return;
	}
	clearInputBuffer();

	index--;
	if (index < 0 || index >= workoutCount) {
		printf("Invalid workout number.\n");
		return;
	}

	for (int i = index; i < workoutCount - 1; i++) {
		workouts[i] = workouts[i + 1];
	}

	workoutCount--;

	if (workoutCount > 0) {
		Workout* temp = realloc(workouts, sizeof(Workout) * workoutCount);
		if (temp) workouts = temp;
		else perror("Memory reallocation failed");
	}
	else {
		freeWorkouts();
	}
}

int compareWorkoutsByUser(const void* a, const void* b) {
	const Workout* wa = (const Workout*)a;
	const Workout* wb = (const Workout*)b;
	return strcmp(wa->user, wb->user);
}

int compareWorkoutsByMuscleGroup(const void* a, const void* b) {
	const Workout* wa = (const Workout*)a;
	const Workout* wb = (const Workout*)b;
	return strcmp(wa->muscleGroup, wb->muscleGroup);
}

int compareWorkoutsByDate(const void* a, const void* b) {
	const Workout* wa = (const Workout*)a;
	const Workout* wb = (const Workout*)b;
	return strcmp(wa->date, wb->date);
}
