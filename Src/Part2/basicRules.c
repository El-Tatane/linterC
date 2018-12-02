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
    if (*(pos + sizeof(char)) == '\0' || *(pos + sizeof(char)) == '\r')
        displayErrorMessage("arrayBracketEol", row + 1, column);
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
        {
            return (1);
        }
    }
    return (0);
}

int ifParticularCase(char *line)
{
    char particularOperator[][2] = {
        "++",  "--"
    };
    int len;

    if (strlen(line) < 1)
        return (0);

    if ((line[0] == '/' && line[1] == '/')
        || (line[0] == '*' && line[1] == '/')
        || (line[0] == '/' && line[1] == '*'))
        return (2);   

    len = 2; 
    for (int i = 0; i < len; i++)
    {
        if (line[0] == particularOperator[i][0] && line[1] == particularOperator[i][1])
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
    
    //printf("%s\n", line);
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
    int nb;
    
    nb = ifParticularCase(&path[0]);
    if (nb == 1)
        i++;
    else if (nb == 2)
        return;
    if ((ifShortOperator(&path[0])) == 1)
        displayErrorMessage("operatorsSpacing", row + 1, 0);
    while (path[i] != '\0')
    {
        nb = ifParticularCase(&path[i]);
        if (nb == 1)
            i++;
        else if (nb == 2)
            return;
        else if ((ifLongOperator(&path[i])) == 1)
        {
            if (path[i - 1] != ' ' || path[i + 2]  != ' ')
                displayErrorMessage("operatorsSpacing", row + 1, i);
            i++;
        }
        else if ((ifShortOperator(&path[i])) == 1)
        {
            if (path[i - 1] != ' ' || path[i + 1]  != ' ')
                displayErrorMessage("operatorsSpacing", row + 1, i);
        }
        i++;
    }   
}

void maxLineNumbers()
{
    
}

void commaSpacing(char *line, int row)
{
    int column;
    char pos;
    int i;

    i = 0;
    while (line[i] != '\0')
    {
        if (line[i] == ',' && line[i + 1] != ' ')
            displayErrorMessage("commaSpacing", row + 1, i);
        i++;
    }
}

//void indent(char *line, int row)

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
