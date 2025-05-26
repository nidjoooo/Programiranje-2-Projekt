#include "header.h"

extern Workout* workouts;
extern int workoutCount;

void showMenu();

int main() {
	loadFromFile();
	showMenu();
	return 0;
}
