#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Map.h"
#include "List.h"
#include "SortedMap.h"

typedef struct{
    char nombre[50];
    SortedMap* fechas;
}ramo;

typedef struct{
    char rut[10];
    List* ramos_impartir;
}profesor;

typedef struct{
    char rut[10];
    List* ramos_seleccionados;
}alumno;

long long stringHash(const void * key) {
    long long hash = 5381;

    const char * ptr;

    for (ptr = key; *ptr != '\0'; ptr++) {
        hash = ((hash << 5) + hash) + tolower(*ptr); /* hash * 33 + c */
    }

    return hash;
}

int stringEqual(const void * key1, const void * key2) {
    const char * A = key1;
    const char * B = key2;

    return strcmp(A, B) == 0;
}

int cmpMin(const void * p1, const void * p2) {
    const int * a = p1;
    const int * b = p2;
    return *b - *a;
}

int cmpstring(const void * p1, const void * p2){
    const char * a = p1;
    const char * b = p2;
    return strcmp(a,b);
}

void crear_mapa_ramo(Map*);
void *iniciar_sesion(Map*);
void *crear_alumno(Map*);
void *crear_profesor(Map*);
void mostrar_ramo(Map*);

int main(){
    int opcion=0,crear_iniciar=0,opc_fechas=0,otra_fecha=0,menu_usuario,usuario=0;
    char *fecha;
    ramo* ramotemp;
    char ramoseleccionado[20];
    Map *mapa_alumnos=createMap(stringHash, stringEqual),*mapa_profesores=createMap(stringHash, stringEqual),*mapa_ramo=createMap(stringHash, stringEqual);
    alumno *student;
    profesor *docente;
    crear_mapa_ramo(mapa_ramo);
    while (opcion!=3){
        printf("-----------------------CALENDAX----------------------\n");
        printf("(1) Iniciar Sesion\n");
        printf("(2) Crear usuario\n");
        printf("(3) Salir\n");
        printf("-----------------------------------------------------\n");
        do{
            scanf("%d",&opcion);
            if ((opcion!=1)&&(opcion!=2)&&(opcion!=3)){
                printf("Ingrese un numero valido\n");
            }
        }while ((opcion!=1)&&(opcion!=2)&&(opcion!=3));

        //INICIAR SESION

        if (opcion==1){
            printf("-----------------------------------------------------\n");
            printf("Ingrese su cargo:\n");
            printf("(1) Alumno\n(2) Profesor\n");
            printf("------------------------------------------------------\n");
            do{
                scanf("%d",&crear_iniciar);
                getchar();
                if ((crear_iniciar!=1)&&(crear_iniciar!=2)){
                    printf("Ingrese un numero valido\n");
                }
            }while ((crear_iniciar!=1)&&(crear_iniciar!=2));
            printf("------------------------------------------------------\n");
            if (crear_iniciar==1){
                student=iniciar_sesion(mapa_alumnos);
                if (student->rut==NULL){
                    printf("------------------------------------------------------\n");
                    printf("El usuario no existe\n");
                    continue;
                }
                usuario=1;
            }
            if (crear_iniciar==2){
                docente=iniciar_sesion(mapa_profesores);
                if (docente->rut==NULL){
                    printf("------------------------------------------------------\n");
                    printf("El usuario no existe\n");
                    continue;
                }
                usuario=2;
            }
            printf("-----------------------------------------------------\n");
            printf("Se ha iniciado sesion correctamente\n");
        }

        //CREAR USUARIO

        if (opcion==2){
            printf("-----------------------------------------------------\n");
            printf("Ingrese su cargo:\n");
            printf("(1) Alumno\n(2) Profesor\n");
            printf("------------------------------------------------------\n");
            do{
                scanf("%d",&crear_iniciar);
                getchar();
                if ((crear_iniciar!=1)&&(crear_iniciar!=2)){
                    printf("Ingrese un numero valido\n");
                }
            }while ((crear_iniciar!=1)&&(crear_iniciar!=2));
            printf("------------------------------------------------------\n");
            if (crear_iniciar==2){
                docente=crear_profesor(mapa_profesores);
                if (docente==NULL){
                    printf("------------------------------------------------------\n");
                    printf("El usuario ya existe\n");
                    continue;
                }
            }
            if (crear_iniciar==1){
                student=crear_alumno(mapa_alumnos);
                if (student==NULL){
                    printf("------------------------------------------------------\n");
                    printf("El usuario ya existe\n");
                    continue;
                }
            }
            printf("------------------------------------------------------\n");
            printf("Se ha creado el usuario\n");
        }

        //SALIR DEL PROGRAMA

        if (opcion==3){
            continue;
        }

        //USUARIO ALUMNO

        if (usuario==1){
            menu_usuario=0;
            while (menu_usuario!=4){
                printf("------------------------------------------------------\n");
                printf("Seleccione una opcion:\n");
                printf("(1) Agregar ramos\n");
                printf("(2) Visualizar sus ramos\n");
                printf("(3) Visualizar Fechas\n");
                printf("(4) Cerrar sesion\n");
                printf("------------------------------------------------------\n");
                do{
                    scanf("%d",&menu_usuario);
                    if ((menu_usuario!=1)&&(menu_usuario!=2)&&(menu_usuario!=3)&&(menu_usuario!=4)){
                        printf("Ingrese un numero valido\n");
                    }
                }while ((menu_usuario!=1)&&(menu_usuario!=2)&&(menu_usuario!=3)&&(menu_usuario!=4));
                if (menu_usuario==1){
                    printf("------------------------------------------------------\n");
                    printf("Ingrese el nombre de los ramos que cursa\n");
                    printf("Ingrese 0 para terminar\n\n");
                    mostrar_ramo(mapa_ramo);
                    printf("------------------------------------------------------\n");
                    while(strcmp(ramoseleccionado,"0")){
                        scanf("%s",ramoseleccionado);
                        ramotemp=searchMap(mapa_ramo,ramoseleccionado);
                        if (strcmp(ramoseleccionado,"0")){
                            if (ramotemp!=NULL){
                                pushBack(student->ramos_seleccionados,ramotemp);
                                printf("Ramo insertado correctamente\n");
                                printf("------------------------------------------------------\n");
                            }else{
                                printf("El ramo ingresado no existe\n");
                                printf("------------------------------------------------------\n");
                            }
                        }
                    }
                    strcpy(ramoseleccionado,"1");
                }

                //MOSTRAR RAMOS DEL ALUMNO

                if (menu_usuario==2){
                    printf("------------------------------------------------------\n");
                    printf("Los ramos que cursa son:\n\n");
                    ramo * aux=firstList(student->ramos_seleccionados);
                    for (int i=0;i<listCount(student->ramos_seleccionados);i++){
                        printf("%s\n",aux->nombre);
                        aux=nextList(student->ramos_seleccionados);
                    }
                }

                //MOSTRAR FECHAS DEL ALUMNO

                if (menu_usuario==3){
                    ramo * aux=firstList(student->ramos_seleccionados);
                    char *aux2;
                    printf("------------------------------------------------------\n");
                    printf("Sus evaluaciones son:\n\n");
                    for (int i=0;i<listCount(student->ramos_seleccionados);i++){
                        printf("%s:\n",aux->nombre);
                        aux2=firstSortedMap(aux->fechas);
                        while (aux2!=NULL){
                            printf("-> %c%c/%c%c/%c%c%c%c\n",aux2[6],aux2[7],aux2[4],aux2[5],aux2[0],aux2[1],aux2[2],aux2[3]);
                            aux2=nextSortedMap(aux->fechas);
                        }
                        aux=nextList(student->ramos_seleccionados);
                    }
                    printf("\n");
                }
            }
        }

        //USUARIO PROFESOR

        if (usuario==2){
            menu_usuario=0;
            usuario=0;
            while (menu_usuario!=4){
                printf("------------------------------------------------------\n");
                printf("Seleccione una opcion:\n");
                printf("(1) Agregar ramos\n");
                printf("(2) Mostrar fechas de sus ramos\n");
                printf("(3) Modificar fechas\n");
                printf("(4) Cerrar sesion\n");
                printf("------------------------------------------------------\n");
                do{
                    scanf("%d",&menu_usuario);
                    if ((menu_usuario!=1)&&(menu_usuario!=2)&&(menu_usuario!=3)&&(menu_usuario!=4)){
                        printf("Ingrese un numero valido\n");
                    }
                }while ((menu_usuario!=1)&&(menu_usuario!=2)&&(menu_usuario!=3)&&(menu_usuario!=4));

                //SELECCIONAR RAMOS PROFESOR

                if (menu_usuario==1){
                    printf("------------------------------------------------------\n");
                    printf("Ingrese el nombre de los ramos que imparte\n");
                    printf("Ingrese 0 para terminar\n\n");
                    mostrar_ramo(mapa_ramo);
                    printf("------------------------------------------------------\n");
                    while(strcmp(ramoseleccionado,"0")){
                        scanf("%s",ramoseleccionado);
                        ramotemp=searchMap(mapa_ramo,ramoseleccionado);
                        if (strcmp(ramoseleccionado,"0")){
                            if (ramotemp!=NULL){
                                pushBack(docente->ramos_impartir,ramotemp);
                                printf("Ramo insertado correctamente\n");
                                printf("------------------------------------------------------\n");
                            }else{
                                printf("El ramo ingresado no existe\n");
                                printf("------------------------------------------------------\n");
                            }
                        }
                    }
                    strcpy(ramoseleccionado,"1");
                }

                //MOSTRAR FECHA EVALUACIONES

                if (menu_usuario==2){
                    ramo * aux=firstList(docente->ramos_impartir);
                    char *aux2;
                    printf("------------------------------------------------------\n");
                    printf("Las fechas de las evaluaciones en sus ramos son:\n\n");
                    for (int i=0;i<listCount(docente->ramos_impartir);i++){
                        printf("%s:\n",aux->nombre);
                        aux2=firstSortedMap(aux->fechas);
                        while (aux2!=NULL){
                            printf("-> %c%c/%c%c/%c%c%c%c\n",aux2[6],aux2[7],aux2[4],aux2[5],aux2[0],aux2[1],aux2[2],aux2[3]);
                            aux2=nextSortedMap(aux->fechas);
                        }
                        aux=nextList(docente->ramos_impartir);
                    }
                    printf("\n");
                }

                //MODIFICAR FECHA EVALUACION

                if (menu_usuario==3){
                    printf("------------------------------------------------------\n");
                    printf("¿Que desea realizar?\n");
                    printf("(1) Agregar fecha de evaluacion\n");
                    printf("(2) Eliminar fecha de evaluacion\n");
                    printf("(3) Volver\n");
                    printf("------------------------------------------------------\n");
                    do{
                        scanf("%d",&opc_fechas);
                        getchar();
                        if ((opc_fechas!=1)&&(opc_fechas!=2)&&(opc_fechas!=3)){
                            printf("Ingrese un numero valido\n");
                        }
                    }while ((opc_fechas!=1)&&(opc_fechas!=2)&&(opc_fechas!=3));

                    //AGREGAR FECHA EVALUACION

                    if (opc_fechas==1){
                        printf("------------------------------------------------------\n");
                        printf("Usted imparte los siguientes ramos:\n\n");
                        ramo * aux=firstList(docente->ramos_impartir);
                        for (int i=0;i<listCount(docente->ramos_impartir);i++){
                            printf("%s\n",aux->nombre);
                            aux=nextList(docente->ramos_impartir);
                        }
                        printf("\nIngrese el nombre del ramo al que desea agregar una fecha de evaluacion\n");
                        printf("------------------------------------------------------\n");
                        scanf("%s",ramoseleccionado);
                        getchar();
                        ramotemp=searchMap(mapa_ramo,ramoseleccionado);
                        while (ramotemp==NULL){
                            printf("El ramo ingresado no existe\n");
                            printf("------------------------------------------------------\n");
                            scanf("%s",ramoseleccionado);
                            getchar();
                            ramotemp=searchMap(mapa_ramo,ramoseleccionado);
                        }
                        while(1){
                            printf("------------------------------------------------------\n");
                            printf("Ingrese la fecha de evaluacion en formato AAAAMMDD\n");
                            fecha=(char*)malloc(sizeof(char)*(10));
                            do{
                                scanf("%s",fecha);
                                if (strlen(fecha)!=8){
                                    printf("Ingrese una fecha valida\n");
                                }
                            }while(strlen(fecha)!=8);
                            printf("------------------------------------------------------\n");
                            insertSortedMap(ramotemp->fechas,fecha,fecha);
                            printf("¿Desea ingresar otra fecha?\n");
                            printf("(1) Si\n");
                            printf("(2) No\n");
                            printf("------------------------------------------------------\n");
                            scanf("%d",&otra_fecha);
                            if (otra_fecha==2){
                                break;
                            }
                        }
                    }

                    //ELIMINAR FECHA EVALUACION

                    if (opc_fechas==2){
                        printf("Usted imparte los siguientes ramos:\n\n");
                        ramo * aux=firstList(docente->ramos_impartir);
                        for (int i=0;i<listCount(docente->ramos_impartir);i++){
                            printf("%s\n",aux->nombre);
                            aux=nextList(docente->ramos_impartir);
                        }
                        printf("\nIngrese el nombre del ramo al que desea eliminar una fecha de evaluacion\n");
                        printf("------------------------------------------------------\n");
                        scanf("%s",ramoseleccionado);
                        getchar();
                        ramotemp=searchMap(mapa_ramo,ramoseleccionado);
                        while (ramotemp==NULL){
                            printf("El ramo ingresado no existe\n");
                            printf("------------------------------------------------------\n");
                            scanf("%s",ramoseleccionado);
                            getchar();
                            ramotemp=searchMap(mapa_ramo,ramoseleccionado);
                        }
                        printf("------------------------------------------------------\n");
                        printf("Ingrese la fecha a borrar en formato AAAAMMDD\n");
                        fecha=(char*)malloc(sizeof(char)*(10));
                        do{
                            scanf("%s",fecha);
                            if (strlen(fecha)!=8){
                                printf("Ingrese una fecha valida\n");
                            }
                        }while(strlen(fecha)!=8);
                        if (searchSortedMap(ramotemp->fechas,fecha)==NULL){
                            printf("La fecha ingresada no existe\n");
                        }else{
                            eraseKeySortedMap(ramotemp->fechas,fecha);
                            printf("La fecha ha sido eliminada exitosamente\n");
                        }
                        free(fecha);
                    }
                }
            }
        }
    }
    printf("-----------------------------------------------------\n");
    printf("\nsaludos,\n--\nWence\n");
}

