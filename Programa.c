/* Programa principal que hará uso de las funciones para manipular la información entre la memoria
virtual y la memoria RAM */
#include <stdio.h>
#include <stdlib.h>
# include "Defs-Memoria-Tabla-Virtual.h"
# include "FuncionesParaRecursos.c"

int main(void){
	// Construccion de las listas
	construccion(0, memoria_virtual);
	construccion(0, ram);
	construccion(0, tabla_con);
	
	// Retroceso de los apuntadores
	inicio(memoria_virtual);
	inicio(ram);
	inicio(tabla_con); 
	
	//system("pause");
	//system("cls");
	int opcion = -1;
	do{
		//system("cls");
		// Muestra estado inicial de las memorias
		mostrar(memoria_virtual);
		mostrar(ram);
		mostrar(tabla_con);
		
		printf("\nQue pagina desea mover a la memoria RAM? (0-15, -2 para hacer fallo de pagina, -1 para salir) ");
		scanf("%d", &opcion);
		printf("\n");
		if(opcion == -2){
		//	printf("Aqui va a ser el fallo de pagina\n");
			int n_pagina = num_random2();
			fallo_pagina(n_pagina);
		}
		else if(opcion != -1){
			paginar(opcion);
		}		
		
	}while(opcion != -1);
}
