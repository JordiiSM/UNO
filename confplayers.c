
#define ERROR 0
#define OK 1

#include <string.h>
#include "confplayers.h"

//--------------CREAR-------------------
Playerlist PLIST_Create() {
    Playerlist list;
    Node *Ghost1;
    Node *Ghost2;
    Ghost1 = (Node *) malloc(sizeof(Node)); //creamos fantasma inicial
    Ghost2 = (Node *) malloc(sizeof(Node)); //creamos fantasma final
    //control de errores
    if (Ghost1 == NULL || Ghost2 == NULL) {
        //error
    } else {
        Ghost1->next = Ghost2;  //asigna el fantasma final al next del inicial
        Ghost1->previous = NULL;    //pone a null el anterior al inicial
        Ghost2->next = NULL;    //pone a null el siguiente al final
        Ghost2->previous = Ghost1;  //guarda la posicion del fantasma inicial en la posicion anterior del final
        list.first = Ghost1;    //pone como primera posiciÃ³n de la lista el fantasma inicial
        list.last = Ghost2;     //pone como ultima posiciÃ³n de la lista el fantasma final
        list.pdi = Ghost1;      //guarda como punto de interes el fantasma inicial
    }
    return list;
}

//---------------INSERTAR----------------
int PLIST_Insert(Playerlist *list, Player player, int *numplayers) {
    numplayers++;
    int i;
    int flag = 0;
    Node *n = (Node *) malloc(sizeof(Node));    //reservamos memoria para un nodo
    Player *p = (Player *) malloc(sizeof(Player));    //reservamos para una cancion
    *p = player;
    int tmp;
    if (list->pdi == list->last) {
        return ERROR;
    } else {
        n->p = p;
        PLIST_Go_First(list);
        while (((list->pdi->next != list->last) || (*numplayers == 1)) && strcmp(list->pdi->p->name, p->name) < 0) {
            tmp = PLIST_Next(list);
            if (strcmp(list->pdi->p->name, p->name) < 0 && *numplayers == 1) {
                *numplayers = 2;
            }
        }

        n->next = list->pdi->next;
        n->previous = list->pdi;
        n->next->previous = n;
        list->pdi->next = n;
        list->pdi = n;

        PLIST_Go_First(list);
    }


    return OK;
}

//---------------ELIMINAR------------
int PLIST_Remove(Playerlist *list) {
    Node *tmp;
    if (list->pdi == list->first || list->pdi == list->last) {  //estem al final
        return ERROR;
    } else {
        tmp = list->pdi;                 // (1)
        tmp->next->previous = tmp->previous;    // (2)
        tmp->previous->next = tmp->next;
        list->pdi = tmp->next;
        free(tmp);
        return OK;
    }
}


//---------------IS EMPTY-----------------
int PLIST_Is_Empty(Playerlist list) {
    return list.pdi == list.last; //Como si fuera un if, devuelve 0 o 1
}

//--------------IR AL PRINCIPIO DE LA LISTA ----------------------
void PLIST_Go_First(Playerlist *list) {
    list->pdi = list->first;
    PLIST_Next(list);
}

//-----------------PASAR AL SIGUIENTE ELEMENTO DE LA LISTA---------------
int PLIST_Next(Playerlist *list) {
    if (list->pdi->next == list->last) {  //estem al final
        return ERROR;
    } else {
        list->pdi = list->pdi->next;
        return OK;
    }
}

//----------------PASAR AL ELEMENTO ANTERIOR DE LA LISTA ---------------
int PLIST_previous(Playerlist *list) {
    if (list->pdi->previous == list->first) {  //estem al final
        return ERROR;
    } else {
        list->pdi = list->pdi->previous;
        return OK;
    }
}

