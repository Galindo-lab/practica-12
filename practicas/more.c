/* Implementar un programa (more.c) para leer un archivo de texto e imprimir */
/* su contenido en la consola. Si el archivo cuenta con más de 15 líneas de */
/* texto, se deberá realizar una pausa en la lectura hasta que el usuario */
/* presione enter y se muestran las siguientes 10 líneas si las tiene. */

#include <stdio.h>
#include <stdlib.h>

#define LINE_WIDTH 82
#define VISIBLE_LINES 15

typedef char uint8_t;

void display_more(FILE*);

int main(int argc, char *argv[])
{
    FILE *fp;

    if(argc >  1)
    {
        fp = fopen(argv[1], "r");
    }

    if (fp == NULL)
    {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        display_more(fp);
    }


    fclose(fp);

    return 0;
}


void display_more(FILE *fp)
{
    char ch;
    uint8_t
        char_count = 0,
        lines_count = 0;

    while((ch = fgetc(fp)) != EOF)
    {
        if(char_count < LINE_WIDTH) {
            /* imprimir caracter */
            printf("%c", ch);
            char_count++;
        }
        else if (char_count == LINE_WIDTH) {
            /* romper linea si es mayor a el tamañao de la terminal */
            printf("\n");
            lines_count++;
            char_count = 0;
        }

        if(lines_count == VISIBLE_LINES)
        {
            /* si la cantidad de lines es iguaal a 15 entonces hace
             * una pausa*/
            getchar();
            lines_count = 0;
        }
    }
}
