/* Definiciones para la listas doblemente enlazadas de la memoria RAM, tabla y memoria virtual */

# ifndef LISTAS
# define LISTAS

# define memoria_virtual 1
# define tabla_con 2
# define ram 3
//Declaración de la memoria virtual
struct mem_vir{ // Representa cada página virtual (4KB)
	int pagina_binario[4]; // indice en binario
	int pagina_decimal;
	int marco_pagina; // Qué página es en RAM
    struct mem_vir *ant;
    struct mem_vir *sig;

};
typedef struct mem_vir MEM_VIR;

//Declaración de la tabla
struct tabla{ // Representa cada celda
    int n_pagina;
    int marco_binario[3];
	int bit_pres_aus;
    struct tabla *ant;
    struct tabla *sig;

};
typedef struct tabla TABLA;

//Declaración de la memoria física
struct memoria{ // Representa cada marco de página (4KB)
    int orden; // Identifica el orden como fue ocupada, comienza en 0 y termina en 7
    int marco_binario[3]; // Indice en binario
    int marco_decimal;
    int marco_pagina; // Qué página es en virtual
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
int num_random(); // Funcion para crear un numero aleatorio
void invertir_arreglo(int *ptr_arreglo, int tam); // Funcion para invertir un arreglo (de bits)
void dec_bin(int num, int *ptr_arreglo, int tam); // Funcion paara convertir numero decimal a binario
int bin_dec(int *ptr_arreglo, int tam); // Funcion para convertir de un numero binario a decimal
void paginar(int n_pagina); // Funcion para hacer la paginacion inicial usando numeros aleatorios
int solicitar_espacio(); // Funcion para buscar algún espacio libre en la memoria, devuelve el índice en decimal
int num_random_extendido(); // Funcion para crear un numero aleatorio entre 0 y 15
void fallo_pagina(int n_pagina, TABLA *aux_tb, MEM_VIR *aux_mv); // En caso de que la memoria RAM este llena, ejecutaremos el algoritmo FIFO para reemplazar alguna pagina

# endif
