/* Funciones para manipular cada una de las listas y la información entre ellas */
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include "Defs-Memoria-Tabla-Virtual.h"

int n_orden = 0; // Numero para identificar el orden como fueron paginados los marcos


// Funcion para crear un numero aleatorio entre 0 y 7 
int num_random(){
	int x;
	srand(time(NULL));
	x = rand()%8;	//Vamos a generar un numero entre 0 y 7 
	return x;
}

// Funcion para crear un numero aleatorio entre 0 y 15
int num_random_extendido(){
	int x;
	srand(time(NULL));
	x = rand()%16;	//Vamos a generar un numero entre 0 y 15
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

/* Construye el número de nodos para cada lista, en la memoria virtual y tabla son 16 y en la ram son 8. Esto depende 
del tamaño total y el tamaño por nodo, en este caso el tamaño del nodo son 4KB, el nodo indica el índice*/
void construccion(int nodo, int type){
    switch(type){
    	case 1: ; // Si es una memoria virtual
    		MEM_VIR *nuevo_mv = (MEM_VIR *) malloc(sizeof(MEM_VIR));
			if(nodo < 16){		
				nuevo_mv -> ant = mv;
		        nuevo_mv -> sig = NULL;
		        dec_bin(nodo, nuevo_mv -> pagina_binario, 4); /* Convertirmos el nodo
				 a binario y lo almacenamos en pagina_binario */
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
		        dec_bin(nodo, nuevo_mm -> marco_binario, 3); /* Convertirmos el nodo a binario y 
				lo almacenamos en marco_binario*/
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
	printf("El numero de pagina a meter en RAM es %d\n", n_pagina);
	int indice_espacio = solicitar_espacio();
	
	// Para la memoria virtual
	MEM_VIR *aux_mv = (MEM_VIR *) malloc(sizeof(MEM_VIR)); // Generamos el apuntador para manejar la página
	aux_mv = mv;
	
	for(int i=0; i<16; i++){ // Buscamos la pagina (MV) con base a su numero 
		if(aux_mv -> pagina_decimal == n_pagina)
			break;
		aux_mv = aux_mv -> sig;		
	}
	
	// Para la tabla de conversiones
	TABLA *aux_tb = (TABLA *) malloc(sizeof(TABLA)); // Generamos el apuntador para manejar el marco de página
	aux_tb = tb;
		
	for(int i=0; i<16; i++){ // Buscamos el índice de pagina en la tabla con base al numero de pagina
		if(aux_tb -> n_pagina == n_pagina)
			break;
		aux_tb = aux_tb -> sig;		
	}
	
	if(aux_tb -> bit_pres_aus == 0){ // Si la pagina no esta en la RAM, procedemos a mover
		
		// Si hay espacio en la RAM
		if(indice_espacio > -1){ 
			MEMORIA *aux_mm = (MEMORIA *) malloc(sizeof(MEMORIA)); // Generamos el apuntador para manejar el marco de página
			aux_mm = mm;
			
			for(int i=0; i<8; i++){ // Buscamos el marco de pagina (MM) con base a su numero 
				if(aux_mm -> marco_decimal == indice_espacio)
					break;
				aux_mm = aux_mm -> sig;		
			}
			aux_mm -> marco_pagina = n_pagina; // Asignamos el numero de pagina a la memoria
			aux_mv -> marco_pagina = indice_espacio; // Asignamos el marco de pagina a la memoria virtual
			aux_mm -> orden = n_orden; // Asignamos el orden como llegó para usar FIFO
			n_orden++;
			
			// Manejo de la tabla de conversiones
			
			aux_tb -> bit_pres_aus = 1; // Asignamos el bit de ausente/presente
			dec_bin(indice_espacio, aux_tb -> marco_binario, 3); // Convertimos el indice de espacio a binario y lo almacenamos
			
			// Impresion de las conversiones
			
			int aux[12];
			printf(" Direcciones virtuales | Direcciones en RAM\n");
			printf("----------------------------------------------\n");
			for(int i=0; i<4096; i++){ // Generación de todos los números
				dec_bin(i, aux, 12); // Conversión a binario
				
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
		
		// Si no hay espacio
		else{ 
			printf("La RAM esta llena...\n");
			/* Algoritmo de fallo de página */
			fallo_pagina(n_pagina, aux_tb, aux_mv);
		}
	}
	
	else			// Si la pagina si esta en la RAM mandamos el mensaje al usuario
		printf("La pagina esta en la RAM, intente con otra pagina\n\n");
	
}


void fallo_pagina(int n_pagina, TABLA *aux_tb, MEM_VIR *aux_mv){
	
		// Ahora, determinar la pagina que debe salir de la tabla de marco de pagina, mediante FIFO
		MEMORIA *aux_mm = (MEMORIA *) malloc(sizeof(MEMORIA)); // Generamos el apuntador para manejar el marco de pagina a salir
		aux_mm = mm;
		
		//Vamos a buscar el marco de pagina cuyo orden = 0
		for(int i=0; i<8; i++){
			if(aux_mm -> orden == 0) //Si el numero orden del marco de pagina es 0, este es el que sacaremos
				break;				
			else //Si el numero orden del marco de pagina no es 0, avanzamos
				aux_mm = aux_mm->sig;				
		}
				
		
		int sale_pag = aux_mm -> marco_pagina; // Esto nos sirvira mas adelante para actualizar datos en la tabla de conversiones
		printf("Pagina a salir de RAM: %d\n", aux_mm -> marco_pagina); //Pagina encontrada en la tabla de marcos de pagina
		
		//Ahora, hacer el cambio (paginación)
		//	aux_mm es la pagina que debe salir
		// aux_mv es la pagina que debe entrar
		
		aux_mm -> marco_pagina = aux_mv -> pagina_decimal; //Sobreescribo la pagina en la tabla marco de pagina
		aux_mv -> marco_pagina = aux_mm -> marco_decimal;	//En la tabla de paginas, le digo que la pagina que entra esta en el marco de pagina que acaba de salir

		
		//Le resto a orden -1 a todos los marcos de pagina menos al que es el menor
		MEMORIA *aux_mm_restar = (MEMORIA *) malloc(sizeof(MEMORIA)); // Generamos el apuntador para manejar el marco de pagina a salir
		aux_mm_restar = mm;
		while(aux_mm_restar != NULL){
			if(aux_mm_restar -> orden != 0){//Si el numero orden del marco de pagina es distinto de 0, le restamos 1
				aux_mm_restar -> orden--;
				aux_mm_restar = aux_mm_restar->sig;
			}
			else
				aux_mm_restar = aux_mm_restar->sig;			
		}
				
		aux_mm -> orden = 7; //Como la pagina que tenía el marco de pagina cambio, este es el que acaba de entrar, por eso orden = 7
		
		
		// Hallar la pagina en la tabla de conversiones que ya no esta en la tabla de marcos de pagina
		TABLA *sal_tb = (TABLA *) malloc(sizeof(TABLA)); // Generamos el apuntador para manejar la tabla 
		sal_tb = tb; //Vuelvo al inicio
		for(int i=0; i<16; i++){ // Buscamos el índice de pagina en la tabla con base al numero de pagina de la tabla de marcos de pagina
			if(sal_tb -> n_pagina == sale_pag)
				break;			
			else
				sal_tb = sal_tb -> sig;			
		}
		
		//Hallar la pagina en la tabla de conversiones que entra para actualizar sus datos
		TABLA *ent_tb = (TABLA *) malloc(sizeof(TABLA)); // Generamos el apuntador para manejar la tabla 
		ent_tb = tb; //Vuelvo al inicio
		for(int i=0; i<16; i++){ // Buscamos el índice de pagina en la tabla con base al numero de pagina de la tabla de marcos de pagina
			if(ent_tb -> n_pagina == n_pagina)
				break;			
			else
				ent_tb = ent_tb -> sig;			
		}
		
		//A la pagina que entra le pasamos el binario de la que sale
		for(int i=0;i<3;i++)
			ent_tb -> marco_binario[i] = sal_tb -> marco_binario[i];		
		ent_tb -> bit_pres_aus = 1;
		
		
		//A la pagina que ya no esta lo actualizamos
		for(int i=0; i<3; i++)
			sal_tb -> marco_binario[i] = 0;		
		sal_tb -> bit_pres_aus = 0;
		

		//Hallar la pagina en la tabla de paginas que ya no esta en la tabla de marcos de pagina
		MEM_VIR *sal_mv = (MEM_VIR *) malloc(sizeof(MEM_VIR)); // Generamos el apuntador para manejar la página
		sal_mv = mv; //Vuelvo al inicio 
		for(int i=0; i<16; i++){ // Buscamos la pagina (MV) con base a la pagina que determinamos de la tabla de conversiones
			if(sal_mv -> pagina_decimal == sale_pag)
				break;			
			else
				sal_mv = sal_mv -> sig;			
		}
		sal_mv -> marco_pagina = -1; 
		
		
		// Impresion de las conversiones
		
		int aux[12];
		printf(" Direcciones vituales | Direcciones en RAM\n");
		printf("----------------------------------------------\n");
		for(int i=0; i<4096; i++){ // Generación de todos los números
			dec_bin(i, aux, 12); // Conversión a binario
			
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
