#ifndef UNTITLED1_GAME_H
#define UNTITLED1_GAME_H

#include "hands.h"
#include "players.h"
#include "baraja.h"
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>


Playerlist Repartir(Baraja *b, Playerlist *p);
Playerlist CARTLIST_Create(Playerlist *p);
int CART_Insert(Cartlist *list, Carta *c);
void CARTLIST_Go_First(Cartlist *list);
int CARTLIST_Next(Cartlist *list);
Baraja EMPEZAR(Baraja *pdescarte, Baraja *b);
void VER_mano(Cartlist *c,Baraja *b, int *chupate);
void View_Cart(Carta c);
void Go_First(Cartlist *l);
void Robar_Carta(Baraja *b, Cartlist *c, Baraja *pdescartes);
int Comprueba_Carta(Baraja *b, Carta *c, int *chupate);
void Play_Card(Baraja *b, Cartlist *c, int ncarta, int chupate);
void Delete_Card(Cartlist *l);
void Hand_GoFirst(Cartlist *l);
void Info_Bots(Playerlist *l, int turno);
void Comprobar_Especial(Carta c, int *chupate, int *sentido, int *prohibido);
void Comprobar_Mano(Baraja *b,Cartlist *l, int *chupate);
void Comprobar_Sentido(Carta c, int *sentido);
int Comprobar_Cambio_Color(Baraja *b,int *color,Playerlist *p);
void Comprobar_nCartas_Baraja(Baraja *baraja, Baraja *pdescartes);
void Recargar_Baraja(Baraja *pdescartes, Baraja *baraja);
int Comprobar_Gameover(Playerlist *list, Player *p, int *npartidas, char stats[50]);
void endGame(Playerlist *p, Baraja *b, Baraja *descartes);
void borrarListaCartas(Cartlist *list);
void Play_Card_Robada(Baraja *b, Cartlist *l,Carta *c, int chupate);

        int Cart_Is_Empty(Cartlist list);
#endif
