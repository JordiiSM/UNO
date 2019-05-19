
#define ERROR 0
#define OK 1

#include <string.h>
#include "confplayers.h"
//--------------CREAR-------------------
Playerlist PLIST_Create(){
    Playerlist list;
    Node *Ghost1;
    Node *Ghost2;
    Ghost1 = (Node *) malloc(sizeof(Node)); //creamos fantasma inicial
    Ghost2 = (Node *) malloc(sizeof(Node)); //creamos fantasma final
    //control de errores
    if(Ghost1 == NULL || Ghost2 == NULL ){
        //error
    }else{
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
int PLIST_Insert(Playerlist *list, Player player){

    int i;
    int flag = 0;
    Node *n = (Node *) malloc(sizeof(Node));    //reservamos memoria para un nodo
    Player *p = (Player *) malloc(sizeof(Player));    //reservamos para una cancion
    *p = player;
    //Node *tmp = (Node *) malloc(sizeof(Node));
    //control de errores
    if(list->pdi == list->last){
        return ERROR;
    }else {
        n->p = p;

        //list->last = list->first;
/*
        while(strcmp(list->pdi->p->name, p->name) != 1){
            PLIST_Next(list);
        }
        */
//printf("%s\n",list->pdi->p->name);

        for (i = 0; i < list->nplayers || flag == 1; i++) {
            if (list->pdi->p->name < p->name) {
                PLIST_Next(list);
                } else {
                  flag = 1;
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
//---------------ELIMINAR-----------------
/*
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
//---------------OBTENER-----------------
Song PLIST_Get(Playerlist list){
    if(list.pdi == list.first || list.pdi == list.last){  //estem al final o principi
    }else{
        return *list.pdi->s;
    }
}
//---------------IS EMPTY-----------------
int PLIST_Is_Empty(Playerlist list){
    return list.pdi == list.last; //Como si fuera un if, devuelve 0 o 1
}
  */
//--------------IR AL PRINCIPIO DE LA LISTA ----------------------
void PLIST_Go_First(Playerlist *list){
    list->pdi = list->first;
    PLIST_Next(list);
}

//-----------------PASAR AL SIGUIENTE ELEMENTO DE LA LISTA---------------
int PLIST_Next(Playerlist *list){
    if(list->pdi->next == list->last){  //estem al final
        return ERROR;
    }else{
        list->pdi = list->pdi->next;
        return OK;
    }
}

//----------------PASAR AL ELEMENTO ANTERIOR DE LA LISTA ---------------
int PLIST_previous(Playerlist *list){
    if(list->pdi->previous == list->first){  //estem al final
        return ERROR;
    }else{
        list->pdi = list->pdi->previous;
        return OK;
    }
}
/*
//---------------BORRAR LA LISTA -------------------
void PLIST_Destroy(Playerlist *list){
    PLIST_Go_First(list);
    while(!PLIST_Is_Empty(*list)){
        PLIST_Remove(list);
    }
    free(list->first);     // free fantasma first
    free(list->last);      // free fantasma last
    list->first = list->last = NULL;    //asignamos null al first y last
}
*/
int Comprueba_Carta_Bot(Cartlist *list, Baraja *b,Baraja *baraja, int *chupate, int *ncarta){
    int aux = 3;
    int cont = 0;
    int flag = 0;
    int jugada = 3;
    int i;
    CARTLIST_Go_First(list);
    for(i = 0 ; i < list->ncartas ; i++) {
            flag = Comprueba_Carta(b,&list->pdicard->c,chupate);
            if(flag == OK){
                cont++;
            }

        CARTLIST_Next(list);

    }


    CARTLIST_Go_First(list);
    //printf("Puede jugar %d cartas\n",cont);
    if(cont > 0) {
            aux = Comprobar_Ceros(b, list, ncarta, chupate);
            if (aux == OK){
                printf("intentando jugar la carta  ZEROS %d \n",*ncarta);
                return OK;
            }
            CARTLIST_Go_First(list);
            aux = Comprobar_Color(b, list, b->c->carta, ncarta, chupate);
            if (aux == OK){
                printf("intentando jugar la carta COLOR %d \n",*ncarta);
                return OK;
            }
            CARTLIST_Go_First(list);
                /*for(int j = 1; j <= list->ncartas ; j++){
                    flag = Comprueba_Carta(b,&list->pdicard->c,chupate);
                    if(flag == OK){
                        printf("intentando jugar la carta OTROS %d \n",*ncarta);
                        *ncarta = j;
                        return OK;
                    }
                }*/
            aux = Comprobar_OTROS(b, list, b->c->carta, ncarta, chupate);
            if (aux == OK){
                printf("intentando jugar la carta OTROS %d \n",*ncarta);
                return OK;
            }
        CARTLIST_Go_First(list);
            }
    if(cont == 0){
        return ERROR;
    }
    return OK;

}

int Comprobar_Ceros(Baraja *b, Cartlist *list, int *ncarta, int *chupate){
    int i=0;
    int flag;
    for(i = 1 ; i <= list->ncartas; i++) {
       View_Cart(list->pdicard->c);
        if (list->pdicard->c.num == 0) {
            flag = Comprueba_Carta(b, &list->pdicard->c, chupate);

            printf("\n");
            if(flag == OK){

                *ncarta = i;

                CARTLIST_Go_First(list);
                return OK;
            }else{
                CARTLIST_Next(list);
            }
        }else {
            CARTLIST_Next(list);
        }
    }
    CARTLIST_Go_First(list);
    return ERROR;
}



int Comprobar_Color(Baraja *b, Cartlist *list, Carta c, int *ncarta, int *chupate){
    int flag;
    for(int i = 1 ; i <= list->ncartas; i++) {
        if (strcmp(list->pdicard->c.color,c.color)==0) {
            flag = Comprueba_Carta(b, &list->pdicard->c, chupate);

            printf("\n");
            if(flag == OK) {

                *ncarta = i;

                CARTLIST_Go_First(list);
                return OK;
            }

        }else{
            CARTLIST_Next(list);
        }
    }
    CARTLIST_Go_First(list);
    return ERROR;
}
int Comprobar_OTROS(Baraja *b, Cartlist *list, Carta c, int *ncarta, int *chupate) {
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