/* Programa principal que hará uso de las funciones para manipular la información entre la memoria
virtual y la memoria RAM */
#include <stdio.h>
#include <stdlib.h>
# include "Defs-Memoria-Tabla-Virtual.h"
# include "FuncionesParaRecursos.c"

int main(void){
	// Incia bloque de construccion de las listas
	construccion(0, memoria_virtual);
	construccion(0, ram);
	construccion(0, tabla_con);
	
	inicio(memoria_virtual);
	inicio(ram);
	inicio(tabla_con); // Finaliza bloque de construccion de las listas
	
	mostrar(memoria_virtual);
	mostrar(ram);
	mostrar(tabla_con);
}
