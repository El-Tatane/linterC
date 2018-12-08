#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototypes.h"
#include "list.h"

void displayScopeList(t_scopeList *mainNode)
{
    t_scopeList *tmpDeep;
    int deep = 1;
     while (mainNode != NULL)
    {
        printf("DEEP %d FUNC NAME : %s FUNC TYPE : %s FOUND AT %d \n",
         deep, mainNode->funcName, mainNode->returnType, mainNode->foundAtLine);
        displayVarList(mainNode->varList);
        tmpDeep = mainNode->deep;
        while (tmpDeep != NULL)
        {    
            deep++;
            printf("DEEP %d SCOPE NAME : %s FUNC TYPE : %s FOUND AT %d \n",
             deep, tmpDeep->funcName, tmpDeep->returnType, tmpDeep->foundAtLine);
            displayVarList(mainNode->varList);
            tmpDeep = tmpDeep->deep;
        }
        deep = 1;
        mainNode = mainNode->next;
    }
}

int listLen(t_scopeList *mainScopeNode)
{
    int i = 0;

    if (mainScopeNode == NULL)
        return (0);
    while (mainScopeNode->next != NULL)
    {
        mainScopeNode = mainScopeNode->next;
        i++;
    }
    return (i);
}

int listDeep(t_scopeList *mainScopeNode)
{
    int i = 0;

    if (mainScopeNode == NULL)
        return (0);
    while (mainScopeNode->deep != NULL)
    {
        printf("ICI\n");
        mainScopeNode = mainScopeNode->deep;
        i++;
    }
    return (i);
}

t_scopeList *addEmptyNodeDeepAtPosition(t_scopeList *mainScopeNode, int n, int d, int len)
{
    t_scopeList *tmpNode;
    int i = 0;

    tmpNode = mainScopeNode;

    while (i < (n - 1)) // enlever - 1 quand ajout casse global
    {
        tmpNode = tmpNode->next;
        i++;
    }
    while (tmpNode->deep != NULL)
        tmpNode = tmpNode->deep;
    if (tmpNode == NULL)
    {
        tmpNode = initScopeList(tmpNode, "EMPTY_NODE", "EMPTY_NODE", NULL, len);
    }
    else
    {

        tmpNode = addLineScopeNode(tmpNode,  "EMPTY_NODE", "EMPTY_NODE", NULL, len);
    }
    return (mainScopeNode);
}

t_scopeList *addVarAtPosition(t_scopeList *mainScopeNode, int n, int d, t_var *tmpVar, int len)
{
    int i = 0;
    int deep;

    t_scopeList *tmpNode;
    t_var *tmp;

    tmpNode = mainScopeNode;
    while (i < n - 1) // enlever - 1 quand ajout casse global
    {
        tmpNode = tmpNode->next;
        i++;
    }
    printf("%s\n", tmpNode->funcName);
    

    deep = listDeep(tmpNode);
    printf("%d %d\n", d, deep);
    if ((d - 1) > deep)
    {
        printf("deep node not existing\n");
        return (NULL);
    }

    i = 0;

    while (i < d - 1)
    {
        tmpNode = tmpNode->deep;
        i++;
    }
    while (tmpNode->next != NULL)
    {
        tmpNode = tmpNode->next;
    }
    
    tmp = tmpNode->varList;
    
    if (tmp == NULL)
    {
        tmpNode->varList = tmpVar;
    }
    else if ((strcmp(tmp->name, "UNDEFINED")) == 0)
    {
        tmpNode->varList = tmpVar;
    }
    else
    {
        while (tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        tmp->next = tmpVar;
    }
    return (mainScopeNode);
}

t_scopeList *addLineScopeNode(t_scopeList *mainNode, char *funcName, char *type, t_var *vars, int len)
{
    t_scopeList *newNode;
    t_scopeList *location;

    location = mainNode;

    if ((newNode = malloc(sizeof(t_scopeList) * 1)) == NULL)
        return (NULL);
    if ((newNode->funcName = malloc(sizeof(char) * strlen(funcName) + 1)) == NULL)
        return (NULL);
    if ((newNode->returnType = malloc(sizeof(char) * strlen(type) + 1)) == NULL)
        return (NULL);
    while (location->next != NULL)
        location = location->next;

    newNode->next = NULL;
    newNode->deep = NULL;
    location->next = newNode;

    newNode->foundAtLine = len;
    strcpy(newNode->funcName, funcName);
    strcpy(newNode->returnType, type);
    newNode->varList = vars;
    return (mainNode);
}

t_scopeList *initScopeList(t_scopeList *mainScopeNode, char *funcName, char *type, t_var *vars, int len)
{
    if ((mainScopeNode = malloc(sizeof(t_scopeList) * 1)) == NULL)
        return (NULL);
    if ((mainScopeNode->funcName = malloc(sizeof(char) * strlen(funcName) + 1)) == NULL)
        return (NULL);
    if ((mainScopeNode->returnType = malloc(sizeof(char) * strlen(type) + 1)) == NULL)
        return (NULL);
    mainScopeNode->next = NULL;
    mainScopeNode->deep = NULL;
    strcpy(mainScopeNode->funcName, funcName);
    strcpy(mainScopeNode->returnType, type);
    mainScopeNode->varList = vars;
    mainScopeNode->foundAtLine = len;
    return (mainScopeNode);
}