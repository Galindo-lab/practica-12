
#include <stdlib.h>
#include <stdio.h>

/*
** Este código no es mio es una solucion de stackoverflow, pero perdí el
** enlace, sin embargo me parecio una solucion muy practica para evitar
** repetir código, ademas que permite utilizar la memoria de manera mas
** eficiente.
 */

typedef struct {
     float *array;                /* direccionde puntero */
     int used;                  /* posisciones usadas */
     int size;                  /* tamaño de la memoria reservada*/
} Array ;

void initArray(Array *a, int initialSize) /* inicialiar el arraglo,
                                           * no hay mucho misterio */
{
     a->array = (float*) malloc( initialSize * sizeof(float) );
     a->used = 0;
     a->size = initialSize;
}

void insertArray(Array *a, float element)
{
     if(a->used == a->size)     /* cuando reservamos memoria no se usa toda
                                 * al mismo tiempo, pero para evitar
                                 * reservar memoria incesesaria revisamos
                                 * si lo elementos en el array han sido
                                 * utilizados */
     {
          a->size *= 2;
          a->array = realloc( a->array, a->size * sizeof(float) );
     }

     a->array[a->used++] = element;
}

void freeArray(Array *a)        /* libera el array */
{
     free(a->array);            /* libera la memoria */
     a->array = NULL;           /* el puntero se le indica que deje de
                                 * señalar esa pocicion de memoria*/
     a->used = a->size = 0;     /* se cambia el tamaño a 0 y la memoria
                                 * usada a 0*/
}
