/* Funciones para manipular cada una de las listas y la información entre ellas */
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include "Defs-Memoria-Tabla-Virtual.h"

int n_orden = 0; // Numero para identificar el orden como fueron paginados los marcos

// Funcion para crear un numero aleatorio
int num_random(){
	int x;
	srand(time(NULL));
	x = rand()%8;	//Vamos a generar un numero entre 0 y 7 
	return x;
}

// Funcion paara convertir numero decimal a binario
void dec_bin(int n, int *ptr_arreglo, int tam){
	int n_digitos = tam; // Obtenemos el número de digitos
	int aux[tam];
	
	for(int i=0; i<tam; i++){ // Converitmos a binario
		aux[i] = n%2;
		n = n/2;		
	}
	for(int i=tam-1; i>=0; i--){ // Invertimos los dígitos
		*ptr_arreglo = aux[i];
		ptr_arreglo++;
	}
}

// Funcion para convertir de un numero binario a decimal
int bin_dec(int *ptr_arreglo, int tam){
	int i = 1, decimal = 0, n_digitos = tam; // Obtenemos el tamaño en bytes y dividimos en 2 para obtener n_digitos
	for(int k = 1; k < n_digitos; k++) // Mandamos al final al puntero porque es binario 
		ptr_arreglo++;	
	
	for(int o = 0; o < n_digitos; o++){		
		if(*ptr_arreglo == 1)
			decimal = decimal + i;			
		ptr_arreglo--;		
		i*=2;		
	}
	return decimal;
}

/* Construye el número de nodos para cada lista, en la memoria virtual y tabla son 16 y en la ram son 8. Esto depende 
del tamaño total y el tamaño por nodo, en este caso el tamaño del nodo son 4KB, el nodo indica el índice*/
void construccion(int nodo, int type){
//	printf("Este es el nodo:  %d\n", nodo);
    switch(type){
    	case 1: ; // Si es una memoria virtual
    		MEM_VIR *nuevo_mv = (MEM_VIR *) malloc(sizeof(MEM_VIR));
			if(nodo < 16){				
				nuevo_mv -> ant = mv;
		        nuevo_mv -> sig = NULL;
		        dec_bin(nodo, nuevo_mv -> pagina_binario, 4); // Convertirmos el nodo a binario y lo almacenamos en pagina_binario
		        nuevo_mv -> pagina_decimal = nodo;
				nuevo_mv -> marco_pagina = -1; // Significa que no hay ninguno en RAM 
				
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
		        dec_bin(0, nuevo_tb -> marco_binario, 3); // Escribimos 000 porque no hay ninguno en RAM
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
		        nuevo_mm -> orden = nodo;
		        dec_bin(nodo, nuevo_mm -> marco_binario, 3); // Convertirmos el nodo a binario y lo almacenamos en marco_binario
		        nuevo_mm -> marco_decimal = nodo;
				nuevo_mm -> marco_pagina = -1; // Significa que no hay ninguno en RAM
		        
				if(mm != NULL) mm -> sig = nuevo_mm;
		        mm = nuevo_mm;
		        construccion(nodo+1, type);
		    }
    		break;
	}	    
}

// Reinicia los frentes al primer nodo
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

// Muestra las tablas
void mostrar(int type){
		switch(type){
			case 1: ; // Si es una memoria virtual
				MEM_VIR *aux_mv = (MEM_VIR *) malloc(sizeof(MEM_VIR));
				aux_mv = mv;
				printf("Tabla de paginas:\n");
				printf("Indice binario | Indice decimal | Marco de pagina \n");
				printf("---------------------------------------------------\n");
				while(aux_mv != NULL){
					
					// Imprimo el número de página en binario
		            for(int i=0; i<4; i++)
		            	printf("%i", aux_mv -> pagina_binario[i]);
		            	
					// Imprimo el número de página en decimal
					printf("           | %d", aux_mv -> pagina_decimal);
					
					//Imprimo el marco de pagina en donde se encuentra la pagina					
					if(aux_mv -> pagina_decimal < 10) printf("              | ");
					else printf("             | ");
					if(aux_mv->marco_pagina != -1)
						printf("%d", aux_mv->marco_pagina);
					
					printf("\n");
		            aux_mv = aux_mv -> sig;
		        }
		        printf("\n");
				break;
				
			case 2: ; // Si es la tabla
				printf("Tabla de conversiones:\n");				
				printf("Numero de pagina | Marco de pagina | Bit Presente/Ausente \n");
				printf("-----------------------------------------------------------\n");
				TABLA *aux_tb = (TABLA *) malloc(sizeof(TABLA));
				aux_tb = tb;
				while(aux_tb != NULL){
					
					// Imprimimos el numero de la pagina
		            printf("%d", aux_tb -> n_pagina); 
		            
		            // Imprimo el marco de pagina
		            if(aux_tb -> n_pagina < 10) printf("                | ");
		            else printf("               | ");
					for(int i=0; i<3; i++){
						printf("%d", aux_tb->marco_binario[i]);
					}
		            	
		        	
					// Imprimimos el bit de presente/ausente
		            printf("            | %d", aux_tb -> bit_pres_aus); //imprime el valor
		            
					printf("\n");
					aux_tb = aux_tb -> sig;		            
		        }
		        printf("\n");
				break;
				
			case 3: ;  // Si es la memoria física
				printf("Tabla de marcos de pagina:\n");				
				printf("Indice binario | Indice decimal | Numero de pagina \n");
				printf("----------------------------------------------------\n");
				MEMORIA *aux_mm = (MEMORIA *) malloc(sizeof(MEMORIA));
				aux_mm = mm;
				while(aux_mm != NULL){
					
					//Imprimo el marco_binario[]
					for(int i=0; i<3; i++)
		            	printf("%i", aux_mm -> marco_binario[i]);
		           
		           	// Imprimo el número de página en decimal
					printf("            | %d", aux_mm -> marco_decimal);
					
					//Imprimo el marco de pagina en donde se encuentra la pagina					
					if(aux_mm -> marco_decimal < 10) printf("              | ");
					else printf("             | ");
					
					if(aux_mm -> marco_pagina != -1){
						printf("%d", aux_mm->marco_pagina);
					}
						
						
					printf("\n");
		            aux_mm = aux_mm -> sig;
		        }
		        printf("\n");
				break;
		} 
}

