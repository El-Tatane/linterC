#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototypes.h"
#include "list.h"

void displayScopeList(t_scopeList *mainNode)
{
     while (mainNode != NULL)
    {
        printf("FUNC NAME : %s FUNC TYPE : %s FOUND AT %d \n", mainNode->funcName, mainNode->returnType, mainNode->foundAtLine);
        displayVarList(mainNode->varList);
        mainNode = mainNode->next;
    }
}

int listDeep(t_scopeList *mainScopeNode)
{
    int i = 0;

    if (mainScopeNode == NULL)
        return (0);
    while (mainScopeNode->deep != NULL)
    {
        mainScopeNode = mainScopeNode->deep;
        i++;
    }
    return (i);
}

t_scopeList *addVarAtPosition(t_scopeList *mainScopeNode, int n, int d, t_var *new_var, int len)
{
    int i = 0;
    int deep;

    while (i < n)
    {
        mainScopeNode = mainScopeNode->next;
        i++;
    }

    deep = listDeep(mainScopeNode);
    printf("%d\n", deep);


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