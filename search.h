#ifndef SEARCH_H
#define SEARCH_H

#include "header.h"

void searchMenu();

void searchByUser();
void searchByMuscleGroup();
void searchByDate();

int compareWorkoutsByUser(const void* a, const void* b);
int compareWorkoutsByMuscleGroup(const void* a, const void* b);
int compareWorkoutsByDate(const void* a, const void* b);

#endif
