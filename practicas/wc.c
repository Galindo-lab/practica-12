/* 3. Elaborar un programa (wc.c) que lea un archivo de texto y cuente el número */
/* de caracteres, palabras y líneas de texto según sea indicado con parámetros */
/* por consola. Posibles opciones que se pueden establecer por consola: */
/* a. -l : Cuenta las líneas de texto que tiene el archivo.       */
/* b. -c : Cuenta los caracteres que contiene un archivo de texto */
/* c. -w : Cuenta las palabras que contiene un archivo de texto.  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int uint32_t;

void wc(char*, uint32_t*, uint32_t*, uint32_t*);
int valid_params(int, char *argv[]);
int file_exists(const char*);
void error_message();

int main(int argc, char *argv[])
{
    uint32_t lines = 0, words = 0, chars = 0;

    if( valid_params(argc,argv) )
    {
        wc(argv[2],&lines, &words, &chars);
        if(strcmp(argv[1], "-l") == 0)
        {
            printf("lines: %d\n", lines);
        }

        if(strcmp(argv[1], "-c") == 0)
        {
            printf("chars: %d\n", chars);
        }

        if(strcmp(argv[1], "-w") == 0)
        {
             printf("words: %d\n", words);
        }
    }
    return 0;
}

int valid_params(int argc, char *argv[])
{
    /* -l : Cuenta las líneas de texto que tiene el archivo.       */
    /* -c : Cuenta los caracteres que contiene un archivo de texto */
    /* -w : Cuenta las palabras que contiene un archivo de texto.  */

    if(argc > 2)
    {
        if(strcmp(argv[1], "-l") == 1
           && strcmp(argv[1], "-c") == 1
           && strcmp(argv[1], "-w") == 1)
        {
            error_message();
            return 0;
        }

        if(file_exists(argv[2]) == 0)
        {
            printf("No existe ese archivo\n");
            return 0;
        }
    }

    return 1;
}

void error_message()
{
    printf("no existe esa opcion:\n");
    printf("-l : Cuenta las líneas de texto que tiene el archivo.\n");
    printf("-c : Cuenta los caracteres que contiene un archivo de texto\n");
    printf("-w : Cuenta las palabras que contiene un archivo de texto.\n");
}

/* https://www.zentut.com/c-tutorial/c-file-exists/ */
int file_exists(const char *filename){ /* preguntar por el puntero constante */
    /* try to open file to read */
    FILE *file = fopen(filename, "r") ;
    if(file){
        fclose(file);
        return 1;
    }
    return 0;
}

void wc(char *filename, uint32_t *lines, uint32_t *words, uint32_t *chars)
{
    char ch;
    FILE *fp = fopen(filename, "r");

    while((ch = fgetc(fp)) != EOF)
    {
       switch (ch) {
           case ' ':            /* cuenta palabras */
               (*words)++;
               break;
           case '\n':           /* cuenta lineas */
               (*lines)++;
               break;
           default:             /* cuenta los caracteres */
               (*chars)++;
       }
    }

    fclose(fp);
}
