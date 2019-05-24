#ifndef UNTITLED1_PLAYERS_H
#define UNTITLED1_PLAYERS_H

#include "hands.h"


typedef struct _player{

    char name[MAX];
    char type[MAX];
    int ganadas;
    Cartlist cart;


}Player;

typedef struct _node {

    struct _player *p;
    struct _node *next;
    struct _node *previous;


}Node;

typedef struct{

    Node *first;
    Node *pdi;
    Node *last;
    int nplayers;

}Playerlist;

#endif //UNTITLED1_PLAYERS_H
