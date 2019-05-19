#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "baraja.h"
#include "conf.h"
#include "game.h"
#include "CLIplayer.h"
#define OK 1
#define ERROR 0

int main() {
    int cardoption;
    int comprueba_bot;
    int turno = 1;
    int chupate = 0;
    int gameover = 0;
    int i = 0;
    int compilar = 1;
    char option;
    int sentido = 0;
    int prohibido = 0;

    Baraja *baraja = malloc(sizeof(Baraja));
    Baraja *pdescartes = malloc(sizeof(Baraja));
    *pdescartes = PILA_crea();
    *baraja = PILA_crea();
    *baraja = PILA_rellenar(baraja);

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
    *pdescartes = EMPEZAR(pdescartes, baraja);

   /* for(int x= 0 ; x< list->nplayers; x++){
        printf("%s\n", list->pdi->p->name);
        CARTLIST_Go_First(&list->pdi->p->cart);
        for(int y = 0 ; y < list->pdi->p->cart.ncartas; y++){
            View_Cart(list->pdi->p->cart.pdicard->c);
            CARTLIST_Next(&list->pdi->p->cart);
        }
        PLIST_Next(list);
    }
    CARTLIST_Go_First(&list->pdi->p->cart);*/
    int tempi;
    while(gameover != 1) {
        printf("\n\n\n## ");
        View_Cart(pdescartes->c->carta);
        printf("##\n");
        if (prohibido  == 1){
            printf("CHUPATE --> %d SENTIDO --> %d PROHIBIDO --> %d\n",chupate,sentido,prohibido);
            Info_Bots(list, turno);
            printf("%s Se te ha saltado el turno\n",list->pdi->p->name);
            prohibido = 0;
            PLIST_Next(list);

            if(turno < list->nplayers ){
                turno++;
            }else{
                turno=1;
            }
        }
        //printf("CHUPATE --> %d SENTIDO --> %d PROHIBIDO --> %d\n",chupate,sentido,prohibido);
        Info_Bots(list, turno);

        Comprobar_Especial(pdescartes->c->carta,&chupate,&sentido,&prohibido);
        printf("CHUPATE --> %d SENTIDO --> %d PROHIBIDO --> %d\n",chupate,sentido,prohibido);







        if (strcmp(list->pdi->p->type, "jugador") == 0) {

            option = CLI_player(list->pdi->p->name);

            if (option == 'A') {
                VER_mano(&list->pdi->p->cart, pdescartes, &chupate);
                option = CLI_play(list->pdi->p->name);
                if (option == 'A') {
                    cardoption = CLI_playcard();
                    Play_Card(pdescartes, &list->pdi->p->cart, cardoption, chupate);
                    CARTLIST_Go_First(&list->pdi->p->cart);
                    option = 0;
                }
            }
            if(option == 'B'){
                Robar_Carta(baraja, &list->pdi->p->cart);
                CARTLIST_Go_First(&list->pdi->p->cart);
            }


        }else{
            do {
                comprueba_bot = Comprueba_Carta_Bot(&list->pdi->p->cart, pdescartes, baraja, &chupate, &cardoption);

                if (comprueba_bot == OK) {
                    printf("\n%s juega un ", list->pdi->p->name);

                    Play_Card(pdescartes, &list->pdi->p->cart, cardoption, chupate);
                   // View_Cart(pdescartes->c->carta);
                    printf("\n");
                    CARTLIST_Go_First(&list->pdi->p->cart);

                }
                if (comprueba_bot == ERROR) {
                    if(chupate>0) {
                        while (chupate > 0) {
                            Robar_Carta(pdescartes, &list->pdi->p->cart);
                            chupate--;
                        }
                        CARTLIST_Go_First(&list->pdi->p->cart);
                    }else {
                        Robar_Carta(baraja, &list->pdi->p->cart);
                        printf("El jugador %s Ha robado ", list->pdi->p->name);
                        View_Cart(list->pdi->p->cart.pdicard->c);
                        printf("\n");
                        CARTLIST_Go_First(&list->pdi->p->cart);
                    }
                }

            }while(comprueba_bot != OK);

        }

        PLIST_Next(list);

        if(turno < list->nplayers ){
            turno++;
        }else{
            turno=1;
        }
    }


}




