#include <stdio.h>
#include "CLIplayer.h"
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
int CLI_menu() {
    int option;
    printf("-------------------------------------------------------\n");
    printf("1. Jugar\n2. Mostrar estadisticas\n3. Salir\n");
    printf("-------------------------------------------------------\n");
    printf("Enter an option:");
    scanf("%d",&option );
    printf("\n");
    return option;

}
char CLI_player(char *name) {
    char tmp;

    char skip;
    printf("-------------------------------------------------------\n");
    printf("%s escoge una acción:\n",name);
    printf("A. Ver mano\nB. Robar carta\n");
    printf("-------------------------------------------------------\n");

    scanf("%c",&tmp);
    fflushnou();
    printf("\n");
    printf("Has escogido la opcion: %c \n",tmp);
    return tmp;

}
int CLI_robado(Baraja *b, Carta c) {
    char tmp;

    char skip;
    int chupate;
    printf("-------------------------------------------------------\n");
    printf("Se ha robado un ");
    View_Cart(c);
    printf("\n");
    //Comprueba_Carta(b, *c, chupate);
    printf("A. Ver mano\nB. Robar carta\n");
    printf("-------------------------------------------------------\n");
    scanf("%c",&tmp);
    fflushnou();
    printf("\n");

    return tmp;

}
char CLI_play(char *name) {
    char tmp;
    char skip;
    printf("-------------------------------------------------------\n");
    printf("%s escoge una acción:\n",name);
    printf("A. Jugar carta\nB. Robar carta\n");
    printf("-------------------------------------------------------\n");
    scanf("%c",&tmp);
    fflushnou();
    printf("\n");
    return tmp;

}
int CLI_playcard() {
    int cardoption;
    printf("-------------------------------------------------------\n");
    printf("Que carta deseas jugar?\n");
    printf("-------------------------------------------------------\n");
    printf("Enter an option: ");
    scanf("%d",&cardoption );
    printf("\n");
    return cardoption;

}
