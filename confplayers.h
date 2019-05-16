#ifndef UNTITLED1_CONFPLAYERS_H
#define UNTITLED1_CONFPLAYERS_H

#include "players.h"
#include "hands.h"

Playerlist PLIST_Create();
int PLIST_Insert(Playerlist *list, Player player);
int PLIST_Remove(Playerlist *list);
Player PLIST_Get(Playerlist list);
void PLIST_Go_First(Playerlist *list);
int PLIST_Next(Playerlist *list);//
int PLIST_previous(Playerlist *list);//
void PLIST_Destroy(Playerlist *list);

#endif
