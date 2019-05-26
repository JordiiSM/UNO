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

int main(int argc, char **argv) {
    int quieresjugarla = 0;
    int optionmenu = 5;
    int optionmenu2 = 5;
    int npartidas = 1;
    int color = 0;
    int cardoption;
    int comprueba_bot;
    int turno = 1;
    int chupate = 0;
    int end = 0;
    int gameover = 0;
    int i = 0;
    int compilar = 1;
    char option;
    int sentido = 0;
    int prohibido = 0;
    int comprobar_player = 0;
    int ncarta;
    int size;
    int aux;
    Playerlist *list;
    list = malloc(sizeof(Playerlist));
    Baraja *baraja;
    Baraja *pdescartes;
    *list = PLIST_Create();
    *list = ADD_Players(argv[1]);

    do {


        do {
            optionmenu2 = CLI_menu();
            if (optionmenu2 == 1) {

                baraja = malloc(sizeof(Baraja));
                pdescartes = malloc(sizeof(Baraja));
                *baraja = PILA_crea();
                *baraja = PILA_rellenar(baraja);
                *pdescartes = PILA_crea();

                size = baraja->cuantos;

                PLIST_Go_First(list);
                BARAJA_mix(baraja);
                *list = Repartir(baraja, list);
                *pdescartes = EMPEZAR(pdescartes, baraja);
                gameover = 0;
            }
            if (optionmenu2 == 2) {
                while (optionmenu != 3) {
                    optionmenu = CLI_menu_stats();
                    if (optionmenu == 1) {
                        lectura_fichero(list, argv[2]);
                        option = 0;
                    }
                    if (optionmenu == 2) {
                        estadisticas_bots(list, npartidas);
                        option = 0;
                    }

                }
                optionmenu = 0;
            }
        } while (optionmenu2 != 1 && optionmenu != 3);

        while (gameover != 1 && optionmenu2 == 1) {

            Comprobar_nCartas_Baraja(baraja, pdescartes);

            printf("\n\n\n----------------------------------------------\n");
            printf("## ");
            View_Cart(pdescartes->c->carta);
            printf("##\n");
            Comprobar_Especial(pdescartes->c->carta, &chupate, &sentido, &prohibido);

            if (prohibido == 1) {
                printf("CHUPATE --> %d SENTIDO --> %d PROHIBIDO --> %d\n", chupate, sentido, prohibido);
                Info_Bots(list, turno);
                printf("%s Se te ha saltado el turno\n", list->pdi->p->name);
                prohibido = 0;
                PLIST_Next(list);
                if (turno < list->nplayers) {
                    turno++;
                } else {
                    turno = 1;
                }
            }


            Info_Bots(list, turno);

            if (strcmp(list->pdi->p->type, "jugador") == 0) {
                do {
                    if (chupate > 0) {
                        while (chupate > 0) {
                            printf("Jugador %s roba carta\n", list->pdi->p->name);
                            Robar_Carta(baraja, &list->pdi->p->cart, pdescartes);
                            chupate--;
                        }
                        CARTLIST_Go_First(&list->pdi->p->cart);
                    }
                    option = CLI_player(list->pdi->p->name);

                    if (option == 'A') {
                        VER_mano(&list->pdi->p->cart, pdescartes, &chupate);
                        option = CLI_play(list->pdi->p->name);
                        if (option == 'A') {
                            cardoption = CLI_playcard();
                            Play_Card(pdescartes, &list->pdi->p->cart, cardoption, chupate);
                            gameover = Comprobar_Gameover(list, list->pdi->p, &npartidas, argv[2]);
                            color = 0;
                            color = Comprobar_Cambio_Color(pdescartes, &color, list);
                            if (color == 1) {
                                CLI_escoje_color(pdescartes, list);
                            }
                            comprobar_player = OK;
                            CARTLIST_Go_First(&list->pdi->p->cart);
                            option = 0;
                        }
                    }
                    if (option == 'B') {
                        Robar_Carta(baraja, &list->pdi->p->cart, pdescartes);
                        printf("Has robado: ");
                        View_Cart(list->pdi->p->cart.pdicard->c);
                        aux = Comprueba_Carta(baraja, &list->pdi->p->cart.pdicard->c, &chupate);
                        if (aux == OK) {
                            printf("Quieres jugarla? \n1 - si\n 2 - no \n");
                            scanf("%d", &quieresjugarla);
                            if (quieresjugarla == 1) {
                                Play_Card_Robada(pdescartes, &list->pdi->p->cart, &list->pdi->p->cart.pdicard->c,
                                                 chupate);
                                gameover = Comprobar_Gameover(list, list->pdi->p, &npartidas, argv[2]);
                                comprobar_player = OK;
                                CARTLIST_Go_First(&list->pdi->p->cart);
                            } else {
                                CARTLIST_Go_First(&list->pdi->p->cart);
                            }
                            quieresjugarla = 0;
                            color = 0;
                            color = Comprobar_Cambio_Color(pdescartes, &color, list);
                            if (color == 1) {
                                CLI_escoje_color(pdescartes, list);
                            }
                            comprobar_player = OK;
                            CARTLIST_Go_First(&list->pdi->p->cart);
                            option = 0;

                        }

                    }
                } while (comprobar_player != OK);
                comprobar_player = ERROR;

            } else {
                do {
                    comprueba_bot = Comprueba_Carta_Bot(list, &list->pdi->p->cart, pdescartes, baraja, &chupate,
                                                        &ncarta);
                    if (comprueba_bot == OK) {
                        Play_Card(pdescartes, &list->pdi->p->cart, ncarta, chupate);
                        gameover = Comprobar_Gameover(list, list->pdi->p, &npartidas, argv[2]);
                        color = Comprobar_Cambio_Color(pdescartes, &color, list);
                        color = 0;
                        printf("\n");
                        CARTLIST_Go_First(&list->pdi->p->cart);
                        printf("\n############################################################\n");
                    }
                    if (comprueba_bot == ERROR) {
                        if (chupate > 0) {
                            while (chupate > 0) {
                                printf("Jugador %s roba carta\n", list->pdi->p->name);
                                Robar_Carta(baraja, &list->pdi->p->cart, pdescartes);
                                chupate--;
                            }
                            CARTLIST_Go_First(&list->pdi->p->cart);
                        } else {
                            Robar_Carta(baraja, &list->pdi->p->cart, pdescartes);
                            printf("El jugador %s Ha robado \n", list->pdi->p->name);
                            CARTLIST_Go_First(&list->pdi->p->cart);
                        }
                    }

                } while (comprueba_bot != OK);

            }

            Comprobar_Sentido(pdescartes->c->carta, &sentido);
            if (sentido == 0) {
                PLIST_Next(list);
                if (turno < list->nplayers) {
                    turno++;
                } else {
                    turno = 1;
                }
            }
            if (sentido == 1) {
                PLIST_previous(list);
                if (turno != 1) {
                    turno--;
                } else {
                    turno = list->nplayers;
                }
            }
        }
        PILA_destruye(baraja);
        free(baraja);
        PILA_destruye(pdescartes);
        free(pdescartes);
        PLIST_Go_First(list);
        for (int k = 0; k < list->nplayers; k++) {
            printf("%s \n", list->pdi->p->name);
            borrarListaCartas(&list->pdi->p->cart);
            PLIST_Next(list);
        }
        PLIST_Go_First(list);
    } while (optionmenu2 != 3);
    PLIST_Destroy(list);
    return 0;
}