//---------------BORRAR LA LISTA -------------------
void PLIST_Destroy(Playerlist *list) {
    PLIST_Go_First(list);
    while (!PLIST_Is_Empty(*list)) {
        PLIST_Remove(list);
    }
    free(list->first);     // free fantasma first
    free(list->last);      // free fantasma last
    list->first = list->last = NULL;    //asignamos null al first y last
}
// Comprobar las cartas que pueden tirar los bots
int Comprueba_Carta_Bot(Playerlist *p, Cartlist *list, Baraja *b, Baraja *baraja, int *chupate, int *ncarta) {
    int aux = 3;
    int cont = 0;
    int flag = 0;
    int jugada = 3;
    int i;
    CARTLIST_Go_First(list);
    for (i = 0; i < list->ncartas; i++) {
        flag = Comprueba_Carta(b, &list->pdicard->c, chupate);
        if (flag == OK) {
            cont++;
        }

        CARTLIST_Next(list);

    }
    CARTLIST_Go_First(list);
    if (cont > 0) {
        if (strcmp(p->pdi->p->type, "Agresivo") == 0) {
            aux = comprobarAgresivo(b, list, ncarta, chupate);
            if (aux == OK) {
                return OK;
            }
        }
        CARTLIST_Go_First(list);
        aux = Comprobar_Ceros(b, list, ncarta, chupate);
        if (aux == OK) {
            return OK;
        }
        CARTLIST_Go_First(list);
        aux = Comprobar_Color(b, list, b->c->carta, ncarta, chupate);
        if (aux == OK) {
            return OK;
        }
        CARTLIST_Go_First(list);
        aux = Comprobar_OTROS(p, b, list, b->c->carta, ncarta, chupate);
        if (aux == OK) {
            return OK;
        }
        CARTLIST_Go_First(list);
        return ERROR;
    }

    if (cont == 0) {
        return ERROR;
    }

}
//Comprobacion en caso de que sea un 0 la ultima carta de la pila de descartes
int Comprobar_Ceros(Baraja *b, Cartlist *list, int *ncarta, int *chupate) {
    int i = 0;
    int flag;
    for (i = 1; i <= list->ncartas; i++) {
        View_Cart(list->pdicard->c);
        if (list->pdicard->c.num == 0) {
            flag = Comprueba_Carta(b, &list->pdicard->c, chupate);

            printf("\n");
            if (flag == OK) {

                *ncarta = i;

                CARTLIST_Go_First(list);
                return OK;
            } else {
                CARTLIST_Next(list);
            }
        } else {
            CARTLIST_Next(list);
        }
    }
    CARTLIST_Go_First(list);
    return ERROR;
}

// Comprobar color de la ultima carta de la pila de descartes
int Comprobar_Color(Baraja *b, Cartlist *list, Carta c, int *ncarta, int *chupate) {
    int flag;
    for (int i = 1; i <= list->ncartas; i++) {
        if (strcmp(list->pdicard->c.color, c.color) == 0) {
            flag = Comprueba_Carta(b, &list->pdicard->c, chupate);

            printf("\n");
            if (flag == OK) {

                *ncarta = i;

                CARTLIST_Go_First(list);
                return OK;
            }

        } else {
            CARTLIST_Next(list);
        }
    }
    CARTLIST_Go_First(list);
    return ERROR;
}
// Comprobar numero y especiales de la mano comparandola con la ultima carta de la pila de descartes
int Comprobar_OTROS(Playerlist *p, Baraja *b, Cartlist *list, Carta c, int *ncarta, int *chupate) {
    int flag;
    for (int i = 1; i <= list->ncartas; i++) {
        flag = Comprueba_Carta(b, &list->pdicard->c, chupate);
        printf("\n");
        if (flag == OK) {
            *ncarta = i;
            CARTLIST_Go_First(list);
            return OK;
        }

        CARTLIST_Next(list);
    }

    CARTLIST_Go_First(list);
    return ERROR;
}
// en caso de que el jugador sea agresivo intentar tirar las especiales cuando sea posible
int comprobarAgresivo(Baraja *b, Cartlist *list, int *ncarta, int *chupate) {
    int i = 0;
    int flag;
    for (i = 1; i <= list->ncartas; i++) {
        if (list->pdicard->c.especial == 4 || list->pdicard->c.especial == 5) {
            flag = Comprueba_Carta(b, &list->pdicard->c, chupate);
            printf("\n");
            if (flag == OK) {
                *ncarta = i;
                CARTLIST_Go_First(list);
                return OK;
            } else {
                CARTLIST_Next(list);
            }
        } else {
            CARTLIST_Next(list);
        }
    }
    CARTLIST_Go_First(list);
    return ERROR;
}