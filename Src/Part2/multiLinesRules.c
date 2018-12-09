#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"
#include "prototypes.h"

int isVarUsed(char *var, char *line, int deep)
{
    if (containsType(line) == 0 && strstr(line, var) != NULL)
        return (1);
    return (0);
}

int searchVariable(t_list *tmpList, t_var *var)
{
    int deep = 0;
    int used = 0;
    int func = 0;

    if (var->isParam == 1)
    {
        deep = -1;
        func = 1;
    }
    while (tmpList != NULL) // parcours les lignes du fichier
    {   
        if (deep == 0)
            func = 0;
        if (deep < 0 && func == 0)
            break;
        if (strchr(tmpList->path, '{') != NULL)
            deep++;
        if (strchr(tmpList->path, '}') != NULL)
            deep--;
        if ((isVarUsed(var->name, tmpList->path, deep)) == 1)
            used = 1;
        tmpList = tmpList->next;
    }
    if (used == 0)
    {
        printf("Error on %s , rule : %s failed at line %d variable : %s \n", currentFile, "unusedVariable", var->foundAtLine , var->name);
    }
}

t_list *getStartingLine(t_list *mainNode, int pos)
{
    int i = 0;
    while (i < pos)
    {
        mainNode = mainNode->next;
        i++;
    }
    return (mainNode);
}

int containsFunction(char *line, char *func)
{
    if ((strstr(line, func) != NULL && strchr(line, '(') != NULL && strchr(line, ')') != NULL) && containsType(line) == 0)
        return (1);
    return (0);
}
void unusedFunction(t_scopeList *mainNode, t_list *list)
{
    t_list *tmpList;
    t_scopeList *tmpNode;
    int          isUsed = 0;

   tmpNode = mainNode;
   while (tmpNode != NULL)
   {
        tmpList = list;
        isUsed = 0;
        while (tmpList != NULL)
        {
            if ((containsFunction(tmpList->path, tmpNode->funcName)) == 1)
            { 
                isUsed = 1;
                break;
            }
            tmpList = tmpList->next;
        }
        if (isUsed == 0)
            printf("Error on %s , rule : %s failed at line %d variable : %s \n", currentFile, "unusedFunction",
             tmpNode->foundAtLine , tmpNode->funcName);
        tmpNode = tmpNode->next;
   }
}

void unusedVariable(t_scopeList *mainNode, t_list *list)
{
    t_var *tmpVar;
    t_list *tmpList;
    t_scopeList *tmpNode;
    t_scopeList *tmpDeep;
    t_scopeList *tmpDN;
    int deep = 1;
    
    tmpNode = mainNode;
    while (tmpNode != NULL)
    {    
        tmpVar = tmpNode->varList;
        while (tmpVar != NULL) // parcours chaque liste de variable 
        {
            tmpList = getStartingLine(list, tmpVar->foundAtLine);
            searchVariable(tmpList, tmpVar); 
            tmpVar = tmpVar->next;
        }
        tmpDeep = tmpNode->deep;
        while (tmpDeep != NULL)
        {
            tmpVar = tmpDeep->varList;
            while (tmpVar != NULL) // parcours chaque liste de variable 
            {
                tmpList = getStartingLine(list, tmpVar->foundAtLine);
                searchVariable(tmpList, tmpVar);      
                tmpVar = tmpVar->next;
            }
            tmpDN = tmpDeep->next;
            while (tmpDN != NULL)
            {
                tmpVar = tmpDN->varList;
                while (tmpVar != NULL) // parcours chaque liste de variable 
                {
                    tmpList = getStartingLine(list, tmpVar->foundAtLine);
                    searchVariable(tmpList, tmpVar);      
                    tmpVar = tmpVar->next;
                }
                tmpDN = tmpDN->next;  
            }
            tmpDeep = tmpDeep->deep;
        }
        deep = 1;
        tmpNode = tmpNode->next;
    }
}

void undeclaredVariable(t_scopeList *mainNode, t_list *list)
{
    t_list *tmpList;

   //while (tmpList != NULL)
   //{

   //}

}

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
    int tmpLen = strlen(ret);
    ret[tmpLen] = ';';
    ret[tmpLen + 1] = '\0';
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
    if ((space / 4  + tab != size * d))
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