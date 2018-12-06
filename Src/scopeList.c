#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototypes.h"
#include "list.h"

t_scopeList addVarAtPosition(t_scopeList mainScopeNode, int N, int D, t_var new_var)
{

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

// ARG
    mainScopeNode->varList = vars;
    return (mainScopeNode);
}