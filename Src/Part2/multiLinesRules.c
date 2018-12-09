#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"
#include "prototypes.h"

void maxFileLineNumbers(t_list *fileContent, int max)
{
    if (listLength(fileContent) >= max)
    {
        displayErrorMessage("maxFileLineNumbers", -1, -1);
    }
}

int  isGoodPrototypes(char *func, char *proto)
{
    char *noSpaceProto;

    if ((noSpaceProto = removeSpaces(proto)) == NULL)
        return (-1);

    printf("%s %s\n", func, noSpaceProto);
    if ((strcmp(func, noSpaceProto) == 0))
        return (1);
    return (0);
}

char *createPrototype(t_scopeList *mainNode)
{
    t_var *tmp;
    char *ret;
    int len;
    
    len = strlen(mainNode->funcName) + strlen(mainNode->returnType);
    tmp = mainNode->varList;
    while (tmp != NULL)
    {
        if (tmp->isParam == 1)
        {
            len += strlen(tmp->type);
            len += strlen(tmp->name);
        }
        tmp = tmp->next;
    }
    if ((ret = malloc(sizeof(char) * len * 2)) == NULL)
        return (NULL);

    strcpy(ret, mainNode->returnType);
    strcat(ret, mainNode->funcName);
    tmp = mainNode->varList;
    strcat(ret, "(");
    while (tmp != NULL)
    {
        if (tmp->isParam == 1)
        {
            strcat(ret, tmp->type);
            strcat(ret, tmp->name);
            strcat(ret, ",");
        }
        tmp = tmp->next;
    }
    if (ret[strlen(ret) - 1] == ',')
        ret[strlen(ret) - 1] = ')';
    else
        strcat(ret, ")");
    ret[strlen(ret)] = ';';
    ret[strlen(ret) + 1] = '\0';
    return (ret);
}

int noPrototype(t_scopeList *mainNode, t_list *fileContent)
{
    int len;
    int maxLine;
    int i = 0;
    char *func;
    int flag = 0;
    t_list *tmpLine;

    maxLine = mainNode->foundAtLine;
    while (mainNode != NULL)
    {
        i = 0;
        if ((func = createPrototype(mainNode)) == NULL)
            return (-1);
        flag = 0;
        tmpLine = fileContent;
        while (i < maxLine - 1)
        {
            if ((isGoodPrototypes(func, tmpLine->path)) == 1)
            {    
                flag = 1;
                break;
            }
            tmpLine = tmpLine->next;
            i++;
        }
        if (flag == 0)
            displayErrorMessage("noPrototype", mainNode->foundAtLine, -1);
        mainNode = mainNode->next;
    } 
    return (0);
}

void indent(char *line, int size, int lineNb, int d)
{
    int i = 0;
    int space = 0;
    int tab = 0;

    while (line[i] != '\0')
    {
        if (line[i] != '\t' && line[i] != ' ')
            break;
        if (line[i] == ' ')
            space++;
        if (line[i] == '\t');
            tab++;
        i++;
    }
    if ((space * 4  + tab != size * d))
        displayErrorMessage("indent", lineNb, -1); 
}

void commentsHeader(t_list *fileContent)
{

    int nb = 0;
    while (fileContent != NULL)
    {    
        int i = 0;
        while (fileContent->path[i] != '\0')
        {
            if (fileContent->path[i] == ' ' || fileContent->path[i] == '\t' || fileContent->path[i] == '\r')
                i++;
            else if (fileContent->path[i] == '/' && fileContent->path[i + 1] == '*')
                return;
            else if (fileContent->path[i] == '/' && fileContent->path[i + 1] == '/')
            { 
                nb++; 
                if (nb >= 2)
                    return;
                break;
            }
            else
            {
                displayErrorMessage("commentsHeader", -1, -1); 
                return;
            }
        }
        fileContent = fileContent->next;
    }
}