#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "header.h"

void addWorkout() {
    FILE* file = NULL;
    static int totalEntries;
    WorkoutEntry* newEntry = (WorkoutEntry*)malloc(sizeof(WorkoutEntry));
    if (!newEntry) {
        perror("Neuspješno zauzimanje memorije");
        exit(EXIT_FAILURE);
    }

    printf("Unesite datum (dd.mm.gggg.): ");
    scanf(" %10[^\n]", newEntry->date);
    getchar();

    printf("Unesite trajanje treninga (u minutama): ");
    scanf("%d", &newEntry->duration);
    getchar();

    printf("Unesite tip treninga (0-Push, 1-Pull, 2-Legs): ");
    scanf("%d", (int*)&newEntry->type);
    getchar();

    printf("Unesite broj vježbi: ");
    scanf("%d", &newEntry->exerciseCount);
    getchar();

    if (newEntry->exerciseCount > MAX_EXERCISES) {
        printf("Maksimalan broj vježbi je %d. Postavljeno na maksimalno.\n", MAX_EXERCISES);
        newEntry->exerciseCount = MAX_EXERCISES;
    }

    for (int i = 0; i < newEntry->exerciseCount; i++) {
        printf("Vježba %d:\n", i + 1);
        printf("- Naziv: ");
        scanf(" %50[^\n]", newEntry->exercises[i].name);
        getchar();

        printf("- Ciljna mišićna skupina (0-Prsa, 1-Ledja, 2-Noge, 3-Ruke, 4-Rame, 5-Core): ");
        scanf("%d", (int*)&newEntry->exercises[i].targetMuscle);
        getchar();

        printf("- Serije: ");
        scanf("%d", &newEntry->exercises[i].sets);
        getchar();

        printf("- Ponavljanja: ");
        scanf("%d", &newEntry->exercises[i].reps);
        getchar();

        printf("- Težina (kg): ");
        scanf("%f", &newEntry->exercises[i].weight);
        getchar();
    }

    printf("Osobna napomena / napredak: ");
    scanf(" %100[^\n]", newEntry->note);
    getchar();

    file = fopen("training_data.bin", "rb+");

    if (!file) {
        file = fopen("training_data.bin", "wb");
        if (!file) {
            perror("Greška pri otvaranju datoteke");
            free(newEntry);
            exit(EXIT_FAILURE);
        }

        totalEntries = 1;
        fwrite(&totalEntries, sizeof(int), 1, file);
        fwrite(newEntry, sizeof(WorkoutEntry), 1, file);
    } else {
        fread(&totalEntries, sizeof(int), 1, file);
        totalEntries++;
        rewind(file);
        fwrite(&totalEntries, sizeof(int), 1, file);
        fseek(file, 0, SEEK_END);
        fwrite(newEntry, sizeof(WorkoutEntry), 1, file);
    }

    fclose(file);
    free(newEntry);
    printf("Trening uspješno dodan.\n");
}

void deleteWorkout() {
    FILE* file = fopen("training_data.bin", "rb");
    if (!file) {
        printf("Datoteka nije pronađena.\n");
        return;
    }

    int total;
    fread(&total, sizeof(int), 1, file);
    WorkoutEntry* workouts = (WorkoutEntry*)malloc(total * sizeof(WorkoutEntry));
    if (!workouts) {
        perror("Greška u alokaciji memorije");
        fclose(file);
        return;
    }

    fread(workouts, sizeof(WorkoutEntry), total, file);
    fclose(file);

    char targetDate[11];
    printf("Unesite datum treninga koji želite obrisati (dd.mm.gggg.): ");
    scanf(" %10[^\n]", targetDate);
    getchar();

    int found = 0, index = -1;
    for (int i = 0; i < total; i++) {
        if (strcmp(workouts[i].date, targetDate) == 0) {
            found = 1;
            index = i;
            break;
        }
    }

    if (!found) {
        printf("Nema treninga s tim datumom.\n");
        free(workouts);
        return;
    }

    file = fopen("training_data.bin", "wb");
    if (!file) {
        perror("Greška pri otvaranju datoteke za pisanje");
        free(workouts);
        return;
    }

    total--;
    fwrite(&total, sizeof(int), 1, file);
    for (int i = 0; i < total + 1; i++) {
        if (i != index)
            fwrite(&workouts[i], sizeof(WorkoutEntry), 1, file);
    }

    fclose(file);
    free(workouts);
    printf("Trening obrisan.\n");
}

void listAllWorkouts() {
    FILE* file = fopen("training_data.bin", "rb");
    if (!file) {
        printf("Nema snimljenih treninga.\n");
        return;
    }

    int total;
    fread(&total, sizeof(int), 1, file);
    WorkoutEntry* data = (WorkoutEntry*)malloc(total * sizeof(WorkoutEntry));
    if (!data) {
        perror("Greška u alokaciji memorije");
        fclose(file);
        return;
    }

    fread(data, sizeof(WorkoutEntry), total, file);
    fclose(file);

    for (int i = 0; i < total; i++) {
        printf("Datum: %s\n", data[i].date);
        printf("Trajanje: %d minuta\n", data[i].duration);
        printf("Tip: %s\n", workoutTypeToStr(data[i].type));
        for (int j = 0; j < data[i].exerciseCount; j++) {
            Exercise e = data[i].exercises[j];
            printf("- Vježba: %s | Skupina: %s | Serije: %d | Ponavljanja: %d | Težina: %.2f kg\n",
                   e.name, muscleGroupToStr(e.targetMuscle), e.sets, e.reps, e.weight);
        }
        printf("Napomena: %s\n\n", data[i].note);
    }

    free(data);
}

void deleteFile() {
    char confirm;
    printf("Želite li izbrisati datoteku? (Y/n): ");
    scanf(" %c", &confirm);
    getchar();

    if (confirm == 'Y' || confirm == 'y') {
        if (remove("training_data.bin") == 0)
            printf("Datoteka je izbrisana.\n");
        else
            perror("Greška pri brisanju datoteke");
    } else {
        printf("Datoteka nije izbrisana.\n");
    }
}
