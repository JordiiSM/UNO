#ifndef UNTITLED1_HANDS_H
#define UNTITLED1_HANDS_H

#include "baraja.h"

typedef struct _nodeHand {

    Carta c;
    struct _nodeHand *next;
    struct _nodeHand *previous;

}NodeHand;

typedef struct{

    NodeHand *firstcard;
    NodeHand *pdicard;
    NodeHand *lastcard;
    int ncartas;
    int cartasinicio;

}Cartlist;
#endif
