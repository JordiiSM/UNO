#include "baraja.h"
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
Baraja PILA_crea() {

    Baraja p;
    p.cuantos = 0;
    //p.c = NULL;
    return p;
}
Baraja PILA_rellenar(Baraja *p) {
    Carta c;
    int i = 0, j = 0;

    //creamos las cartas numero
    for (i;i<10;i++){
        c.especial = 0;
        if(i!=0) {  //Si el numero es un 0 solo tienen que haber 4

            c.num = i;
            strcpy(c.color, "rojo");
            PILA_push(p, c);
            strcpy(c.color, "amarillo");
            PILA_push(p, c);
            strcpy(c.color, "verde");
            PILA_push(p, c);
            strcpy(c.color, "azul");
            PILA_push(p, c);
        }
        c.num = i;
        strcpy(c.color, "rojo");

        PILA_push(p, c);
        strcpy(c.color, "amarillo");
        PILA_push(p, c);
        strcpy(c.color, "verde");
        PILA_push(p, c);
        strcpy(c.color, "azul");
        PILA_push(p, c);
    }
    //creamos cartas especiales sin color
    c.num = -1;
    for(i = 1; i<4;i++){


        c.especial = i;
        strcpy(c.color, "rojo");
        PILA_push(p, c);
        PILA_push(p, c);
        strcpy(c.color, "amarillo");
        PILA_push(p, c);
        PILA_push(p, c);
        strcpy(c.color, "verde");
        PILA_push(p, c);
        PILA_push(p, c);
        strcpy(c.color, "azul");
        PILA_push(p, c);
        PILA_push(p, c);
    }
    //añadimos cartas especiales
    strcpy(c.color, "NULL");
    c.especial = 4;
    for(i = 0;i<4;i++) {
        PILA_push(p, c);
    }
    c.especial = 5;
    for(i = 0;i<4;i++) {
        PILA_push(p, c);
    }

    return *p;
}

void BARAJA_mix(Baraja *p) {

    int i = 0,j=0,k=0;
    int random = 0;
    Carta tmp;
    int size = p->cuantos;
    Carta *baraja_mix;
    baraja_mix = malloc(p->cuantos * sizeof(Carta));



    for(i = 0 ;i < size; i++){//asignacion de datos a la pila

        baraja_mix[i] = p->c->carta;
        PILA_pop(p);
    }



    for(j=0;j<size;j++) {//swap de posicion secuencial a random

        random = rand() % size;
        random--; // restamos 1 al random para que este entre los valores 0 - 4
        tmp = baraja_mix[j];
        baraja_mix[j] = baraja_mix[random];
        baraja_mix[random] = tmp;
        PILA_push(p, baraja_mix[j]);

    } /*
    for(k=0;k <= j;k++){ //sube las prendas desordenadas a la pila
        PILA_push(p, baraja_mix[k]);
        printf("Clote FINAL  [%d] ----> %s\n", k, clotes->last->clote);
    }*/
}

void PILA_push(Baraja *p, Carta c) {

    NodeCart *aux = malloc(sizeof(NodeCart));
    aux->carta = c;
    aux->next = p->c;
    p->c = aux;

    (p->cuantos)++;
    /*if(p->c == NULL)
        printf("No se ha podido agregar elemento");*/
}


void PILA_pop(Baraja *p) {
    NodeCart *tmp;
    tmp = p->c;
    p->c = p->c->next;
    (p->cuantos)--;
    free(tmp);
}
/*
int PILA_top(Baraja p) {
    int elemento = -1;
    if (p.cuantos>0) {
        elemento = p.elementos[p.cuantos-1];
    } else {
        printf("\nError al hacer top, la pila estÃ¡ vacÃ­a.");
    }
    return elemento;
}

int PILA_vacia(Baraja p) {
//	int vacia = 0;
//	if ((*p).cuantos == 0) {
//		vacia = 1;
//	}
//	return vacia;
    return p.cuantos==0;
}

void PILA_destruye(Baraja *p) {
    (*p).cuantos = 0;
}
*/
