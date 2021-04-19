/* Definiciones para la listas doblemente enlazadas de la memoria RAM, tabla y memoria virtual */

#ifndef LISTAS
#define LISTAS
#include <stddef.h>
//Declaraci�n de la memoria virtual
struct mem_vir{ // Representa cada p�gina virtual
    int n_pagina;
    struct nodo *ant;
    struct nodo *sig;

};
typedef struct mem_vir MEM_VIR;

//Declaraci�n de la tabla
struct tabla{ // Representa cada celda
    int n_pagina;
    unsigned bits;
	int bit_pres_aus;
    struct nodo *ant;
    struct nodo *sig;

};
typedef struct tabla TABLA;

//Declaraci�n de la memoria f�sica
struct memoria{ // Representa cada marco de p�gina
    int marco_pagina;
    struct nodo *ant;
    struct nodo *sig;

};
typedef struct memoria MEMORIA;

//Definici�n de los frentes
MEM_VIR *mv = NULL;
TABLA *tb = NULL;
MEMORIA *mm = NULL;


//Definici�n de las funciones a usar
void construccion(void);
void insertar(int, int);
int retirar(int);
void mostrar(int);
void vaciar (int);

#endif // COLITA
