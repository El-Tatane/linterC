#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototypes.h"
#include "list.h"

char *removeSpaces(char *part)
{
    int i = 0;
    int n = 0;
    char *ret;

    if ((ret = malloc(sizeof(char) * strlen(part))) == NULL)
        return (NULL);
    while (part[i] != '\0')
    {   
        if (part[i] != ' ' && part[i] != '\t')
            ret[n++] = part[i];
        i++;
    }
    ret[n] = '\0';
    return (ret);
}

int isFunctionChar(char c)
{  
    if (c >= '0' && c <= '9' || c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z' || c == '_')
    {
        return (1);
    }
    return (0);
}

char  *getLastPart(char *str, char c)
{
    char *ret;
    int i;
    int n;

    n = 0;
    i = strlen(str);
    while (str[i] != c)
        i--;   
    if ((ret = malloc(sizeof(char) * i + 1)) == NULL)
        return (NULL);
    i = strlen(str);
    while (str[i] != c)
    {
        ret[n] = str[i];
        n++;
        i--;
    }
    ret[n] = '\0';
    return (ret);
}

char  *getFirstPart(char *str, char c, int *nbWord)
{
    char *ret;
    int i = 0;
    
    while (str[i] != c)
    {
        if (i == 0 && isFunctionChar(str[i]) == 1)
            (*nbWord)++;
        else if (isFunctionChar(str[i]) == 1 && (str[i - 1] == ' ' || str[i - 1] == '\t'))  
            (*nbWord)++;
        i++;
    }
    if ((ret = malloc(sizeof(char) * i + 1)) == NULL)
        return (NULL);
    strncpy(ret, str, i);
    ret[i] = '\0';
    return (ret);
}

t_var *getOneParam(t_var *mainNode, char *part)
{
    char *noSpace;
    char *tmpType;

    if (strchr(part, '*') != NULL)
    {
        if ((noSpace = removeSpaces(part)) == NULL)
            return (NULL);

        char *lastPart;

        if ((lastPart = getLastPart(noSpace, '*')) == NULL)
            return (NULL);
        if ((tmpType = malloc(sizeof(char) * (strlen(noSpace) - strlen(lastPart + 1)) + 1)) == NULL)
            return (NULL);
        strncpy(tmpType, noSpace, (strlen(noSpace) - strlen(lastPart + 1)));
        tmpType[strlen(noSpace) - strlen(lastPart + 1)] = '\0';
        
        if (mainNode == NULL)
        {
            if (((mainNode = initVarList(mainNode, tmpType, lastPart + 1, 1))) == NULL)
                return (NULL);
        }
        else
        {
            if (((mainNode = addVarNode(mainNode, tmpType, lastPart + 1, 1))) == NULL)
                return (NULL);
        }
    }
    else
    {
        int i;
        int n;
        char *type;
        char *name;

        i = 0;
        while (part[i] != '\0')
        {
            if (!(part[i] == ' ' || part[i] == '\t'))
                type = getFirstPart(part, ' ', &n);
            i++;
        }
        i = strlen(part);
        while (i > 0)
        {
            if (!(part[i] == ' ' || part[i] == '\t'))
                name = getLastPart(part, ' ');
            i--;
        }
        
        if (mainNode == NULL)
        {
            if (((mainNode = initVarList(mainNode, type, name, 1))) == NULL)
                return (NULL);
        }
        else
        {
            if (((mainNode = addVarNode(mainNode, type, name, 1))) == NULL)
                return (NULL);
        }
    }
}

t_var *getFuncParams(char *line)
{
    int nb  = 0;
    char part[2048];
    t_var *newVarList = NULL;
    char *tmpType;
    char *tmpName;


    strcpy(part, getFirstPart(strchr(line, '(') + 1, ')', &nb));

    //no params
    if (strchr(part, ',') == NULL && nb == 0)
    {
        if (((newVarList = initVarList(newVarList, "UNDEFINED", "UNDEFINED", 0))) == NULL)
            return (NULL);
    }
    else if (strchr(part, ',') == NULL && nb != 0)
    {
        if ((newVarList = getOneParam(newVarList, part)) == NULL)
            return (NULL);
    }

    // if (nb == 2)
    // {
    //     if ((tmpType = strdup(strtok(part, " "))) == NULL)
    //         return (NULL);
    //     if ((tmpName = strdup(strtok(NULL, " "))) == NULL)
    //         return (NULL);
    //     if (newVarList == NULL)
    //     {
    //         if ((newVarList = initVarList(newVarList, tmpType, tmpName, 1)) == NULL)
    //             return (NULL);
    //     }
    //     else
    //     {
    //         if ((newVarList = addVarNode(newVarList, tmpType, tmpName, 1)) == NULL)
    //             return (NULL);
    //     }
    // }

    displayVarList(newVarList);
    return (newVarList);
}

t_scopeList *createScopeList(t_list *fileContent, t_scopeList *mainScopeList)
{

    while (fileContent != NULL)
    {
        char tmpName[2048];
        char tmpType[2048];
        char firstPart[2048];
        int  nbWord = 0;
        t_var *varNode;
        if ((strchr(fileContent->path, '(') != NULL) && (strchr(fileContent->path, ')') != NULL)
         && (strchr(fileContent->path, ';') == NULL))
        {
            strcpy(firstPart, getFirstPart(fileContent->path, '(', &nbWord));
            if (nbWord == 2)
            {
                strcpy(tmpType, strtok(firstPart, " "));
                strcpy(tmpName, strtok(NULL, " "));
                varNode = getFuncParams(fileContent->path); // FUNC
                if (mainScopeList == NULL)
                    mainScopeList = initScopeList(mainScopeList, tmpName, tmpType, varNode);
            }
            
        }
        fileContent = fileContent->next;
    }
    return (mainScopeList);
}