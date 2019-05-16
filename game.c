#include "game.h"
#include "baraja.h"
#include "confplayers.h"
#define OK 1
#define ERROR 0
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
Playerlist Repartir(Baraja *b, Playerlist *p){
    Carta tempcart;
   //p->pdi->p->cart = *list;
    int i,j;
    printf("Numero players: %d \n",p->nplayers);

    PLIST_Go_First(p);
    for(i = 0; i < p->nplayers; i++) { //recorre todos los jugadores
        //Cartlist *list = malloc(sizeof(Cartlist));
        //list->cartasinicio =  p->pdi->p->cart.cartasinicio;
        *p = CARTLIST_Create(p);
       // list->cartasinicio = p->pdi->p->cart.cartasinicio;

        printf("Numero Cartas inicio: %d Jugador: %d\n",p->pdi->p->cart.cartasinicio,i);
        printf("Numero Cartas inicio: %d Jugador: %s\n",p->pdi->p->cart.cartasinicio,p->pdi->p->name);
        for (j = 0; j < p->pdi->p->cart.cartasinicio; j++) { //hasta que tenga todas las cartas asignadas
             //cambiar por funcion
            CART_Insert(&p->pdi->p->cart, &b->c->carta);
            View_Cart(p->pdi->p->cart.pdicard->c);
            printf("Prueba\n");
            PILA_pop(b);
            //View_Cart(p->pdi->p->cart.pdicard->p->c);
            printf("Insertada \n");

            //printf("%d %s %d \n", list->pdicard->p->c->num, list->pdicard->p->c->color, list->pdicard->p->c->especial);

        }
       // p->pdi->p->cart = *list;
        PLIST_Next(p);

    }
    PLIST_Go_First(p);
    return *p;
}
//--------------CREAR-------------------
Playerlist CARTLIST_Create(Playerlist *p){
    Cartlist *list = malloc(sizeof(Cartlist));
    NodeHand *Ghost1;
    NodeHand *Ghost2;
    Ghost1 = (NodeHand *) malloc(sizeof(NodeHand)); //creamos fantasma inicial
    Ghost2 = (NodeHand *) malloc(sizeof(NodeHand)); //creamos fantasma final
    //control de errores
    if(Ghost1 == NULL || Ghost2 == NULL ){
        //error
    }else{
        Ghost1->next = Ghost2;  //asigna el fantasma final al next del inicial
        Ghost1->previous = NULL;    //pone a null el anterior al inicial
        Ghost2->next = NULL;    //pone a null el siguiente al final
        Ghost2->previous = Ghost1;  //guarda la posicion del fantasma inicial en la posicion anterior del final
        list->firstcard = Ghost1;    //pone como primera posiciÃ³n de la lista el fantasma inicial
        list->lastcard = Ghost2;     //pone como ultima posiciÃ³n de la lista el fantasma final
        list->pdicard = Ghost1;      //guarda como punto de interes el fantasma inicial
        list->ncartas = 0;
        //list.cartasinicio = 0;
        list->cartasinicio = p->pdi->p->cart.cartasinicio;
        p->pdi->p->cart = *list;


    }
    return *p;
}
//------------INSERTAR----------------------
int CART_Insert(Cartlist *list, Carta *c){
    NodeHand *aux = (NodeHand *) malloc(sizeof(NodeHand));
    //control de errores

    if(list->pdicard == list->lastcard){
        return ERROR;
    }else{
        aux->c = *c;
        aux->next = list->pdicard->next;
        aux->previous = list->pdicard;
        aux->next->previous = aux;
        list->pdicard->next = aux;
        list->pdicard = aux;
        list->ncartas++;
    }

    return OK;
}

//--------------IR AL PRINCIPIO DE LA LISTA ----------------------
void CARTLIST_Go_First(Cartlist *list){
    list->pdicard = list->firstcard;
    CARTLIST_Next(list);
}
//-----------------PASAR AL SIGUIENTE ELEMENTO DE LA LISTA---------------
int CARTLIST_Next(Cartlist *list){
    if(list->pdicard->next == list->lastcard){  //estem al final
        return ERROR;
    }else{
        list->pdicard = list->pdicard->next;
        return OK;
    }
}
//-----------------EMPIEZA PARTIDA---------------
Baraja EMPEZAR(Baraja *pdescarte, Baraja *b){

    do{ //Comprueba que la primera carta no sea especial

    PILA_push(pdescarte, b->c->carta);
    PILA_pop(b);

    }while(pdescarte->c->carta.especial != 0);
    return *pdescarte;

}
void Robar_Carta(Baraja *b, Cartlist *c){

    CART_Insert(c, &b->c->carta);
    PILA_pop(b);

}

void Go_First(Cartlist *l){
    l->pdicard = l->firstcard->next;
}
void View_Cart(Carta c){
        switch(c.especial) {
            case 0:
                printf("%d %s ", c.num, c.color);
                break;
            case 1:
                printf("Prohibido tirar %s ",c.color);
                break;
            case 2:
                printf("Cambio de sentido %s ",c.color);
                break;
            case 3:
                printf("Roba 2 %s ",c.color);
                break;
            case 4:
                printf("Cambio de color ");
                break;
            case 5:
                printf("Chupate 4 ");
                break;
        }

}
void VER_mano(Cartlist *c,Baraja *b,int *chupate){
    int i;
    int option;
    printf("%d <--- Num cartas \n", c->ncartas);
    Go_First(c);
    for(i = 0 ; i < c->ncartas ; i++){
        View_Cart(c->pdicard->c);
        option = Comprueba_Carta(b, &c->pdicard->c, chupate);
        if(option == OK){
            printf(" *\n");
        }else{
            printf(" \n");
        }
        CARTLIST_Next(c);
    }
}
int Comprueba_Carta(Baraja *b, Carta *c, int *chupate){

    switch (b->c->carta.especial){
        case 0:
            if(*chupate == 0) {
                if ((strcmp(b->c->carta.color, c->color) == 0) || (b->c->carta.num == c->num) || (c->especial == 4) ||
                    (c->especial == 5)) {
                    return OK;
                } else {
                    return ERROR;
                }
            }else{
                return ERROR;
            }
        case 1:
            if(*chupate == 0) {
                if ((strcmp(b->c->carta.color, c->color) == 0) || (c->especial == 4) || (c->especial == 5)) {
                    return OK;
                } else {
                    return ERROR;
                }
            }else{
                return  ERROR;
            }

        case 2:
            if(*chupate == 0) {
                if ((strcmp(b->c->carta.color, c->color) == 0) || (c->especial == 4) || (c->especial == 5)) {
                    return OK;
                } else {
                    return ERROR;
                }
            }else{
                return ERROR;
            }
        case 3:
            if(*chupate == 0){
                if((strcmp(b->c->carta.color, c->color) == 0) || (c->especial == 4) || (c->especial == 5)){
                    return OK;
                }else{
                    return ERROR;
                }
            }else{
                if(b->c->carta.especial == c->especial){
                    return OK;
                }else{
                    return ERROR;
                }

            }

        case 4:
            if(*chupate == 0){
                return OK;
            }else{
                return ERROR;
            }

        case 5:
            if(*chupate == 0){
                return OK;
            }else{
                if(b->c->carta.especial == c->especial){
                    return OK;
                }else{
                    return ERROR;
                }
            }
    }

}