// Funcion para buscar algún espacio libre en la memoria, devuelve el índice en decimales
int solicitar_espacio(){
	int esp_usado[7];
	int mem_llena = 1;
	MEMORIA *aux_mm = (MEMORIA *) malloc(sizeof(MEMORIA));
	aux_mm = mm;
	
	for(int i=0; i<8; i++){ // Algoritmo para ver si están vacíos u ocupados los espacios en memoria
		if(aux_mm -> marco_pagina == -1)
			esp_usado[i] = 0;
		else
			esp_usado[i] = 1;	
		aux_mm = aux_mm -> sig;	
	}
	free(aux_mm);
	
	for(int i=0; i<8; i++){ // Comprobamos que no toda la memoria esté llena
		if(esp_usado[i] == 0)
			mem_llena = 0;
		//printf("%d", esp_usado[i]);	
	}
	if(mem_llena)
		return -1;	
		
	while(1){ // Si no esta llena, buscamos un espacio de forma aleatoria que este vacio
		int indice = num_random();
		if(esp_usado[indice] == 0)
			return indice;
	}
		
}


//Funcion para hacer la paginacion inicial usando numeros aleatorios
void paginar(int n_pagina){
	int indice_espacio = solicitar_espacio();
	MEM_VIR *aux_mv = (MEM_VIR *) malloc(sizeof(MEM_VIR)); // Generamos el apuntador para manejar la página
	aux_mv = mv;
	
	for(int i=0; i<16; i++){ // Buscamos la pagina (MV) con base a su numero 
		if(aux_mv -> pagina_decimal == n_pagina)
			break;
		aux_mv = aux_mv -> sig;		
	}
	
	if(indice_espacio > -1){ // Si hay espacio
		MEMORIA *aux_mm = (MEMORIA *) malloc(sizeof(MEMORIA)); // Generamos el apuntador para manejar el marco de página
		aux_mm = mm;
		
		for(int i=0; i<8; i++){ // Buscamos el marco de pagina (MM) con base a su numero 
			if(aux_mm -> marco_decimal == indice_espacio)
				break;
			aux_mm = aux_mm -> sig;		
		}
		aux_mm -> marco_pagina = n_pagina; // Asignamos el numero de pagina a la memoria
		aux_mv -> marco_pagina = indice_espacio; // Asignamos el marco de pagina a la memoria virtual
		aux_mm -> orden = n_orden; // Asignamos el orden como legó para usar FIFO
		n_orden++;
		
		// Manejo de la tabla de conversiones
		TABLA *aux_tb = (TABLA *) malloc(sizeof(TABLA)); // Generamos el apuntador para manejar el marco de página
		aux_tb = tb;
		
		for(int i=0; i<16; i++){ // Buscamos el índice de pagina en la tabla con base al numero de pagina
			if(aux_tb -> n_pagina == n_pagina)
				break;
			aux_tb = aux_tb -> sig;		
		}
		aux_tb -> bit_pres_aus = 1; // Asignamos el bit de ausente/presente
		dec_bin(indice_espacio, aux_tb -> marco_binario, 3); // Convertimos el indice de espacio a binario y lo almacenamos
		
		// Impresion de las conversiones
		int aux[12];
		printf(" Direcciones vituales | Direcciones en RAM\n");
		printf("----------------------------------------------\n");
		for(int i=0; i<4096; i++){
			dec_bin(i, aux, 12);
			
			// Seccion de direcciones virtuales
			printf(" ");
			for(int i=0; i<4; i++){
				printf("%d", aux_mv -> pagina_binario[i]); // Imprime primeros 4 bits (de MV)
			}
			printf(" ");
			
			for(int i=0; i<4; i++){ // Los siguientes 4 bits generados del for
				printf("%d", aux[i]);
			}
			printf(" ");
			
			for(int i=4; i<8; i++){ // Los siguientes 4 bits generados del for
				printf("%d", aux[i]);
			}
			printf(" ");
			
			for(int i=8; i<12; i++){ // Los siguientes 4 bits generados del for
				printf("%d", aux[i]);
			}
			printf("  | ");
			
			// Seccion de direcciones en RAM
			printf(" ");
			for(int i=0; i<3; i++){
				printf("%d", aux_tb -> marco_binario[i]); // Imprime primeros 3 bits (de MM)
			}
			printf("%d", aux_tb -> bit_pres_aus); // Imprime el siguiente bit (de MM, bit ausente/presente)
			printf(" ");
			
			for(int i=0; i<4; i++){ // Los siguientes 4 bits generados del for
				printf("%d", aux[i]);
			}
			printf(" ");
			
			for(int i=4; i<8; i++){ // Los siguientes 4 bits generados del for
				printf("%d", aux[i]);
			}
			printf(" ");
			
			for(int i=8; i<12; i++){ // Los siguientes 4 bits generados del for
				printf("%d", aux[i]);
			}
			printf("  | \n");
		}
		printf("\n");		
		
	}
	else{ // Si no hay espacio
		/* Algoritmo de fallo de página */
	}
}
