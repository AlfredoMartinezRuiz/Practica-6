/* Definiciones para la listas doblemente enlazadas de la memoria RAM, tabla y memoria virtual */

# ifndef LISTAS
# define LISTAS

# define memoria_virtual 1
# define tabla_con 2
# define ram 3
//Declaración de la memoria virtual
struct mem_vir{ // Representa cada página virtual (4KB)
    int n_pagina;
    struct mem_vir *ant;
    struct mem_vir *sig;

};
typedef struct mem_vir MEM_VIR;

//Declaración de la tabla
struct tabla{ // Representa cada celda
    int n_pagina;
    unsigned bits;
	int bit_pres_aus;
    struct tabla *ant;
    struct tabla *sig;

};
typedef struct tabla TABLA;

//Declaración de la memoria física
struct memoria{ // Representa cada marco de página (4KB)
    int marco_pagina;
    struct memoria *ant;
    struct memoria *sig;

};
typedef struct memoria MEMORIA;

//Definición de los frentes
MEM_VIR *mv = NULL;
TABLA *tb = NULL;
MEMORIA *mm = NULL;


//Definición de las funciones a usar (type es el tipo de estructura)
void construccion(int nodo, int type); /* Construye el número de nodos para cada lista, en la memoria virtual y tabla son 16 y en la ram son 8. Esto depende 
del tamaño total y el tamaño por nodo, en este caso el tamaño del nodo son 4KB, el nodo indica el índice*/
void inicio(int type); // Reinicia los frentes al primer nodo
void mostrar(int type); // Muestra la lista
# endif // COLITA
