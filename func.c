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

    printf("Unesite datum: ");
    scanf(" %20[^\n]", workoutField->date);  
    getchar();  

    printf("Unesite ciljnu misicnu skupinu: ");
    fgets(workoutField->muscleGroup, sizeof(workoutField->muscleGroup), stdin);
    workoutField->muscleGroup[strcspn(workoutField->muscleGroup, "\n")] = '\0';

    printf("Unesite naziv vjezbe: ");
    fgets(workoutField->exerciseName, sizeof(workoutField->exerciseName), stdin);
    workoutField->exerciseName[strcspn(workoutField->exerciseName, "\n")] = '\0';
    

    printf("Unesite broj serija: ");
    scanf("%d", &workoutField->sets);
    getchar(); 

    printf("Unesite broj ponavljanja: ");
    scanf("%d", &workoutField->reps);
    getchar();  

    printf("Unesite koristenju tezinu (kg): ");
    scanf("%f", &workoutField->weight);
    getchar(); 

    printf("Unesite trajanje treninga (minute): ");
    scanf("%f", &workoutField->duration);
    getchar();  

    printf("Unesite osobni napredak (1-100): ");
    scanf("%f", &workoutField->progress);
    getchar(); 

    fp = fopen("workoutfile.bin", "rb");
    if (fp == NULL) {
        fp = fopen("workoutfile.bin", "wb");
        n = 1;
        fwrite(&n, sizeof(int), 1, fp);
        fwrite(workoutField, sizeof(WORKOUT), 1, fp);
        fclose(fp);
    }
    else {
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
    int n, index = -1, flag = 0;
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
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = '\0';

    for (int i = 0; i < n; i++) {
        if (strcmp((delField + i)->exerciseName, searchName) == 0) {
            index = i;
            flag = 1;
            break;
        }
    }

    if (flag == 0) {
        printf("Vjezba nije pronadjena.\n");
    }
    else {
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
    char confirm;
    char filename[] = "workoutfile.bin";

    printf("Zelite li obrisati cijelu datoteku? (Y/n): ");
    scanf(" %c", &confirm);

    if (confirm == 'Y') {
        if (remove(filename) == 0) {
            printf("Datoteka obrisana.\n");
        }
        else {
            perror("Greska pri brisanju datoteke");
        }
    }
    else {
        printf("Datoteka NIJE obrisana.\n");
    }
}

int exitProgram() {
    char confirm;
    printf("Zelite li izaci? (Y/n): ");
    scanf(" %c", &confirm);

    if (confirm == 'Y') {
        return 0;
    }

    return 1;
}
