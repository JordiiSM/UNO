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
void Robar_Carta(Baraja *b, Cartlist *c,Baraja *pdescartes){
    Comprobar_nCartas_Baraja(b,pdescartes);
    CART_Insert(c, &b->c->carta);
    PILA_pop(b);

}

void Go_First(Cartlist *l){
    l->pdicard = l->firstcard->next;
}
void View_Cart(Carta c){
        switch(c.especial) {
            case 0:
                if(c.num == 10){
                    printf("Cambio de color ");
                }else if(c.num == 11){
                    printf("Chupate 4 ");
                }else {
                    printf("%d %s ", c.num, c.color);
                }
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
int Comprueba_Carta(Baraja *b, Carta *c, int *chupate) {

    switch (b->c->carta.especial) {
        case 0:
            if (*chupate == 0) {
                if ((strcmp(b->c->carta.color, c->color) == 0) || (b->c->carta.num == c->num) || (c->especial == 4) ||
                    (c->especial == 5)) {
                    return OK;
                } else {
                    return ERROR;
                }
            } else {
                return ERROR;
            }
        case 1:
            if (*chupate == 0) {
                if ((strcmp(b->c->carta.color, c->color) == 0) || (c->especial == 4) || (c->especial == 5)) {
                    return OK;
                } else {
                    return ERROR;
                }
            } else {
                return ERROR;
            }

        case 2:
            if (*chupate == 0) {
                if ((strcmp(b->c->carta.color, c->color) == 0) || (c->especial==2) ||(c->especial == 4) || (c->especial == 5)) {
                    return OK;
                }
            } else if (b->c->carta.especial == 2 || c->especial == 2) {

                return OK;
            }
            return ERROR;


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
    CARTLIST_Go_First(c);
    while (comp != OK){
        for (i = 1; i < ncarta; i++) {
            CARTLIST_Next(c);
        }
        printf("Chupate ---------> %d\n",chupate);
        printf("intentando jugar la carta %d \n",ncarta);
    comp = Comprueba_Carta(b, &c->pdicard->c, &chupate);
    if (comp == ERROR) {
        View_Cart(c->pdicard->c);
        printf(" Esta carta no se puede jugar, escoge otra: ");
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
    CARTLIST_Go_First(c);

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
    printf("----------------------------------------------\n");
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
    printf("----------------------------------------------\n");
    printf("ESTAMOS EN EL TURNO %d LE TOCA A %s\n",turno,l->pdi->p->name);
    printf("----------------------------------------------\n\n");
}

//////////////////////////////////////////////////////////////////////
void Comprobar_Especial(Carta c, int *chupate, int *sentido, int *prohibido){
    switch (c.especial){
        case 1:
            if(*prohibido == 1){
                *prohibido=0;
            }
            if(*prohibido == 0){
                *prohibido = 1;
            }
            break;

        case 3:
            *chupate = *chupate+2;
            break;
        case 0:
            if(c.num == 11) {
                *chupate = *chupate + 4;
            }
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
void Comprobar_Sentido(Carta c, int *sentido){
    if(c.especial == 2) {
        if (*sentido == 1) {
            *sentido = 0;
        }else{
            *sentido = 1;
        }
    }
}
int Comprobar_Cambio_Color(Baraja *b,int *color,Playerlist *p) {
    int aux;
    Carta c;
    c.especial = 0;
    if (b->c->carta.especial == 4 || b->c->carta.especial == 5) {
        if (strcmp(p->pdi->p->type, "jugador") == 0) {
            return 1;
        } else {
            if ((p->pdi->p->cart.rojas >= p->pdi->p->cart.azules) &&
                (p->pdi->p->cart.rojas >= p->pdi->p->cart.amarillas) &&
                (p->pdi->p->cart.rojas >= p->pdi->p->cart.verdes)) {
                if (b->c->carta.especial == 4) {
                    c.num = 10;
                }
                if (b->c->carta.especial == 5) {
                    c.num = 11;
                }

                strcpy(c.color, "rojo");
                printf("%s cambia de color al %s", p->pdi->p->name, c.color);
                PILA_push(b, c);

            } else if ((p->pdi->p->cart.verdes >= p->pdi->p->cart.azules) &&
                       (p->pdi->p->cart.verdes >= p->pdi->p->cart.amarillas) &&
                       (p->pdi->p->cart.verdes >= p->pdi->p->cart.rojas)) {
                if (b->c->carta.especial == 4) {
                    c.num = 10;
                }
                if (b->c->carta.especial == 5) {
                    c.num = 11;
                }
                strcpy(c.color, "verde");
                printf("%s cambia de color al %s", p->pdi->p->name, c.color);
                PILA_push(b, c);
            } else if ((p->pdi->p->cart.azules >= p->pdi->p->cart.rojas) &&
                       (p->pdi->p->cart.azules >= p->pdi->p->cart.amarillas) &&
                       (p->pdi->p->cart.azules >= p->pdi->p->cart.verdes)) {
                if (b->c->carta.especial == 4) {
                    c.num = 10;
                }
                if (b->c->carta.especial == 5) {
                    c.num = 11;
                }
                strcpy(c.color, "azul");
                printf("%s cambia de color al %s", p->pdi->p->name, c.color);
                PILA_push(b, c);
            } else if ((p->pdi->p->cart.amarillas >= p->pdi->p->cart.rojas) &&
                       (p->pdi->p->cart.amarillas >= p->pdi->p->cart.azules) &&
                       (p->pdi->p->cart.amarillas >= p->pdi->p->cart.verdes)) {
                if (b->c->carta.especial == 4) {
                    c.num = 10;
                }
                if (b->c->carta.especial == 5) {
                    c.num = 11;
                }
                strcpy(c.color, "amarillo");
                printf("%s cambia de color al %s", p->pdi->p->name, c.color);
                PILA_push(b, c);
            }
        }
        return 0;
    }else {
        return 0;
    }
}
void Comprobar_nCartas_Baraja(Baraja *baraja, Baraja *pdescartes){
    printf("Quedan %d cartas en la baraja \n",baraja->cuantos);
    if (baraja->cuantos == 0){
        printf("Se ha quedado sin cartas \n");
        Recargar_Baraja(pdescartes, baraja);
    }
}
void Recargar_Baraja(Baraja *pdescartes, Baraja *baraja){
    printf("Recargando baraja 2 \n");
    Carta c = pdescartes->c->carta;
    PILA_pop(pdescartes);
    printf("Ultima carta en la piladescartes: ");
    View_Cart(c);
    printf("\n");
    for(int i = 0 ; i < pdescartes->cuantos ; i++){
        if(pdescartes->c->carta.num != 10 && pdescartes->c->carta.num != 11) {
            PILA_push(baraja, pdescartes->c->carta);
        }else{
            printf("Se ha eliminado una espedial");
        }
        PILA_pop(pdescartes);

    }
    PILA_push(pdescartes,c);



    BARAJA_mix(baraja);
}
int Comprobar_Gameover(Player *p){


        if(p->cart.ncartas == 0) {
            printf("%s - HA GANADO!\n", p->name);
            return 1;
        }else{
            return 0;
        }

    }