void crear_mapa_ramo(Map* mapa){
    char dato[50];
    ramo *aux;
    FILE *fp;
    fp = fopen ("materias.txt","r");
    while (!feof(fp)){
        fscanf(fp," %[^\n]",&dato);
        aux=(ramo*)malloc(sizeof(ramo));
        strcpy(aux->nombre,dato);
        aux->fechas=createSortedMap(cmpstring);
        insertMap(mapa,aux->nombre,aux);
    }
}

void* iniciar_sesion(Map* mapa){
    char rut[10];
    printf("Ingrese su RUT sin puntos ni digito verificador:\n");
    do{
        gets(rut);
        if ((strlen(rut)<7)||(strlen(rut)>8)){
            printf("Ingrese un RUT valido\n");
        }
    }while((strlen(rut)<7)||(strlen(rut)>8));
    if (searchMap(mapa,rut)!=NULL){
        return searchMap(mapa,rut);
    }
    return NULL;
}

void* crear_alumno(Map* mapa){
    char rut[10];
    alumno *aux;
    printf("Ingrese su RUT sin puntos ni digito verificador:\n");
    do{
        gets(rut);
        if ((strlen(rut)<7)||(strlen(rut)>8)){
            printf("Ingrese un RUT valido\n");
        }
    }while((strlen(rut)<7)||(strlen(rut)>8));
    if (searchMap(mapa,rut)!=NULL){
        return NULL;
    }
    aux=(alumno*)malloc(sizeof(alumno));
    strcpy(aux->rut,rut);
    aux->ramos_seleccionados=createList();
    insertMap(mapa,aux->rut,aux);
    return aux;
}

void* crear_profesor(Map* mapa){
    char rut[10];
    profesor *aux;
    printf("Ingrese su RUT sin puntos ni digito verificador:\n");
    do{
        gets(rut);
        if ((strlen(rut)<7)||(strlen(rut)>8)){
            printf("Ingrese un RUT valido\n");
        }
    }while((strlen(rut)<7)||(strlen(rut)>8));
    if (searchMap(mapa,rut)!=NULL){
        return NULL;
    }
    aux=(profesor*)malloc(sizeof(profesor));
    strcpy(aux->rut,rut);
    aux->ramos_impartir=createList();
    insertMap(mapa,aux->rut,aux);
    return aux;
}

void mostrar_ramo(Map* mapa){
    int i=1;
    ramo *aux;
    aux=firstMap(mapa);
    printf("(%d) %s\n",i,aux->nombre);
    aux=nextMap(mapa);
    while(aux!=NULL){
        i++;
        printf("(%d) %s\n",i,aux->nombre);
        aux=nextMap(mapa);
    }
    return 0;
}
