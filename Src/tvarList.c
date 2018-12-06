#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototypes.h"
#include "list.h"

void displayVarList(t_var *mainNode)
{
    while (mainNode != NULL)
    {
        printf("type : %s name : %s flag : %d\n", mainNode->type, mainNode->name, mainNode->isParam);
        mainNode = mainNode->next;
    }
}

t_var *initVarList(t_var *mainNode, char *type, char *name, int isParam)
{
    if ((mainNode = malloc(sizeof(t_var) * 1)) == NULL)
        return (NULL);
    if ((mainNode->type = malloc(sizeof(char) * strlen(type) + 1)) == NULL)
        return (NULL);
    if ((mainNode->name = malloc(sizeof(char) * strlen(name) + 1)) == NULL)
        return (NULL);
    strcpy(mainNode->type, type);
    strcpy(mainNode->name, name);
    mainNode->isParam = isParam;
    mainNode->next = NULL;
    return (mainNode);
}

t_var *addVarNode(t_var *mainNode, char *type, char *name, int isParam)
{
    t_var *newNode;
    t_var *location;

    location = mainNode;

    if ((newNode = malloc(sizeof(t_var) * 1)) == NULL)
        return (NULL);
    if ((mainNode->type = malloc(sizeof(char) * strlen(type) + 1)) == NULL)
        return (NULL);
    if ((mainNode->name = malloc(sizeof(char) * strlen(name) + 1)) == NULL)
        return (NULL);
    while (location->next != NULL)
        location = location->next;

    newNode->next = NULL;
    location->next = newNode;
    strcpy(newNode->type, type);
    strcpy(newNode->name, name);
    newNode->isParam = isParam;
    return (mainNode);
}