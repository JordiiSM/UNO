#ifndef UNTITLED1_CONFPLAYERS_H
#define UNTITLED1_CONFPLAYERS_H

#include "players.h"
#include "hands.h"
#include "game.h"

Playerlist PLIST_Create();
int PLIST_Insert(Playerlist *list, Player player);
int PLIST_Remove(Playerlist *list);
Player PLIST_Get(Playerlist list);
void PLIST_Go_First(Playerlist *list);
int PLIST_Next(Playerlist *list);//
int PLIST_previous(Playerlist *list);//
void PLIST_Destroy(Playerlist *list);
int Comprueba_Carta_Bot(Cartlist *list, Baraja *b,Baraja *baraja, int *chupate, int *ncarta);
int Comprobar_Ceros(Baraja *b ,Cartlist *list, int *ncarta, int *chupate);
int Comprobar_Color(Baraja *b, Cartlist *list, Carta c, int *ncarta, int *chupate);
#endif
