#ifndef UNTITLED1_CLIPLAYER_H
#define UNTITLED1_CLIPLAYER_H

#include "game.h"
#define CLI_PLAY	1
#define CLI_VIEW_STATS 2
#define CLI_EXIT 3

#define CLI_VER_MANO	1
#define CLI_ROBAR_CARTA 2
#define CLI_JUGAR_CARTA 3



int CLI_menu();
char CLI_player(char*);
int CLI_playcard();
char CLI_play(char *name);
int CLI_robado(Baraja *b, Carta c);
void CLI_escoje_color(Baraja *b, Playerlist *p);
int CLI_menu_stats();


#endif
