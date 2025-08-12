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
void procesar_Nuevo_Ingreso(tMovimiento *mov,FILE *arcMov,FILE *arcTMP);
bool cargar_en_Memoria(tVector *vec, tProducto *prod, size_t ce);
bool cargar_en_Memoria_mov(tVector *vec, tMovimiento *mov, size_t ce);
bool ordenar_Elementos(tVector *vec);
bool cargar_en_Archivo(const char *archivo,tVector *vec);
bool funcion_Merge(const char*archivo_uno,const char *archivo_dos,const char *temporal);
void mostrar_Elemento_Archivo(const char *archivo);

#endif // MERGE_H_INCLUDED
