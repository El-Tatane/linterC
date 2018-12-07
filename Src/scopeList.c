#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototypes.h"
#include "list.h"

void displayScopeList(t_scopeList *mainNode)
{
     while (mainNode != NULL)
    {
        printf("Func name : %s Func type : %s \n", mainNode->funcName, mainNode->returnType);
        displayVarList(mainNode->varList);
        mainNode = mainNode->next;
    }
}



t_scopeList addVarAtPosition(t_scopeList mainScopeNode, int N, int D, t_var new_var)
{

}

t_scopeList *addLineScopeNode(t_scopeList *mainNode, char *funcName, char *type, t_var *vars)
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

    strcpy(newNode->funcName, funcName);
    strcpy(newNode->returnType, type);
    newNode->varList = vars;
    return (mainNode);
}

t_scopeList *initScopeList(t_scopeList *mainScopeNode, char *funcName, char *type, t_var *vars)
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
    return (mainScopeNode);
}