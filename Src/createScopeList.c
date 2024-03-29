#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototypes.h"
#include "list.h"

t_var *getPointerParam(t_var *mainNode, char *part, int len, int isParam) // get pointer param
{
    char *noSpace;
    char *tmpType;

    if ((noSpace = removeSpaces(part)) == NULL)
        return (NULL);

    char *lastPart;

    if ((lastPart = getLastPart(noSpace, '*')) == NULL)
        return (NULL);
    if ((tmpType = malloc(sizeof(char) * (strlen(noSpace) - strlen(lastPart + 1)) + 1)) == NULL)
        return (NULL);
    strncpy(tmpType, noSpace, (strlen(noSpace) - strlen(lastPart + 1)));
    tmpType[strlen(noSpace) - strlen(lastPart + 1)] = '\0';

    int i = 1;
    while (lastPart[i] != '\0')
    {
        if (lastPart[i] == ';')
            lastPart[i] = '\0';
        i++;
    }
    if (mainNode == NULL)
    {
        if (((mainNode = initVarList(mainNode, tmpType, lastPart + 1, isParam, len))) == NULL)
            return (NULL);
    }
    else
    {
        if (((mainNode = addVarNode(mainNode, tmpType, lastPart + 1, isParam, len))) == NULL)
            return (NULL);
    }
    return (mainNode);
}

t_var *getNotPointerParam(t_var *mainNode, char *part, int len, int isParam) //Get a not pointer param
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
    int strLen = strlen(part) - ((strlen(name) + strlen(part + i)));
    if ((type = malloc(sizeof(char) * (strLen + 1))) == NULL)
        return (NULL);
    while (j < strLen)
    {
        if ((part[j] != ' ' && part[j] != '\t'))
        {
            type[n] = part[j];
            n++;
        }
        j++;
    }
    type[n] = '\0';
    j = strlen(name);

    while (j > 0)
    {
        if (name[j] == ';')
            name[j] = '\0';
        j--;
    }
    if (mainNode == NULL)
    {
        if (((mainNode = initVarList(mainNode, type, name, isParam, len))) == NULL)
            return (NULL);
    }
    else
    {
        if (((mainNode = addVarNode(mainNode, type, name, isParam, len))) == NULL)
            return (NULL);
    }
    return (mainNode);
}

t_var *getOneParam(t_var *mainNode, char *part, int len, int isParam) // Get One Func Param
{
    char *noSpace;
    char *tmpType;

    if ((strchr(part, '*')) != NULL)
    {
        if ((mainNode = getPointerParam(mainNode, part, len, isParam)) == NULL)
            return (NULL);
    }
    else
    {
        if ((mainNode = getNotPointerParam(mainNode, part, len, isParam)) == NULL)
            return (NULL);
    }
    return (mainNode);
}

t_var *getFuncParams(char *line, int len) // get ALL Func Params
{
    int nb  = 0;
    char part[2048];
    t_var *newVarList = NULL;
    char *tmpPart;


    strcpy(part, getFirstPart(strchr(line, '(') + 1, ')', &nb));
    //no params
    if (strchr(part, ',') == NULL && nb == 0)
    {
        if (((newVarList = initVarList(newVarList, "UNDEFINED", "UNDEFINED", 0, len))) == NULL)
            return (NULL);
    }
    else if (strchr(part, ',') == NULL && nb != 0)
    {
        if ((newVarList = getOneParam(newVarList, part, len, 1)) == NULL)
            return (NULL);
    }
    else if (strchr(part, ',') != NULL && nb != 0)
    {
        if ((tmpPart = strtok(part, ",")) == NULL)
            return (NULL);
        if ((newVarList = getOneParam(newVarList, tmpPart, len, 1)) == NULL)
            return (NULL);
        while ((tmpPart = strtok(NULL, ",")) != NULL)
        {
            if ((newVarList = getOneParam(newVarList, tmpPart, len, 1)) == NULL)
                return (NULL);                    
        }
    }
    return (newVarList);
}

t_scopeList *addInsideParams(t_scopeList *mainScopeList, char *line, int len, int n, int d)
{
    t_var *tmpVar;

    tmpVar = getInsideParams(line, len);
    mainScopeList = addVarAtPosition(mainScopeList, n, d, tmpVar, len);
    return (mainScopeList);
}

t_scopeList *addFunction(t_scopeList *mainScopeList, char *line, int len, char * firstPart)
{
    char tmpName[2048];
    char tmpType[2048];
    t_var *varNode;

    strcpy(tmpType, strtok(firstPart, " "));
    strcpy(tmpName, strtok(NULL, " "));
    if ((varNode = getFuncParams(line, len)) == NULL)
        return (NULL);
    if (mainScopeList == NULL)
        mainScopeList = initScopeList(mainScopeList, tmpName, tmpType, varNode, len);
    else
        mainScopeList = addLineScopeNode(mainScopeList, tmpName, tmpType, varNode, len);
    return (mainScopeList);
}

t_scopeList *createScopeList(t_list *fileContent, t_scopeList *mainScopeList, t_rules rules)
{
    int d = 0;
    int n = 0;
    int len = 1;
    int func = 1;

    while (fileContent != NULL)
    {
        if ((strchr(fileContent->path, '(') != NULL) && (strchr(fileContent->path, ')') != NULL) && (strchr(fileContent->path, ';') == NULL))
        {
            char firstPart[2048];
            int nbWord = 0;
            strcpy(firstPart, getFirstPart(fileContent->path, '(', &nbWord));
            if (nbWord == 2)
            {
                n++;
                func = 1;
                if ((mainScopeList = addFunction(mainScopeList, fileContent->path, len, firstPart)) == NULL)
                    return (NULL);
            }
        }
        else if ((containsType(fileContent->path) == 1 && strchr(fileContent->path, '(') == NULL && strchr(fileContent->path, ')') == NULL))
        {
            mainScopeList = addInsideParams(mainScopeList, fileContent->path, len, n, d);
        }
        if (rules.indent != 0)
        {
            indent(fileContent->path, rules.indent, len, d);
        }

        if ((strchr(fileContent->path, '}')) != NULL)
            d--;

        if ((strchr(fileContent->path, '{')) != NULL)
        {
            d++;
            if (func == 1)
                func = 0;
            else
                mainScopeList = addEmptyNodeDeepAtPosition(mainScopeList, n, d, len);
        }
        fileContent = fileContent->next;
        len++;
    }
    return (mainScopeList);
}