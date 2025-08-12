#ifndef MERGE_H_INCLUDED
#define MERGE_H_INCLUDED
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define max_nom 30
#include <stdbool.h>

typedef struct
{
    int id;
    char nombre[max_nom];
    int stock;

}tProducto;

typedef struct
{
    int id;
    char nombre[max_nom];
    int stock;

}tMovimiento;

typedef struct
{
    void *vec;
    size_t tamanio;
    size_t ce;
    size_t tam_Elemento;

}tVector;

bool crear_Vector(tVector *vec,size_t tamanio,size_t tam_Elemento);
bool asignar_Memoria(tVector *vec);
bool liberar_Memoria(tVector *vec);
bool asignar_Dato(tVector *vec, void *dato);
void mostrar_Elemento_Memoria(tVector *vec);




#endif // MERGE_H_INCLUDED
