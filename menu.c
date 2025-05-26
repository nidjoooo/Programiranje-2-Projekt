#include "header.h"
#include "search.h"

extern Workout* workouts;
extern int workoutCount;

void showMenu() {
	while (1) {
		printf("\nMain Menu:\n");
		printf("1. Add Workout\n");
		printf("2. List Workouts\n");
		printf("3. Update Workout\n");
		printf("4. Delete Workout\n");
		printf("5. Search Workouts\n");
		printf("6. Exit\n");
		printf("Choose option: ");

		int choice;
		if (scanf("%d", &choice) != 1) {
			while (getchar() != '\n');
			printf("Invalid input\n");
			continue;
		}
		while (getchar() != '\n');

		switch (choice) {
		case MENU_ADD:
			addWorkout();
			saveToFile();
			break;
		case MENU_LIST:
			listWorkouts();
			break;
		case MENU_UPDATE:
			updateWorkout();
			saveToFile();
			break;
		case MENU_DELETE:
			deleteWorkout();
			saveToFile();
			break;
		case MENU_SEARCH:
			searchMenu();
			break;
		case MENU_EXIT:
			saveToFile();
			freeWorkouts();
			return;
		default:
			printf("Invalid option\n");
		}
	}
}
