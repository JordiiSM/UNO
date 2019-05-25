#ifndef UNTITLED1_CONF_H
#define UNTITLED1_CONF_H

#include "players.h"
#include "confplayers.h"
#define MAXC 50

Playerlist ADD_Players(char f[50]);
void Stats(char f[50], Playerlist *p);
void estadisticas_bots(Playerlist *pls, int npartidas);
int lectura_fichero(Playerlist *p, char statsfile[50]);
int lectura_fichero_escritura(Playerlist *list, Player *p, char statsfile[50]);


#endif //UNTITLED1_CONF_H
