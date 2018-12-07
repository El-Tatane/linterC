#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototypes.h"


void arrayBracketEol(char *line, int rowNb)
{
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
        displayErrorMessage("arrayBracketEol", rowNb + 1, column);
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

void operatorsSpacing(char *path, int rowNb)
{
    int i = 1;
    int nb;
    
    nb = ifParticularCase(&path[0]);
    if (nb == 1)
        i++;
    else if (nb == 2)
        return;
    if ((ifShortOperator(&path[0])) == 1)
        displayErrorMessage("operatorsSpacing", rowNb + 1, 0);
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
                displayErrorMessage("operatorsSpacing", rowNb + 1, i);
            i++;
        }
        else if ((ifShortOperator(&path[i])) == 1)
        {
            if (path[i - 1] != ' ' || path[i + 1]  != ' ')
                displayErrorMessage("operatorsSpacing", rowNb + 1, i);
        }
        i++;
    }   
}

void maxLineNumbers(char *line, int rowNb, int max)
{
    int len;
    len = strlen(line);
    if (len > max)
       displayErrorMessage("maxLineNumbers", rowNb + 1, len); 
}

void noTrailingSpaces(char *line, int rowNb)
{
    int column;

    column = strlen(line);
    printf("%c\n", line[column - 2]);
    if (line[column - 2] == ' ' || line[column - 2] == '\t')
        displayErrorMessage("noTrailingSpaces", rowNb + 1, column - 1);
    return;
}

void commaSpacing(char *line, int rowNb)
{
    int column;
    char pos;
    int i;

    i = 0;
    while (line[i] != '\0')
    {
        if (line[i] == ',' && line[i + 1] != ' ')
            displayErrorMessage("commaSpacing", rowNb + 1, i);
        i++;
    }
}

void noMultiDeclaration(char *line, int rowNb)
{
    char types[][10] = {
        "int",
        "char",
        "double",
        "float",
        "short",
        "long",
        "bool",
        "void",
        "unsigned",
        "struct",
    };
    int find;
    int n;
    unsigned int count;

    n = 0;
    count = 0;
    find = 0;
    for (int i = 0; i < 10; i++)
    {
        if ((strstr(line, types[i])) != NULL)
        {
            find = 1;
            break;
        }
    }
    if (find == 0)
        return;
    if ((strchr(line, '(')) != NULL && (strchr(line, ')')) != NULL)
        return;
    if ((strchr(line, ',')) != NULL)
        displayErrorMessage("noMultiDeclaration", rowNb + 1, -1);

    while (line[n] != '\0')
    {
        if (line[n] == ';')
            count++;
        n++;
    }
    if (count >= 2)
        displayErrorMessage("noMultiDeclaration", rowNb + 1, -1);
}
