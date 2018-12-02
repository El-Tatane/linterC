#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototypes.h"


void arrayBracketEol(char *line, int row){
    int column;
    char *pos;
    int  i = 0;

    if ((pos = strchr(line, '{')) == NULL)
        return;
    while (line[i] != '{')
    {
        if (line[i] != ' ' && line[i] != '\t')
            return;
        i++;
    }
    column = strlen(line);
    if (*(pos + sizeof(char)) == '\0')
        displayErrorMessage("arrayBracketEol", row, column);
    return;
}

int ifLongOperator(char *line)
{
    char longOperator[][2] = {
        "+=", "-=","/=", "%=",  "==",  "=!",  "||",  ">>",  "<<", "&&"
    };
    int len;

    if (strlen(line) < 1)
        return (0);

    len = 10;    
    for (int i = 0; i < len; i++)
    {
        if (line[0] == longOperator[i][0] && line[1] == longOperator[i][1])
            return (1);
    }
    return (0);
}


int ifShortOperator(char *line)
{
    char  shortOperator[] = {
        '=', '*', '+', '-', '%','/','&', '<', '>', '|'
    };

        int len;

    if (strlen(line) < 1)
        return (0);

    len = strlen(shortOperator);    
    for (int i = 0; i < len; i++)
    {
        if (line[0] == shortOperator[i])
            return (1);
    }
    return (0);
}

void operatorsSpacing(char *path, int row)
{
    int i = 1;
    if ((ifShortOperator(&path[0])) == 1)
    {
        //display
        //display msg
    }
    while (path[i] != '\0')
    {
        if ((ifLongOperator(&path[i])) == 1)
        {
            if (path[i - 1] != ' ' && path[i + 2]  != ' ')
            {
                //msg
            }
            i++;
        }
        else if ((ifShortOperator(&path[i])) == 1)
        {
            if (path[i - 1] != ' ' && path[i + 1]  != ' ')
             {
                //msg
             }
        }
        i++;
    }   
}

void commaSpacing(char path[]){

    FILE* fichier = fopen(path, "r");
    char cara = 0;
    int ligne = 1;
    int colonne = 1;
    int longueur = 0;
    int i = 0;

    if(fichier != NULL){

        // init du nombre de caractere dans le fichier
        while(cara != EOF){
            cara = fgetc(fichier);
            longueur++;
        }

        rewind(fichier);
        cara = 0;
        char T[longueur];

        // init du tableau T avec les valeur du fichier
        while(cara != EOF){
            i++;
            cara = fgetc(fichier);

            T[i] = cara;
        }

        rewind(fichier);
        cara = 0;
        i = 0;

        // verification de la regle
        while(cara != EOF){
            i++;
            colonne++;
            cara = fgetc(fichier);

            if(cara == '\n'){
                ligne++;
                colonne = 0;
            }

            if(T[i] == ',' && T[i + 1] != '\"' && T[i + 1] != '\''){
                if(T[i + 1] != ' '){
                    printf("comma-spacing: Dans le fichier %s il doit y avoir un espace a droite de la virgule.\nErreur ligne: %d, colonne: %d\n\n", path, ligne, colonne);
                }
            }
        }

        fclose(fichier);
    }

    else {
        printf("Erreur lors de l'ouverture \n");
    }
}

void commentsHeader(char path[]){

    FILE* fichier = fopen(path, "r");
    char cara = 0;
    int ligne = 1;
    int longueur = 0;
    int i = 0;

    if(fichier != NULL){

        // init du nombre de caractere dans le fichier
        while(cara != EOF){
            cara = fgetc(fichier);
            longueur++;
        }

        rewind(fichier);
        cara = 0;
        char T[longueur];

        // init du tableau T avec les valeur du fichier
        while(cara != EOF){
            i++;
            cara = fgetc(fichier);

            T[i] = cara;
        }

        rewind(fichier);
        cara = 0;
        i = 0;

        // verification de la regle
        while(cara != EOF){
            i++;
            cara = fgetc(fichier);

            if(cara == '\n'){
                ligne++;
            }

            if(T[i] == '/' && T[i + 1] == '*'){
                printf("comments-header : Dans le fichier %s il y a la presence d'un commentaire multi-ligne a la ligne %d\n\n", path, ligne);
            }
        }

        fclose(fichier);
    }

    else {
        printf("Erreur lors de l'ouverture \n");
    }
}

void maxLineNumbers(char path[], int n){

    FILE* fichier = fopen(path, "r");
    char cara = 0;
    int longueur = 0;

    if(fichier != NULL){

        // init du nombre de caractere dans le fichier
        while(cara != EOF){
            cara = fgetc(fichier);
            longueur++;
        }

        if(longueur > n){
            printf("max-line-numbers : Le fichier %s a depasser le nombre de caractere max demander, %d > %d\n", path, longueur, n);
        }

        fclose(fichier);
    }

    else {
        printf("Erreur lors de l'ouverture \n");
    }
}

void maxFileLineNumbers(char path[], int n){

    FILE* fichier = fopen(path, "r");
    char cara = 0;
    int ligne = 1;
    int longueur = 0;

    if(fichier != NULL){

        // init du nombre de caractere dans le fichier
        while(cara != EOF){
            cara = fgetc(fichier);
            longueur++;

            if(cara == '\n'){
                ligne++;
            }
        }

        if(ligne > n){
            printf("max-file-line-numbers : Le fichier %s a depasser le nombre de ligne max demander, %d > %d\n", path, ligne, n);
        }

        fclose(fichier);
    }

    else {
        printf("Erreur lors de l'ouverture \n");
    }
}

void noTrailingSpaces(char path[]){

    FILE* fichier = fopen(path, "r");
    char cara = 0;
    int ligne = 1;
    int colonne = 1;
    int longueur = 0;
    int i = 0;

    if(fichier != NULL){

        // init du nombre de caractere dans le fichier
        while(cara != EOF){
            cara = fgetc(fichier);
            longueur++;
        }

        rewind(fichier);
        cara = 0;
        char T[longueur];

        // init du tableau T avec les valeur du fichier
        while(cara != EOF){
            i++;
            cara = fgetc(fichier);

            T[i] = cara;
        }

        rewind(fichier);
        cara = 0;
        i = 0;

        // verification de la regle
        while(cara != EOF){
            i++;
            colonne++;
            cara = fgetc(fichier);

            if(T[i] == '\n' && T[i - 1] == ' '){
                printf("no-trailing-spaces: Dans le fichier %s il ne doit pas y avoir d'espace a la fin de la ligne.\nErreur ligne: %d, colonne: %d\n\n", path, ligne, colonne);
            }

             if(cara == '\n'){
                ligne++;
                colonne = 0;
            }
        }

        fclose(fichier);
    }

    else {
        printf("Erreur lors de l'ouverture \n");
    }
}
