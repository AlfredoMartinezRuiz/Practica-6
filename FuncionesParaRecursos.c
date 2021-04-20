/* Funciones para manipular cada una de las listas y la información entre ellas */
# include <stdio.h>
# include <stdlib.h>
#include <time.h>
# include "Defs-Memoria-Tabla-Virtual.h"

//Funcion para crear un numero aleatorio
int num_random(){
	int x;
	srand(time(NULL));
	x = rand()%8;	//Vamos a generar un numero entre 0 y 7 
	return x;
}

void construccion(int nodo, int type){
//	printf("Este es el nodo:  %d\n", nodo);
    switch(type){
    	case 1: ; // Si es una memoria virtual
    		MEM_VIR *nuevo_mv = (MEM_VIR *) malloc(sizeof(MEM_VIR));
			if(nodo < 16){				
				nuevo_mv -> ant = mv;
		        nuevo_mv -> sig = NULL;
		        nuevo_mv -> n_pagina = nodo;
		     //   nuevo_mv -> pagina_binario1=nodo;
		        //Paso el nodo a binario
		      	int n = nodo;
				int i = 0;
	
				while(i<4){
					nuevo_mv -> pagina_binario[i] = n%2;
					n = n/2;
					i++;
				} //Termino de pasar el nodo a binario
		      	
		        nuevo_mv -> marco_pagina = 0;
		        if(mv != NULL) mv -> sig = nuevo_mv;
		        mv = nuevo_mv;
				construccion(nodo+1, type);
		    }
    		break;
    		
    	case 2: ; // Si es la tabla
    		TABLA *nuevo_tb = (TABLA *) malloc(sizeof(TABLA));
			if(nodo < 16){
				nuevo_tb -> ant = tb;
		        nuevo_tb -> sig = NULL;
		        nuevo_tb -> n_pagina = nodo;
		      //  nuevo_tb -> marco_binario[];
		        nuevo_tb -> bit_pres_aus = 0;
		        if(tb != NULL) tb -> sig = nuevo_tb;
		        tb = nuevo_tb;
		        construccion(nodo+1, type);
		    }
    		break;
    		
    	case 3: ; // Si es la memoria física
    		MEMORIA *nuevo_mm = (MEMORIA *) malloc(sizeof(MEMORIA));
			if(nodo < 8){
				nuevo_mm -> ant = mm;
		        nuevo_mm -> sig = NULL;
		        nuevo_mm -> marco_pagina = nodo;
		        
		        //Paso el nodo a binario
		      	int n = nodo;
				int i = 0;
	
				while(i<3){
					nuevo_mm -> marco_binario[i] = n%2;
					n = n/2;
					i++;
				} //Termino de pasar el nodo a binario
				
				nuevo_mm->n_pagina = 0;
		        if(mm != NULL) mm -> sig = nuevo_mm;
		        mm = nuevo_mm;
		        construccion(nodo+1, type);
		    }
    		break;
	}	    
}

void inicio(int type){
	switch(type){
		case 1: // Si es una memoria virtual
			if(mv -> ant != NULL){
				mv = mv -> ant;				
				inicio(type);
			}
			break;
		case 2: // Si es la tabla
			if(tb -> ant != NULL){
				tb = tb -> ant;				
				inicio(type);
			}
			break;
		case 3: // Si es la memoria física
			if(mm -> ant != NULL){
				mm = mm -> ant;				
				inicio(type);
			}
			break;
	}
}

void mostrar(int type){
	//	printf("\nLista completa: \n");
		switch(type){
			case 1: ; // Si es una memoria virtual
				MEM_VIR *aux_mv = (MEM_VIR *) malloc(sizeof(MEM_VIR));
				aux_mv = mv;
				printf("Tabla de paginas:\n");
			//	printf("Indice binario  |Indice decimal | Marco de pagina\n");
				while(aux_mv != NULL){
					
					//Imprimo el binario_pagina[]
		            int i = 3;
		            while(i >= 0){
					printf("%i", aux_mv->pagina_binario[i]);
						i--;
					}
					//imprime el valor
		          //  printf("| %d ", aux_mv -> n_pagina); 
					//Imprimo el marco de pagina en donde se encuentra la pagina
					printf("| %d", aux_mv->marco_pagina);
					printf("\n");
		            aux_mv = aux_mv -> sig;
		        }
		        printf("\n");
				break;
			case 2: ; // Si es la tabla
				printf("Tabla de conversiones:\n");
				TABLA *aux_tb = (TABLA *) malloc(sizeof(TABLA));
				aux_tb = tb;
				while(aux_tb != NULL){
		            printf("%d  |", aux_tb -> n_pagina); //imprime el valor
		            //Imprimo el marco_binario[]
		            int i = 2;
		            while(i >= 0){
					printf("%i", aux_tb->marco_binario[i]);
						i--;
					}
		            printf("| %d", aux_tb -> bit_pres_aus); //imprime el valor
		            aux_tb = aux_tb -> sig;
		            printf("\n");
		        }
		        printf("\n");
				break;
			case 3: ;  // Si es la memoria física
				printf("Tabla de marcos de pagina:\n");
				MEMORIA *aux_mm = (MEMORIA *) malloc(sizeof(MEMORIA));
				aux_mm = mm;
				while(aux_mm != NULL){
					//Imprimo el marco_binario[]
		            int i = 2;
		            while(i >= 0){
					printf("%i", aux_mm->marco_binario[i]);
						i--;
					}
					//imprime el valor
		          //  printf("| %d ", aux_mm -> marco_pagina);
		            //Imprimo la pagina que aloja el marco de pagina
					printf("| %d", aux_mm->n_pagina);
					printf("\n");
		            aux_mm = aux_mm -> sig;
		        }
		        printf("\n");
				break;
		} 
}

//Funcion para saber si un numero aleatorio ya ha sido usado
int Num_usado(int num){
	int num_usado[7];
	int i = 0;
	int bandera = 0;
	while(i<7){
		if(i == num_usado[0]){
			bandera++;	//Si regresa 1 ha sido usado
		}
		else{
			bandera = 0;	//Si regresa 0 no ha sido usado
		}
		i++;
	}
}

//Funcion para hacer la paginacion inicial usando numeros aleatorios
void Paginacion_Inicial(){
	int i = 0;
	int num_usado[7];
	while(i<8){
		int indice_mover = num_random();
		int booleano = Num_usado(indice_mover);
		if(booleano == 0){
			
		}
	}
}
