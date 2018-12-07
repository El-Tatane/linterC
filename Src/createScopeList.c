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
    if ((strchr(str, c)) == NULL)
        return (NULL);
    i = strlen(str);
    while (str[i] != c)
        i--;
    if ((ret = malloc(sizeof(char) * (strlen(str)))) == NULL)
        return (NULL);
    
    while (str[i] != '\0')
    {
        ret[n] = str[i];
        n++;
        i++;
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

char  *getLastWord(char *str, int pos)
{
    int tmp;
    char *ret;
    int i = 0;

    tmp = pos;
    while (tmp > 0)
    {
        if (str[tmp] == ' ' || str[tmp] == '\t')
            break;
        tmp--;
    }
    if ((ret = malloc(sizeof(char) * (pos - tmp) + 1)) == NULL)
        return (NULL);

    tmp++;
    while (tmp < pos)
    {
        ret[i] = str[tmp];
        i++;
        tmp++;
    }
    ret[i] = '\0';
   return (ret);
}

t_var *getOneParam(t_var *mainNode, char *part)
{
    char *noSpace;
    char *tmpType;

    if ((strchr(part, '*')) != NULL)
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
        int j;
        char *type;
        char *name;

        i = strlen(part);
        while (i > 0)
        {
            if ((part[i] != ' ' && part[i] != '\t'))
            {
                if ((name = getLastWord(part, i)) == NULL)
                    return (NULL);
                break;
            }
            i--;
        }
        n = 0;
        j = 0;
        int len = strlen(part) - ((strlen(name) + strlen(part + i)));
        if ((type = malloc(sizeof(char) * (len + 1))) == NULL)
            return (NULL);
        while (j < len)
        {
            if ((part[j] != ' ' && part[j] != '\t'))
            {
                type[n] = part[j];
                n++;
            }
            j++;
        }
        type[n] = '\0';

        
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
    char *tmpPart;


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
    else if (strchr(part, ',') != NULL && nb != 0)
    {
        if ((tmpPart = strtok(part, ",")) == NULL)
            return (NULL);
        if ((newVarList = getOneParam(newVarList, tmpPart)) == NULL)
            return (NULL);
        while ((tmpPart = strtok(NULL, ",")) != NULL)
        {
            if ((newVarList = getOneParam(newVarList, tmpPart)) == NULL)
                return (NULL);                    
        }
    }
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
                varNode = getFuncParams(fileContent->path);
                if (mainScopeList == NULL)
                    mainScopeList = initScopeList(mainScopeList, tmpName, tmpType, varNode);
                else
                    mainScopeList = addLineScopeNode(mainScopeList, tmpName, tmpType, varNode);
            }
            
        }
        fileContent = fileContent->next;
    }
    displayScopeList(mainScopeList);
    return (mainScopeList);
}