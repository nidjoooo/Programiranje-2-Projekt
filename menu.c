#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include "header.h"

int menu(void) {
  unsigned int condition = 0;
  
  printf("\n================ IronFlow - Trening Evidencija ================\n");
  printf("\tOpcija 1: Dodaj novi trening\n");
  printf("\tOpcija 2: Pretraga treninga po korisniku\n");
  printf("\tOpcija 3: Obrisi trening po vježbi\n");
  printf("\tOpcija 4: Obrisi cijelu datoteku\n");
  printf("\tOpcija 5: Izlaz iz programa\n");
  printf("===============================================================\n");
  printf("Unesite broj opcije: ");

do {
  scanf("%d", &condition);
  getchar();
} while (condition < 1 || condition > 5);

switch (condition) {
  case ADD_WORKOUT:
  addWorkout();
  break;
  case SEARCH_WORKOUT:
  searchByUser();
  break;
  case DELETE_WORKOUT:
  deleteWorkout();
  break;
  case DELETE_FILE:
  deleteFile();
  break;
  case EXIT_PROGRAM:
  condition = exitProgram();
  break;
  default:
  condition = 0;
}

return condition;
}
