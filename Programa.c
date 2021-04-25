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
	
	int opcion = -1;
	printf("Estado inicial: \n\n");
	do{
		// Muestra estado inicial de las memorias
		mostrar(memoria_virtual);
		mostrar(ram);
		mostrar(tabla_con);
		printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
		printf("\nBienvenido, digite lo que desea hacer:\n\n");
		printf("Si quiere hacer paginacion manual, digite la pagina que desea mover a la RAM (0-15)\n");
		printf("Si quiere paginar alguna pagina aleatoriamente, digite -2\n");
		printf("Si quiere salir del programa, digite -1\n");;
		printf("Opcion: ");		
		scanf("%d", &opcion);		
		printf("\n");
		
		if(opcion == -2){
			opcion = num_random_extendido();
			paginar(opcion);
		}
		else if(opcion != -1){
			paginar(opcion);
		}	
		
	}while(opcion != -1);
}
