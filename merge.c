#include"merge.h"



bool crear_Vector(tVector *vec,size_t tamanio,size_t tam_Elemento)
{
    vec->vec=malloc(tamanio*tam_Elemento);
    if(!vec->vec)
    {
        printf("Error al asignar memoria");
        return false;
    }
    vec->ce=0;
    vec->tamanio=tamanio;
    vec->tam_Elemento=tam_Elemento;
    return true;
}
bool asignar_Memoria(tVector *vec)
{
    size_t nuevo_Tam=vec->tamanio*2;
    void *auxiliar=realloc(vec->vec,nuevo_Tam*vec->tam_Elemento);
    if(!auxiliar)
    {
        printf("No se pudo agregar memoria");
        return false;
    }
    vec->vec=auxiliar;
    vec->tamanio=nuevo_Tam;
    return true;
}
bool liberar_Memoria(tVector *vec)
{
    free(vec->vec);
    vec->vec=NULL;
    vec->tamanio=0;
    vec->tam_Elemento=0;
    vec->ce=0;
    return true;
}
bool asignar_Dato(tVector *vec, void *dato)
{
    if(vec->ce >= vec->tamanio)
    {
        if(!asignar_Memoria(vec))
        {
            printf("Error al asignar memoria");
            return false;
        }
    }
    void *destino=(char*)vec->vec+(vec->ce*vec->tam_Elemento);
    memcpy(destino,dato,vec->tam_Elemento);
    vec->ce++;
    return true;
}
void mostrar_Elemento_Memoria(tVector *vec)
{
    tProducto *inicio=vec->vec;
    tProducto *fin = inicio+ vec->ce-1;
    for(tProducto *i=inicio; i<=fin ;i++)
    {
        printf("ID: %d\n",i->id);
        printf("NOMBRE: %s\n",i->nombre);
        printf("VECES ESCUCHADO: %d",i->stock);
        printf("\n------------------------------\n");
    }

}

bool ordenar_Elementos(tVector *vec)
{
    tProducto *inicio = (tProducto*)vec->vec;
    tProducto *fin = inicio + vec->ce;
    tProducto temp;

    for (tProducto *temaA = inicio; temaA < fin - 1; temaA++)
    {
        for (tProducto *temaB = temaA + 1; temaB < fin; temaB++)
        {
            if (temaA->id > temaB->id)
            {
                 temp  = *temaA;
                *temaA = *temaB;
                *temaB =temp;
            }
        }
    }
    return true;
}
bool cargar_en_Archivo(const char *archivo,tVector *vec)
{
    FILE *fp=fopen(archivo,"wb");
    if(!fp)
    {
        printf("Error al abrir el archivo");
        return false;
    }
    tProducto *inicio=vec->vec;
    tProducto *fin=inicio+vec->ce;

    for(tProducto *temaA=inicio; temaA<fin;temaA++)
    {
        fwrite(temaA,sizeof(tProducto),1,fp);
    }
    fclose(fp);
    liberar_Memoria(vec);
    return true;

}

void mostrar_Elemento_Archivo(const char *archivo)
{
    FILE *fp=fopen(archivo,"rb");
    if(!fp)
    {
        printf("Error al abrir archivo");
        exit(1);
    }
    tProducto elemento;
    while(fread(&elemento,sizeof(tProducto),1,fp)==1)
    {
        printf("ID: %d\n",elemento.id);
        printf("NOMBRE: %s\n",elemento.nombre);
        printf("VECES ESCUCHADO: %d",elemento.stock);
        printf("\n------------------------------\n");

    }
    fclose(fp);
}
bool cargar_en_Memoria(tVector *vec,tProducto *prod,size_t ce)
{

    for(size_t i=0;i<ce;i++)
    {
        if(!asignar_Dato(vec,&prod[i]))
    {
        printf("Error al asignar dato");
        return 0;
    }
    }
    return true;
}

bool funcion_Merge(const char *archivo_uno,const char *archivo_dos,const char *temporal)
{
    FILE *fa=fopen(archivo_uno,"rb");
    if(!fa)
    {
        printf("Error al abrir archivo");
        return false;
    }
    FILE *fb=fopen(archivo_dos,"rb");
    if(!fb)
    {
        printf("Error al abrir archivo 2");
        fclose(fa);
        return false;
    }

    FILE *tmp=fopen(temporal,"wb");
    if(!tmp)
    {
        printf("Error al abrir archivo escritura");
        fclose(fa);
        fclose(fb);
        return false;
    }
    tProducto prod;
    tMovimiento mov;
    fread(&prod,sizeof(tProducto),1,fa);
    fread(&mov,sizeof(tMovimiento),1,fb);
    while(!feof(fa) && !feof(fb))
    {
        if(prod.id==mov.id)
        {
            prod.stock+=mov.stock;
            fread(&mov,sizeof(tMovimiento),1,fb);

        }
        if(prod.id<mov.id)
        {
            fwrite(&prod,sizeof(tProducto),1,tmp);
            fread (&prod,sizeof(tProducto),1,fa);
        }
        if(prod.id>mov.id)
        {
            procesar_Nuevo_Ingreso(&mov,fb,tmp);
        }
    }
    while(!feof(fa))
    {
        fwrite(&prod,sizeof(tProducto),1,tmp);
        fread(&prod,sizeof(tProducto),1,fa);
    }
    while(!feof(fb))
    {
        tProducto nuevo;
        procesar_Nuevo_Ingreso(&mov,fb,tmp);
        fwrite(&nuevo,sizeof(tProducto),1,tmp);
        fread(&mov,sizeof(tMovimiento),1,fb);
    }

    fclose(fa);
    fclose(fb);
    fclose(tmp);
    remove(archivo_uno);
    rename(temporal,archivo_uno);
    return true;

}
void procesar_Nuevo_Ingreso(tMovimiento *mov,FILE *archMov,FILE *arcTMP)
{
    tProducto nuevo;
    nuevo.id=mov->id;
    strcpy(nuevo.nombre,mov->nombre);
    nuevo.stock=mov->stock;

    ///leer el siguiente movimiento

    fread(mov,sizeof(tMovimiento),1,archMov);
    while(!feof(archMov) && nuevo.id==mov->id)
    {
        ///acumular la cantidad de stock
        nuevo.stock+=mov->stock;
        fread(mov,sizeof(tProducto),1,archMov);
    }
    ///ESCRIBIR EL NUEVO PRODUCTO

    fwrite(&nuevo,sizeof(tProducto),1,arcTMP);


}
