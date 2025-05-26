#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"
#include "search.h"

void searchByUser() {
  char firstName[30];
  char lastName[30];
  int n, found = 0;

  FILE* fp = fopen("workoutfile.bin", "rb");
  if (!fp) {
      printf("Datoteka nije pronađena.\n");
      return;
    }
  
  fread(&n, sizeof(int), 1, fp);

  WORKOUT* workouts = (WORKOUT*)malloc(n * sizeof(WORKOUT));
  if (!workouts) {
    perror("Greska u alokaciji memorije");
    fclose(fp);
    return;
    }

  fread(workouts, sizeof(WORKOUT), n, fp);
  fclose(fp);

  printf("Unesite ime korisnika: ");
  scanf(" %29[^\n]", firstName);
  getchar();
  printf("Unesite prezime korisnika: ");
  scanf(" %29[^\n]", lastName);
  getchar();

  for (int i = 0; i < n; i++) {
  if (strcmp(workouts[i].firstName, firstName) == 0 && strcmp(workouts[i].lastName, lastName) == 0) {
  printf("\n--- Trening #%d ---\n", i + 1);
  printf("Ime: %s %s\n", workouts[i].firstName, workouts[i].lastName);
  printf("Godine: %d\n", workouts[i].age);
  printf("Težina: %.2f kg\n", workouts[i].weight);
  printf("Datum: %s\n", workouts[i].date);
  printf("Mišićna skupina: %s\n", workouts[i].muscleGroup);
  printf("Vježba: %s\n", workouts[i].exerciseName);
  printf("Serije: %d, Ponavljanja: %d\n", workouts[i].sets, workouts[i].reps);
  printf("Težina: %.2f kg\n", workouts[i].usedWeight);
  printf("Trajanje: %.2f min\n", workouts[i].duration);
  printf("Napredak: %.2f %%\n", workouts[i].progress);
  found = 1;
    }
  }

  if (!found) {
    printf("Nisu pronađeni treninzi za korisnika %s %s.\n", firstName, lastName);
  }

  free(workouts);
}
