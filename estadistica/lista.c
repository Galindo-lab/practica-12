/* 4. Elaborar un programa que lea de un archivo de texto con una serie de */
/* números reales en forma de lista, al leer cada número se debe guardar en un */
/* arreglo de tamaño dinámico, una vez terminado de leer el archivo, imprimir el */
/* arreglo creado, el valor máximo, mínimo, media, mediana y moda. */

/* a. Hacer uso de arreglos de apuntadores a función. */

/* b. Las funciones deberán contener el siguiente prototipo. */
/*    float funcion(float* array, int size); */

/* c. El programa debe de ejecutar de forma iterativa el arreglo de */
/*    apuntadores a funciones, apoyarse en el código de ejemplo. */

/* d. La función para ordenar elementos de un arreglo es libre, se */
/*    recomienda consultar la función qsort de stdlib.h. */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "array.c"
#include "tools.c"

float suma(Array*);
float media(Array*);
float maximo(Array*);
float minimo(Array*);
float mediana(Array*);
float moda(Array*);

int filter(const void *a, const void *b);
void ordenar( float datos[], int n );

float(*op[])(Array*) = {
     moda,
     media,
     maximo,
     minimo,
     suma,
     mediana
};

char funciones[][20] = {
    "moda     ",
    "media    ",
    "maximo   ",
    "minimo   ",
    "sumatoria",
    "mediana  "
};

int main(int argc, char *argv[])
{
    if(argc > 1){
        Array data = {0};
        initArray(&data,2);

        read_data(argv[1], &data);

        /* for(int i = 0 ; i < data.used ; i++) */
        /* { */
        /*     printf("%f \n", data.array[i]); */
        /* } */

        for(int i = 0; i < 6; i++){
            printf(" %s : %.2f\n", funciones[i],op[i](&data));
        }

        freeArray(&data);
    }

    return 0;
}

int filter(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

float maximo( Array *a )
{
    int n = a->used;
    qsort(a->array, a->used, sizeof(float), &filter);
    return a->array[n-1];
}

float minimo( Array *a )
{
    int n = a->used;
    qsort(a->array, a->used, sizeof(float), &filter);
    return a->array[0];
}

float suma(Array *a) /* sumatoria */
{
    float s = 0;
    for(int i = 0; i < a->used ; i++){
        s = a->array[i];
    }
    return s;
}

float media(Array *a)
{
    float sumatoria = suma(a);
    float media = sumatoria / a->used;
    return media;
}

float mediana(Array *a)
{
    qsort(a->array, a->used, sizeof(float), &filter);
    return a->array[a->used/2];
}

float moda(Array *a)
{
    float
        a_ctrl = 0,
        a_frec = 0;

    float
        b_ctrl = 0,
        b_frec = 0;

    int n = a->used;

    for(int i = 0;i<n;i++)
    {
        a_frec = 0;             /* recorre todos los elemntos */
        a_ctrl = a->array[i];

        for(int j = 0;j<n;j++)  /* suma 1 cada vez que se
                                 * repite */
        {
            if(a->array[j] == a_ctrl)
            {
                a_frec++;
            }
        }

        if(a_frec > b_frec)     /* sí la frecuencia es mayor
                                 * se remplaza */
        {
            b_ctrl = a_ctrl;
            b_frec = a_frec;
        }
    }

    return b_ctrl;
}
