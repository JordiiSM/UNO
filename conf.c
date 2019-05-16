#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "conf.h"

//falta pasar fichero por argumento
Playerlist ADD_Players(char f[50]) {
    char ncartas[50], nplayers[50];
    int i, numplayers;
    int val, val1;
    Playerlist *list = malloc(sizeof(Playerlist));
    *list = PLIST_Create();
    Cartlist c;
    FILE *file;
    Player tmp;
    char skip[MAXC];
    file = fopen(f, "r");
    if (file == NULL) {
        printf("No s'ha pogut obrir el fitxer \n");
    } else {
        fgets(nplayers, 100, file);
        numplayers = atoi(nplayers);
        printf("N players: %d \n", numplayers);
        list->nplayers = numplayers+1;
        for (i = 0; i < numplayers; i++) {

            fgets(tmp.name, 100, file);
            //printf("Nombre: %s \n", tmp.name);
            fgets(tmp.type, 100, file);
            //printf("Tipo: %s \n", tmp.type);
            fgets(ncartas, 100, file);
            c.cartasinicio = atoi(ncartas);
            tmp.cart = c;
            //printf("N cartas: %d \n", tmp.h->ncartas);
            PLIST_Insert(list, tmp);
           // list->pdi->p->cart.ncartas = list->pdi->p->cart.cartasinicio;
            //printf("Nombre insertado: %s \n", list->pdi->p->name);
            //printf("Prueba\n");

        }
        strcpy(tmp.name, "jordi");
        strcpy(tmp.type,"jugador");
        c.cartasinicio = 7;
        //list->pdi->p->cart.ncartas = list->pdi->p->cart.cartasinicio;
        tmp.cart = c;
        printf("Prueba\n");
        PLIST_Insert(list,tmp);
        fclose(file);
    }
    PLIST_Go_First(list);
    return *list;
}
