/* Definiciones para la listas doblemente enlazadas de la memoria RAM, tabla y memoria virtual */

#ifndef LISTAS
#define LISTAS
#include <stddef.h>
//Declaración de la memoria virtual
struct mem_vir{ // Representa cada página virtual
    int n_pagina;
    struct nodo *ant;
    struct nodo *sig;

};
typedef struct mem_vir MEM_VIR;

//Declaración de la tabla
struct tabla{ // Representa cada celda
    int n_pagina;
    unsigned bits;
	int bit_pres_aus;
    struct nodo *ant;
    struct nodo *sig;

};
typedef struct tabla TABLA;

//Declaración de la memoria física
struct memoria{ // Representa cada marco de página
    int marco_pagina;
    struct nodo *ant;
    struct nodo *sig;

};
typedef struct memoria MEMORIA;

//Definición de los frentes
MEM_VIR *mv = NULL;
TABLA *tb = NULL;
MEMORIA *mm = NULL;


//Definición de las funciones a usar
void construccion(void);
void insertar(int, int);
int retirar(int);
void mostrar(int);
void vaciar (int);

#endif // COLITA
