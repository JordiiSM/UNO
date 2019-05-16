#include <stdio.h>
#include "CLIplayer.h"
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int CLI_menu() {
    int option;
    printf("-------------------------------------------------------\n");
    printf("1. Jugar\n2. Mostrar estadisticas\n3. Salir\n");
    printf("-------------------------------------------------------\n");
    fflush( stdin );
    printf("Enter an option:");
    scanf("%d",&option );
    printf("\n");
    return option;

}
int CLI_player(char *name) {
    char tmp;
    int option;
    char skip;
    printf("-------------------------------------------------------\n");
    printf("%s escoge una acción:\n",name);
    printf("A. Ver mano\nB. Robar carta\n");
    printf("-------------------------------------------------------\n");
    fflush( stdin );
    scanf("%c%c",&tmp, &skip);
    if(tmp == 'A'){
        option = 1;
    }
    if(tmp == 'B'){
        option = 2;
    }
    printf("\n");
    return option;

}
int CLI_robado(Baraja *b, Carta c) {
    char tmp;
    int option;
    char skip;
    printf("-------------------------------------------------------\n");
    printf("Se ha robado un ");
    View_Cart(c);
    printf("\n");
    Comprueba_Carta()
    printf("A. Ver mano\nB. Robar carta\n");
    printf("-------------------------------------------------------\n");
    fflush( stdin );
    scanf("%c%c",&tmp, &skip);
    if(tmp == 'A'){
        option = 1;
    }
    if(tmp == 'B'){
        option = 2;
    }
    printf("\n");
    return option;

}
int CLI_play(char *name) {
    char tmp;
    char skip;
    int option;
    printf("-------------------------------------------------------\n");
    printf("%s escoge una acción:\n",name);
    printf("A. Jugar carta\nB. Robar carta\n");
    printf("-------------------------------------------------------\n");
    fflush( stdin );
    scanf("%c%c",&tmp, &skip);
    if(tmp == 'A'){
        option = 1;
    }
    if(tmp == 'B'){
        option = 2;
    }
    printf("\n");
    return option;

}
int CLI_playcard() {
    int option;
    printf("-------------------------------------------------------\n");
    printf("Que carta deseas jugar?\n");
    printf("-------------------------------------------------------\n");
    fflush( stdin );
    printf("Enter an option:");
    scanf("%d",&option );
    printf("\n");
    return option;

}
