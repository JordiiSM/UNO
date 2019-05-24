#include <stdio.h>
#include "CLIplayer.h"
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int get_num() {
    char str_num[5];

    fgets(str_num, 5, stdin);
    str_num[strlen(str_num) - 1] = '\0';

    return atoi(str_num);
}

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

    scanf("%c%c",&tmp,&skip);
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
void CLI_escoje_color(Baraja *b, Playerlist *p) {
   Carta c;
   c.especial = 0;
    int option;
    do {
        printf("-------------------------------------------------------\n");
        printf("¿Que color quieres cambiar?\n");
        printf("1. Rojo\n2. Amarillo\n3. Azul\n4. Verde\n");
        printf("-------------------------------------------------------\n");
        option = get_num();
        printf("\n");
        switch (option) {
            case 1:
                if (b->c->carta.especial == 4) {
                    c.num = 10;
                }
                if (b->c->carta.especial == 5) {
                    c.num = 11;
                }
                strcpy(c.color, "rojo");
                printf("%s cambia de color al %s", p->pdi->p->name, c.color);
                PILA_push(b, c);
                break;
            case 2:
                if (b->c->carta.especial == 4) {
                    c.num = 10;
                }
                if (b->c->carta.especial == 5) {
                    c.num = 11;
                }
                strcpy(c.color, "amarillo");
                printf("%s cambia de color al %s", p->pdi->p->name, c.color);
                PILA_push(b, c);
                break;
            case 3:
                if (b->c->carta.especial == 4) {
                    c.num = 10;
                }
                if (b->c->carta.especial == 5) {
                    c.num = 11;
                }
                strcpy(c.color, "azul");
                printf("%s cambia de color al %s", p->pdi->p->name, c.color);
                PILA_push(b, c);
                break;
            case 4:
                if (b->c->carta.especial == 4) {
                    c.num = 10;
                }
                if (b->c->carta.especial == 5) {
                    c.num = 11;
                }
                strcpy(c.color, "verde");
                printf("%s cambia de color al %s", p->pdi->p->name, c.color);
                PILA_push(b, c);
                break;
        }
    }while(option > 4 || option < 1);
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
    cardoption = get_num();
    printf("\n");
    return cardoption;

}
int CLI_menu_stats(){
int option;
printf("UNO  -   Estadisticas\n\n");
printf("Elige el tipo de estadistica a visualizar\n");
printf("\t1. Jugador\n\t2. Bots\n\t3. Regresar al menu principal\n");
printf("Enter an option: ");
scanf("%d",&option);
printf("n");
return option;
}
