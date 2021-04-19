/* Definiciones para la listas doblemente enlazadas de la memoria RAM, tabla y memoria virtual */

# ifndef LISTAS
# define LISTAS

# define memoria_virtual 1
# define tabla_con 2
# define ram 3
//Declaraci�n de la memoria virtual
struct mem_vir{ // Representa cada p�gina virtual (4KB)
    int n_pagina;
    struct mem_vir *ant;
    struct mem_vir *sig;

};
typedef struct mem_vir MEM_VIR;

//Declaraci�n de la tabla
struct tabla{ // Representa cada celda
    int n_pagina;
    unsigned bits;
	int bit_pres_aus;
    struct tabla *ant;
    struct tabla *sig;

};
typedef struct tabla TABLA;

//Declaraci�n de la memoria f�sica
struct memoria{ // Representa cada marco de p�gina (4KB)
    int marco_pagina;
    struct memoria *ant;
    struct memoria *sig;

};
typedef struct memoria MEMORIA;

//Definici�n de los frentes
MEM_VIR *mv = NULL;
TABLA *tb = NULL;
MEMORIA *mm = NULL;


//Definici�n de las funciones a usar (type es el tipo de estructura)
void construccion(int nodo, int type); /* Construye el n�mero de nodos para cada lista, en la memoria virtual y tabla son 16 y en la ram son 8. Esto depende 
del tama�o total y el tama�o por nodo, en este caso el tama�o del nodo son 4KB, el nodo indica el �ndice*/
void inicio(int type); // Reinicia los frentes al primer nodo
void mostrar(int type); // Muestra la lista
# endif // COLITA
