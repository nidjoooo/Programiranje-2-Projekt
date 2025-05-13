#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "header.h"

void addWorkout() {
    FILE* fp = NULL;
    int n;
    WORKOUT* workoutField = (WORKOUT*)malloc(sizeof(WORKOUT));
    if (workoutField == NULL) {
        perror("workoutField == NULL");
        exit(EXIT_FAILURE);
    }

    printf("Unesite datum (DD/MM/YYYY): ");
    scanf(" %10[^\n]", workoutField->date);

    printf("Unesite ciljnu misicnu skupinu (Push, Pull, Legs): ");
    scanf(" %50[^\n]", workoutField->muscleGroup);

    printf("Unesite naziv vjezbe: ");
    scanf(" %50[^\n]", workoutField->exerciseName);

    printf("Unesite broj serija: ");
    scanf("%d", &workoutField->sets);

    printf("Unesite broj ponavljanja: ");
    scanf("%d", &workoutField->reps);

    printf("Unesite koristenju tezinu (kg): ");
    scanf("%f", &workoutField->weight);

    printf("Unesite trajanje treninga (minute): ");
    scanf("%f", &workoutField->duration);

    printf("Unesite osobni napredak (1-100): ");
    scanf("%f", &workoutField->progress);

    fp = fopen("workoutfile.bin", "rb");
    if (fp == NULL) {
        fp = fopen("workoutfile.bin", "wb");
        n = 1;
        fwrite(&n, sizeof(int), 1, fp);
        fwrite(workoutField, sizeof(WORKOUT), 1, fp);
        fclose(fp);
    } else {
        fread(&n, sizeof(int), 1, fp);
        fclose(fp);

        fp = fopen("workoutfile.bin", "rb+");
        n++;
        fseek(fp, 0, SEEK_SET);
        fwrite(&n, sizeof(int), 1, fp);
        fseek(fp, 0, SEEK_END);
        fwrite(workoutField, sizeof(WORKOUT), 1, fp);
        fclose(fp);
    }

    free(workoutField);
    return;
}

void deleteWorkout() {
    WORKOUT* delField = NULL;
    int n, index, flag = 0;
    char searchName[51];
    FILE* fp = fopen("workoutfile.bin", "rb");

    if (fp == NULL) {
        printf("Datoteka je prazna.\n");
        return;
    }

    fread(&n, sizeof(int), 1, fp);
    delField = (WORKOUT*)malloc(n * sizeof(WORKOUT));
    if (delField == NULL) {
        perror("delField == NULL");
        exit(EXIT_FAILURE);
    }

    fread(delField, sizeof(WORKOUT), n, fp);
    fclose(fp);

    printf("Unesite naziv vjezbe koju zelite obrisati: ");
    scanf(" %50[^\n]", searchName);

    for (int i = 0; i < n; i++) {
        if (strcmp((delField + i)->exerciseName, searchName) == 0) {
            index = i;
            flag = 1;
            break;
        }
    }

    if (flag == 0) {
        printf("Vjezba nije pronadjena.\n");
    } else {
        fp = fopen("workoutfile.bin", "wb");
        if (fp == NULL) {
            perror("Greska prilikom otvaranja datoteke");
            free(delField);
            exit(EXIT_FAILURE);
        }

        n--;
        fwrite(&n, sizeof(int), 1, fp);

        for (int i = 0; i < n + 1; i++) {
            if (i == index) continue;
            fwrite((delField + i), sizeof(WORKOUT), 1, fp);
        }

        printf("Vjezba je obrisana.\n");
        fclose(fp);
    }

    free(delField);
    return;
}

void deleteFile() {
    char confirm[2] = { '\0' };
    char filename[] = "workoutfile.bin";

    printf("Zelite li obrisati cijelu datoteku? (Y/n): ");
    scanf(" %c", confirm);

    if (!strcmp("Y", confirm)) {
        if (remove(filename) == 0) {
            printf("Datoteka obrisana.\n");
        } else {
            perror("Greska pri brisanju datoteke");
        }
    } else {
        printf("Datoteka NIJE obrisana.\n");
    }
}

int exitProgram() {
    char confirm[2] = { '\0' };
    printf("Zelite li izaci? (Y/n): ");
    scanf(" %c", confirm);

    if (!strcmp("Y", confirm)) {
        return 0;
    }

    return 1;
}
