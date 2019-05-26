#ifndef UNTITLED1_BARAJA_H
#define UNTITLED1_BARAJA_H

#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX 50

typedef struct {
    char color[MAX];
    int num;
    int especial;  // 0 = no || 1 = prohibido || 2 = cambio de sentido || 3 = roba 2 || = 4 cambio de color || 5 = chupate 4
}Carta;

typedef struct _nodeCart {
    Carta carta;
    struct _nodeCart *next;
}NodeCart;

typedef struct {
    NodeCart *c ;
    int cuantos;

}Baraja;


Baraja PILA_crea();
void BARAJA_mix(Baraja *p);
Baraja PILA_rellenar(Baraja *p);
void PILA_push(Baraja *p, Carta c);
void PILA_pop(Baraja *p);
int PILA_top(Baraja p);
int PILA_vacia(Baraja p);
void PILA_destruye(Baraja *b);


#endif //UNTITLED1_BARAJA_H
