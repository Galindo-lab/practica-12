/* 2. Elaborar un programa (convert.c) que lea un archivo de texto y convierta las */
/* minúsculas por mayúsculas (o viceversa según los parámetros), además, */
/* dependiendo de los parámetros por consola imprimir el contenido del archivo */
/* en la consola o en otro archivo. */
/* > convert.exe mayus nombre_de_archivo.txt */
/* > convert.exe mayus nombre_de_archivo.txt nombre_destino.txt */
/* > convert.exe minus nombre_de_archivo.txt */
/* > convert.exe minus nombre_de_archivo.txt nombre_destino.txt */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int valid_params(int, char *argv[]);
void error_message();
int file_exists(const char*);
char to_lower(char);
char to_upper(char);
void write(char[], char[], char (*casing)(char));
void display(char[], char (*casing)(char));


int main(int argc, char *argv[])
{
    if(valid_params(argc, argv))
    {

        switch (argc) {
            case 3:
                if(strcmp(argv[1], "mayus") == 0)
                    display(argv[2], to_upper);

                if(strcmp(argv[1], "minus") == 0)
                    display(argv[2], to_lower);

                break;
            case 4:
                if(strcmp(argv[1], "mayus") == 0)
                    write(argv[2], argv[3], to_upper);

                if(strcmp(argv[1], "minus") == 0)
                    write(argv[2], argv[3], to_lower);

                break;
        }

    }
    else
    {
        error_message();
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
        if(strcmp(argv[1], "mayus") == 1
           && strcmp(argv[1], "minus") == 1)
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
    printf("mayus : Convierte las letras a mayusculas.\n");
    printf("minus : Convierte las letras a minusculas\n");
}

char to_lower(char c)
{
    return (c >= 'A' && c <= 'Z') ? c + 32 : c ;
}

char to_upper(char c)
{
    return (c >= 'a' && c <= 'z') ? c - 32 : c ;
}

void display(char origen[], char (*casing)(char))
{
    char ch;
    FILE *fr = fopen(origen, "r"); /* archivo a leer */

    while((ch = fgetc(fr)) != EOF)
    {
        printf("%c", casing(ch));
    }

    fclose(fr);
}

void write(char origen[], char destino[], char (*casing)(char)  )
{
    char ch;
    FILE *fr = fopen(origen, "r"); /* archivo a leer */
    FILE *fw = fopen(destino, "w"); /* archivo a escribir */

    while((ch = fgetc(fr)) != EOF)
    {
        fprintf (fw, "%c", casing(ch));
    }

    fclose(fr);
    fclose(fw);
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
