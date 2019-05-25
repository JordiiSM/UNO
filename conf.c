#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "conf.h"


//falta pasar fichero por argumento
Playerlist ADD_Players(char f[50]) {
    char ncartas[50], nplayers[50];
    int i, numplayers;
    int contplayers = 1;
    int val, val1;
    Playerlist *list = malloc(sizeof(Playerlist));
    *list = PLIST_Create();
    Cartlist c;
    FILE *file;
    Player tmp;
    char skip[MAXC];
    file = fopen(f, "r");
    if (file == NULL) {
        printf("No s'ha pogut obrir el fitxer \n");
    } else {
        fgets(nplayers, 100, file);
        numplayers = atoi(nplayers);
        list->nplayers = numplayers+1;
        for (i = 0; i <= numplayers; i++) {

            fgets(tmp.name, 100, file);
            tmp.name[strlen(tmp.name)-1]='\0';
            //printf("Nombre: %s \n", tmp.name);
            fgets(tmp.type, 100, file);
            //printf("Tipo: %s \n", tmp.type);
            fgets(ncartas, 100, file);
            c.cartasinicio = atoi(ncartas);
            tmp.cart = c;
            //printf("N cartas: %d \n", tmp.h->ncartas);
            PLIST_Insert(list, tmp, &contplayers);
           // list->pdi->p->cart.ncartas = list->pdi->p->cart.cartasinicio;
            //printf("Nombre insertado: %s \n", list->pdi->p->name);
            //printf("Prueba\n");

        }
        strcpy(tmp.name, "Jordi");
        strcpy(tmp.type,"jugador");
        c.cartasinicio = 1;
        tmp.cart = c;
        PLIST_Insert(list,tmp, &contplayers);
        fclose(file);
    }
    PLIST_Go_First(list);
    return *list;
}


void estadisticas_bots(Playerlist *pls, int npartidas){
    printf("\n\nUNO - Estadistica de bots \n\n");
    printf("\n-----------------------------------------------------------------------------------------------------\n");
    printf("Nombre\t\t\t\tP.Ganadas\t\t\t\tP.Perdidas\n");
    printf("\n-----------------------------------------------------------------------------------------------------\n");
    int totwinsagre = 0;
    int totwinscalm = 0;
    int porcwins = 0;
    int perdidas = 0;
    int porcperdidas = 0;
    perdidas = 0;
    for(int x = 0 ; x < pls->nplayers; x++) {
        if (strcmp(pls->pdi->p->type, "Agresivo") == 0) {
            totwinsagre = totwinsagre + pls->pdi->p->ganadas;
            PLIST_Next(pls);
        } else if (strcmp(pls->pdi->p->type, "Calmado") == 0) {
            totwinscalm = totwinscalm + pls->pdi->p->ganadas;
            PLIST_Next(pls);
        }
    }
    PLIST_Go_First(pls);
    for(int i = 0; i < pls->nplayers; i++){
        if(strcmp(pls->pdi->p->type, "jugador") != 0){
            printf("%s\t\t",pls->pdi->p->name);
            porcwins = (pls->pdi->p->ganadas * 100) /npartidas;
            perdidas = npartidas - pls->pdi->p->ganadas;
            porcperdidas = (perdidas * 100) /npartidas;
            printf("%d\t%d\t\t\t%d\t%d\n",pls->pdi->p->ganadas, porcwins, perdidas,porcperdidas );

        }
        PLIST_Next(pls);

    }

}




int lectura_fichero(Playerlist *p, char statsfile[50]) {//lectura view stats
    int cartas_array[50];
    char nombre[50];
    char ganadaschar[50];
    char perdidaschar[50];
    char cartas_manochar[50];
    int cartas_mano;
    int ganadas;
    int perdidas;
    float porcwin = 0;
    float porclose = 0;
    int totalgames;
    char skip;
    char msg;
    int j = 0;
    FILE *stats;
    stats = fopen(statsfile, "r");
    printf("\n-----------------------------------------------------------------------------------------------------\n");
    printf("UNO  -  Estadisticas del jugador\n");

    fgets(nombre, 100, stats);
    fgets(ganadaschar, 100, stats);
    ganadas = atoi(ganadaschar);
    fgets(perdidaschar, 100, stats);
    perdidas = atoi(perdidaschar);

    totalgames = ganadas + perdidas;
    porcwin = (ganadas * 100) / totalgames;
    porclose = (perdidas * 100) / totalgames;

    printf("Nombre: %s \n\n\n",nombre);
    printf("Estadisticas de partidas\n");
    printf("Ganadas:\t.....\t%d  (%.2f)\n",ganadas,porcwin);
    printf("Perdidas:\t.....\t%d  (%.2f)\n",perdidas,porclose);
    printf("Presiona enter para volver al menu principal");
    char enter=0;
    while(enter!='\r' && enter !='\n'){
        enter=getchar();
    }
    return 0;
}
int lectura_fichero_escritura(Playerlist *list, Player *p, char statsfile[50]) {//lectura view stats
    int *data = malloc(sizeof (int));
    int cartas_array[50];
    char nombre[50];
    char ganadaschar[50];
    char perdidaschar[50];
    char cartas_manochar[50];
    int cartas_mano;
    int ganadas;
    int perdidas;
    int j = 0;
    FILE *stats;
    stats = fopen(statsfile, "r");
    fgets(nombre, 100, stats);
    fgets(ganadaschar, 100, stats);
    ganadas = atoi(ganadaschar);
    fgets(perdidaschar, 100, stats);
    perdidas = atoi(perdidaschar);
   // int *tmp;
    while(!feof(stats)){
        fgets(cartas_manochar, 100, stats);
        sscanf(cartas_manochar,"%d",&data[j]);
        //data[j] = cartas_manochar;
        j++;
        data = realloc(data,j * sizeof(int)*2);

        printf("Realloc\n");
    }
    //data = tmp;
    fclose(stats);

    FILE* stats_escritura;
    stats_escritura = fopen(statsfile, "wr");
        printf("Abre el archibo");
        fprintf(stats_escritura, "%s", nombre);
        if(p->type == "jugador"){
            fprintf(stats_escritura, "%d\n", ganadas + 1);//mas la que gana
            fprintf(stats_escritura, "%d\n", perdidas);
        }else{
            fprintf(stats_escritura, "%d\n", ganadas);
            fprintf(stats_escritura, "%d\n", perdidas + 1);//mas la que pierdes
        }
        printf("Escritura bucle inicio");
        for(int x = 0; x < j; x++){
            fprintf(stats_escritura, "%d\n", data[x]);
        }
        PLIST_Go_First(list);
    for(int k = 0; k < list->nplayers; k++){
        if(strcmp(list->pdi->p->type, "jugador") != 0){
            PLIST_Next(list);
        }
    }
    fprintf(stats_escritura, "%d\n", list->pdi->p->cart.ncartas);

    fclose(stats_escritura);
    free(data);
    return 0;
}