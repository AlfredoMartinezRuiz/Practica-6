/* Funciones para manipular cada una de las listas y la información entre ellas */
# include <stdio.h>
# include <stdlib.h>
# include "Defs-Memoria-Tabla-Virtual.h"

void construccion(int nodo, int type){
//	printf("Este es el nodo:  %d\n", nodo);
    switch(type){
    	case 1: ; // Si es una memoria virtual
    		MEM_VIR *nuevo_mv = (MEM_VIR *) malloc(sizeof(MEM_VIR));
			if(nodo < 16){				
				nuevo_mv -> ant = mv;
		        nuevo_mv -> sig = NULL;
		        nuevo_mv -> n_pagina = nodo;
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
		        nuevo_tb -> bits = 0000;
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
				printf("Indice binario  |Indice decimal | Marco de pagina\n");
				while(aux_mv != NULL){
					
					//Imprimo el binario_pagina[]
		            int i = 3;
		            while(i >= 0){
					printf("%i", aux_mv->pagina_binario[i]);
						i--;
					}
					//imprime el valor
		            printf("| %d |", aux_mv -> n_pagina); 
					//Imprimo el marco de pagina en donde se encuentra la pagina
					printf("%d", aux_mv->marco_pagina);
					printf("\n");
		            aux_mv = aux_mv -> sig;
		        }
				break;
			case 2: ; // Si es la tabla
				TABLA *aux_tb = (TABLA *) malloc(sizeof(TABLA));
				aux_tb = tb;
				while(aux_tb != NULL){
		            printf("%d  ", aux_tb -> n_pagina); //imprime el valor
		            aux_tb = aux_tb -> sig;
		        }
				break;
			case 3: ;  // Si es la memoria física
				MEMORIA *aux_mm = (MEMORIA *) malloc(sizeof(MEMORIA));
				aux_mm = mm;
				while(aux_mm != NULL){
		            printf("%d  ", aux_mm -> marco_pagina); //imprime el valor
		            aux_mm = aux_mm -> sig;
		        }
				break;
		} 
}
