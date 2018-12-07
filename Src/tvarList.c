#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototypes.h"
#include "list.h"

void displayVarList(t_var *mainNode)
{
    while (mainNode != NULL)
    {
        //printf("TYPE %s|\n", mainNode->type);
        //printf("%s|\n", mainNode->name);
        //printf("FLAG %d|\n", mainNode->isParam);
        //printf("LINE %d|\n", mainNode->foundAtLine);
        mainNode = mainNode->next;
    }
}

t_var *initVarList(t_var *mainNode, char *type, char *name, int isParam, int len)
{
    printf("E%sE\n", name);
    if ((mainNode = malloc(sizeof(t_var) * 1)) == NULL)
        return (NULL);
    if ((mainNode->type = malloc(sizeof(char) * strlen(type) + 1)) == NULL)
        return (NULL);
    if ((mainNode->name = malloc(sizeof(char) * strlen(name) + 1)) == NULL)
        return (NULL);
    strcpy(mainNode->type, type);
    //printf("TEST 1%s\n", mainNode->type);
    strcpy(mainNode->name, name);
    mainNode->isParam = isParam;
    mainNode->foundAtLine = len;
    mainNode->next = NULL;
    //displayVarList(mainNode);
    return (mainNode);
}

t_var *addVarNode(t_var *mainNode, char *type, char *name, int isParam, int len)
{
    t_var *newNode;
    t_var *location;

    location = mainNode;

    if ((newNode = malloc(sizeof(t_var) * 1)) == NULL)
        return (NULL);
    if ((newNode->type = malloc(sizeof(char) * strlen(type) + 1)) == NULL)
        return (NULL);
    if ((newNode->name = malloc(sizeof(char) * strlen(name) + 1)) == NULL)
        return (NULL);
    while (location->next != NULL)
        location = location->next;

    newNode->next = NULL;
    location->next = newNode;
    strcpy(newNode->type, type);
    strcpy(newNode->name, name);
    newNode->isParam = isParam;
    newNode->foundAtLine = len;
    return (mainNode);
}