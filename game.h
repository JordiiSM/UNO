#ifndef UNTITLED1_GAME_H
#define UNTITLED1_GAME_H

#include "hands.h"
#include "players.h"
#include "baraja.h"
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


Playerlist Repartir(Baraja *b, Playerlist *p);
Playerlist CARTLIST_Create(Playerlist *p);
int CART_Insert(Cartlist *list, Carta *c);
void CARTLIST_Go_First(Cartlist *list);
int CARTLIST_Next(Cartlist *list);
Baraja EMPEZAR(Baraja *pdescarte, Baraja *b);
void VER_mano(Cartlist *c,Baraja *b, int *chupate);
void View_Cart(Carta c);
void Go_First(Cartlist *l);
void Robar_Carta(Baraja *b, Cartlist *c);
int Comprueba_Carta(Baraja *b, Carta *c, int *chupate);
void Play_Card(Baraja *b, Cartlist *c, int ncarta, int chupate);
void Delete_Card(Cartlist *l);
void Hand_GoFirst(Cartlist *l);
void Info_Bots(Playerlist *l, int turno);
void Comprobar_Especial(Carta c, int *chupate, int *sentido, int *prohibido);
void Comprobar_Mano(Baraja *b,Cartlist *l, int *chupate);
void Comprobar_Sentido(Carta c, int *sentido);
#endif
