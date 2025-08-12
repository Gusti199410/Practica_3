#include"merge.h"
#define producto "producto.bin"
#define prod_del_dia "prod_dia.bin"
#define temporal "temp.bin"

int main()
{
    printf("\nHOLA NUEVAS PRACTICAS\n");
    tVector vec;
    tVector vec_b;
    tProducto prod[]={{1,"torre de marfil",15},
                      {2,"Entre canibales",16},
                      {4,"Cactus ",15},
                      {7,"Zona de promesas",16},
                      {3,"Crimen",15},
                      {6,"Adios",16},
                      {15,"Bocanada",15},
                      {11,"Beatifoul",16},
                      {12,"La excepcion",16}
                      };

    tMovimiento prod_b[]={{5,"Amor amarillo",19},
                      {8,"Profugos",20},
                      {4,"Cactus",15},
                      {7,"Zona de promesas",16},
                      {3,"Crimen",15},
                      {6,"Adios",16},
                      {15,"Bocanada",15},
                      {9,"Ahora es nunca",16},
                      {10,"sudestada",3}
                      };
    size_t tam_Prod=sizeof(tProducto);
    size_t ce_prod=sizeof(prod)/sizeof(tProducto);
    size_t ce_b=sizeof(prod_b)/sizeof(tMovimiento);

    ///creo el primer vector con memoria
    if(!crear_Vector(&vec,5,tam_Prod))
    {
        printf("Error al crear memoria");
        return 0;
    }
    ///creo el segundo vector con memoria
    if(!crear_Vector(&vec_b,5,tam_Prod))
    {
        printf("Error al crear memoria");
        return 0;
    }
    if(!cargar_en_Memoria(&vec,&prod,ce_prod))
    {
        printf("Error al crear memoria");
        return 0;
    }
     if(!cargar_en_Memoria(&vec_b,&prod_b,ce_b))
    {
        printf("Error al crear memoria");
        return 0;
    }

    ordenar_Elementos(&vec);

    ordenar_Elementos(&vec_b);

    cargar_en_Archivo(producto,&vec);

    cargar_en_Archivo(prod_del_dia,&vec_b);

    mostrar_Elemento_Archivo(producto);

    printf("\n***********************************************\n");

    mostrar_Elemento_Archivo(prod_del_dia);

    printf("\n*****************************************************\n");

    if(!funcion_Merge(producto,prod_del_dia,temporal))
    {
        printf("Error al abrir archivo_merge");
        return 0;
    }

    mostrar_Elemento_Archivo(producto);

    return 0;
}
