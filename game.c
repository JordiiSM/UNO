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
        for (j = 0; j < p->pdi->p->cart.cartasinicio; j++) { //hasta que tenga todas las cartas asignadas
             //cambiar por funcion
            CART_Insert(&p->pdi->p->cart, &b->c->carta);
            PILA_pop(b);
            //View_Cart(p->pdi->p->cart.pdicard->p->c);

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
        if(strcmp(list->pdicard->c.color,"rojo")==0){
            list->rojas++;
        }else if(strcmp(list->pdicard->c.color,"amarillo")==0){
            list->amarillas++;
        }else if(strcmp(list->pdicard->c.color,"verde")==0){
            list->verdes++;
        }else if(strcmp(list->pdicard->c.color,"azul")==0){
            list->azules++;
        }

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
    Go_First(c);
    for(i = 0 ; i < c->ncartas ; i++){

        printf("%d. ",i+1);
        View_Cart(c->pdicard->c);
        option = Comprueba_Carta(b, &c->pdicard->c, chupate);

        if(option == OK){
            printf(" *\n");
        }else{
            printf(" \n");
        }

        CARTLIST_Next(c);
    }
    CARTLIST_Go_First(c);
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

void Play_Card(Baraja *b, Cartlist *c, int ncarta,int chupate) {
    int i;
    int comp = 3;

    while (comp != OK){
        for (i = 1; i < ncarta; i++) {
            CARTLIST_Next(c);
        }
    comp = Comprueba_Carta(b, &c->pdicard->c, &chupate);
    if (comp == ERROR) {
        printf("Esta carta no se puede jugar, escoge otra: ");
        scanf("%d",&ncarta);
        printf("\n");
        Hand_GoFirst(c);
    }

}
            PILA_push(b, c->pdicard->c);
    //printf("Has tirado la carta ");
    View_Cart(b->c->carta);
    printf("\n");
    Delete_Card(c);
    Hand_GoFirst(c);

}

void Delete_Card(Cartlist *l){
    NodeHand *aux;
    if (l->pdicard == l->firstcard || l->pdicard == l->lastcard) {
        printf("\nError al eliminar, PDI situado al principio o final...");
    } else {
        aux = l->pdicard;
        aux->next->previous = aux->previous;
        aux->previous->next = aux->next;
        l->pdicard = aux->next;
        free(aux);
        l->ncartas--;
        if(strcmp(l->pdicard->c.color,"rojo")==0){
            l->rojas--;
        }else if(strcmp(l->pdicard->c.color,"amarillo")==0){
            l->amarillas--;
        }else if(strcmp(l->pdicard->c.color,"verde")==0){
            l->verdes--;
        }else if(strcmp(l->pdicard->c.color,"azul")==0){
            l->azules--;
        }
    }
}
void Hand_GoFirst(Cartlist *l){
    l->pdicard = l->firstcard->next;
}
void Info_Bots(Playerlist *l, int turno){
    int i;
    printf("ESTAMOS EN EL TURNO %d LE TOCA A %s\n\n",turno,l->pdi->p->name);
    PLIST_Go_First(l);
    for(i = 1 ; i <= l->nplayers ; i++){

        if(i == turno) {
           printf("%s - %d cartas         v\n", l->pdi->p->name,l->pdi->p->cart.ncartas);
        }
        else{
            printf("%s - %d cartas\n", l->pdi->p->name,l->pdi->p->cart.ncartas);

        }
        PLIST_Next(l);
    }
    PLIST_Go_First(l);
    //if( != ) {
        for (i = 2; i <= turno; i++) {
            PLIST_Next(l);
      //  }
    }
}

//////////////////////////////////////////////////////////////////////
void Comprobar_Especial(Carta c, int *chupate, int *sentido){
    switch (c.especial){
        case 2:
            if(*sentido == 1){
            *sentido=0;
            }
            if(*sentido == 0){
                *sentido = 1;
            }

        case 3:
            *chupate = *chupate+2;
            break;
        case 5:
            *chupate = *chupate+4;
            break;
    }
}
void Comprobar_Mano(Baraja *b,Cartlist *l, int *chupate){

    int i;
    int cont = 0;
    int aux;
    for(i=0 ; i<l->ncartas; i++){
        aux = Comprueba_Carta(b,&l->pdicard->c, chupate);
        if(aux == OK){
            cont++;
        }
    }
    if(cont > 0){
        //Robar_Carta();
    }

}