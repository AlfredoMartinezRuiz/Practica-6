/* Programa principal que hará uso de las funciones para manipular la información entre la memoria
virtual y la memoria RAM */
#include <stdio.h>
#include <stdlib.h>
# include "Defs-Memoria-Tabla-Virtual.h"
# include "FuncionesParaRecursos.c"

int main(void){
	// Incia bloque de construccion de las listas
	construccion(0, memoria_virtual);
	construccion(0, tabla_con);
	construccion(0, ram);
	
	inicio(memoria_virtual);
	inicio(tabla_con);
	inicio(ram); // Finaliza bloque de construccion de las listas
	 
	
	mostrar(memoria_virtual);
//	mostrar(tabla_con);
//	mostrar(ram);
}
