#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "baraja.h"
#include "conf.h"
#include "game.h"
#include "CLIplayer.h"

int main() {
    int chupate = 0;
    int gameover = 0;
    int i = 0;
    int compilar = 1;
    int option=0;
    Baraja *baraja = malloc(sizeof(Baraja));
    printf("%d \n",compilar);
    compilar++;
    Baraja *pdescartes = malloc(sizeof(Baraja));
    printf("%d \n",compilar);
    compilar++;
    *pdescartes = PILA_crea();
    printf("%d \n",compilar);
    compilar++;
    *baraja = PILA_crea();
    printf("%d \n",compilar);
    compilar++;
    *baraja = PILA_rellenar(baraja);
    printf("%d \n",compilar);
    compilar++;

    int size = baraja->cuantos;
    char f[50]; //esto es temporal, se pasa por argumento
    strcpy(f, "fichero_bots.uno");
/*
    for(i;i<108;i++){
        switch(baraja->c->carta.especial) {
            case 0:
                printf("%d %s \n", baraja->c->carta.num, baraja->c->carta.color);
                break;
            case 1:
                printf("Prohibido tirar %s \n",baraja->c->carta.color);
                break;
            case 2:
                printf("Cambio de sentido %s \n",baraja->c->carta.color);
                break;
            case 3:
                printf("Roba 2 %s \n",baraja->c->carta.color);
                break;
            case 4:
                printf("Cambio de color \n");
                break;
            case 5:
                printf("Chupate 4 \n");
                break;
        }
        PILA_pop(baraja);
    }

    printf("----------------------------------------------\n");
*/
    Playerlist *list = malloc(sizeof(Playerlist));
    *list = PLIST_Create();
    *list = ADD_Players("fichero_bots.uno");
    for (i = 0; i < 2; i++) {
       printf("Name main: %s \n",list->pdi->p->name);
       printf("Type main: %s\n",list->pdi->p->type);
       printf("Ncartas main: %d\n",list->pdi->p->cart.cartasinicio);
            PLIST_Next(list);
    }
    PLIST_Go_First(list);
    printf("----------------------------------------------\n");
    BARAJA_mix(baraja);
/*
    for(i = 0 ;i < size;i++){
        switch(baraja->c->especial) {
            case 0:
                printf("%d %s \n", baraja->c->num, baraja->c->color);
                break;
            case 1:
                printf("Prohibido tirar %s \n",baraja->c->color);
                break;
            case 2:
                printf("Cambio de sentido %s \n",baraja->c->color);
                break;
            case 3:
                printf("Roba 2 %s \n",baraja->c->color);
                break;
            case 4:
                printf("Cambio de color \n");
                break;
            case 5:
                printf("Chupate 4 \n");
                break;
        }
        PILA_pop(baraja);
    }
*/
    *list = Repartir(baraja,list);
    printf("Numero de cartas: %d \n",list->pdi->p->cart.ncartas);
    *pdescartes = EMPEZAR(pdescartes, baraja);
    printf("Carta encima de la mesa: ");
    View_Cart(pdescartes->c->carta);
    while(gameover != 1) {
        if (strcmp(list->pdi->p->type,"jugador")==0){
            printf("Numero de cartas: %d \n",list->pdi->p->cart.ncartas);
            option = CLI_player(list->pdi->p->name);
            PLIST_Next(list);


            if(option == 1){
                VER_mano(&list->pdi->p->cart, pdescartes, &chupate);
                option = CLI_play(list->pdi->p->name);
                        if(option == 1){
                            option = CLI_playcard();
                        }

            }
            if(option == 2){
                Robar_Carta(baraja, &list->pdi->p->cart);

            }
        }
        else{
          PLIST_Next(list);
          printf("Jugador tipo %s \n",list->pdi->p->type);
        }

    }

    return 0;

}