#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void arrayBracketEol(char path[]){

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

            if(T[i] == '{'){
                if (T[i - 1] == '\n' && T[i + 1] == '\n'){
                    printf("array-bracket-eol: Dans le fichier %s l'accolade doit se trouver en fin de ligne.\nErreur ligne: %d, colonne: %d;\n\n", path, ligne, colonne);
                }
            }
        }

        fclose(fichier);
    }

    else {
        printf("Erreur lors de l'ouverture \n");
    }
}

void operatorsSpacing(char path[]){

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

            // Test '='
            if(T[i] == '=' && T[i + 1] != '=' && T[i - 1] != '=' && T[i + 1] != '\'' && T[i - 1] != '\''){
                if(T[i - 1] != ' '){
                    printf("operators-spacing: Dans le fichier %s il doit y avoir un espace avant le '='.\nErreur ligne: %d, colonne: %d\n\n", path, ligne, colonne);
                }
                else if(T[i + 1] != ' '){
                    printf("operators-spacing: Dans le fichier %s il doit y avoir un espace apres le '='.\nErreur ligne: %d, colonne: %d\n\n", path, ligne, colonne);
                }
            }
            // Test '=='
            else if(T[i] == '=' && T[i + 1] == '=' && T[i + 1] != '\'' && T[i - 1] != '\''){
                if(T[i - 1] != ' '){
                    printf("operators-spacing: Dans le fichier %s il doit y avoir un espace avant le '=='.\nErreur ligne: %d, colonne: %d\n\n", path, ligne, colonne);
                }
                else if(T[i + 2] != ' '){
                    printf("operators-spacing: Dans le fichier %s il doit y avoir un espace apres le '=='.\nErreur ligne: %d, colonne: %d\n\n", path, ligne, colonne);
                }
            }
            // Test '+'
            else if(T[i] == '+' && T[i + 1] != '+' && T[i - 1] != '+' && T[i + 1] != '\'' && T[i - 1] != '\''){
                if(T[i - 1] != ' '){
                    printf("operators-spacing: Dans le fichier %s il doit y avoir un espace avant le '+'.\nErreur ligne: %d, colonne: %d\n\n", path, ligne, colonne);
                }
                else if(T[i + 1] != ' '){
                    printf("operators-spacing: Dans le fichier %s il doit y avoir un espace apres le '+'.\nErreur ligne: %d, colonne: %d\n\n", path, ligne, colonne);
                }
            }
            // Test '-'
            else if(T[i] == '-' && T[i + 1] != '-' && T[i - 1] != '-' && T[i + 1] != '\'' && T[i - 1] != '\''){
                if(T[i - 1] != ' '){
                    printf("operators-spacing: Dans le fichier %s il doit y avoir un espace avant le '-'.\nErreur ligne: %d, colonne: %d\n\n", path, ligne, colonne);
                }
                else if(T[i + 1] != ' '){
                    printf("operators-spacing: Dans le fichier %s il doit y avoir un espace apres le '-'.\nErreur ligne: %d, colonne: %d\n\n", path, ligne, colonne);
                }
            }
            // Test '*'
            else if(T[i] == '*' && T[i + 1] != '\'' && T[i - 1] != '\''){
                if(T[i - 1] != ' '){
                    printf("operators-spacing: Dans le fichier %s il doit y avoir un espace avant le '*'.\nErreur ligne: %d, colonne: %d\n\n", path, ligne, colonne);
                }
                else if(T[i + 1] != ' '){
                    printf("operators-spacing: Dans le fichier %s il doit y avoir un espace apres le '*'.\nErreur ligne: %d, colonne: %d\n\n", path, ligne, colonne);
                }
            }
            // Test '/'
            else if(T[i] == '/' && T[i + 1] != '/' && T[i - 1] != '/' && T[i + 1] != '\'' && T[i - 1] != '\''){
                if(T[i - 1] != ' '){
                    printf("operators-spacing: Dans le fichier %s il doit y avoir un espace avant le '/'.\nErreur ligne: %d, colonne: %d\n\n", path, ligne, colonne);
                }
                else if(T[i + 1] != ' '){
                    printf("operators-spacing: Dans le fichier %s il doit y avoir un espace apres le '/'.\nErreur ligne: %d, colonne: %d\n\n", path, ligne, colonne);
                }
            }
            // Test '%'
            else if(T[i] == '%' && T[i + 1] != '\'' && T[i - 1] != '\''){
                if(T[i - 1] != ' '){
                    printf("operators-spacing: Dans le fichier %s il doit y avoir un espace avant le '%%'.\nErreur ligne: %d, colonne: %d\n\n", path, ligne, colonne);
                }
                else if(T[i + 1] != ' '){
                    printf("operators-spacing: Dans le fichier %s il doit y avoir un espace apres le '%%'.\nErreur ligne: %d, colonne: %d\n\n", path, ligne, colonne);
                }
            }
        }

        fclose(fichier);
    }

    else {
        printf("Erreur lors de l'ouverture \n");
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
