#include <stdio.h>
#include "header.h"

int menu(void) {
    int option;

    printf("\n===== IronFlow - Evidencija Treninga =====\n");
    printf("1. Dodaj novi trening\n");
    printf("2. Obrisi trening po nazivu vjezbe\n");
    printf("3. Obrisi cijelu datoteku\n");
    printf("4. Izlaz iz programa\n");
    printf("==========================================\n");
    printf("Odaberite opciju (1-4): ");
    scanf("%d", &option);
    getchar();

    switch ((enum MainMenu)option) {
        case ADD_WORKOUT:
            addWorkout();
            break;
        case DELETE_WORKOUT:
            deleteWorkout();
            break;
        case DELETE_FILE:
            deleteFile();
            break;
        case EXIT_PROGRAM:
            return exitProgram();
        default:
            printf("Nepostojeca opcija. Pokusajte ponovo.\n");
    }

    return 1; 
}