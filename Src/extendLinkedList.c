#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "extend.h"

void displayList(t_extend *mainNode)
{
    while (mainNode != NULL)
    {
        printf("NODE %s\n", mainNode->path);
        mainNode = mainNode->next;
    }
}

unsigned int listExist(t_extend *mainNode, char *str)
{
    while (mainNode->next != NULL)
    {
        if ((strcmp(mainNode->path, str)) == 0)
            return (1);
        mainNode = mainNode->next;
    }
    return (0);
} 

unsigned int listLength(t_extend *mainNode)
{
    int i = 0;
    while (mainNode->next != NULL)
    {
        i++;
        mainNode = mainNode->next;
    }
    return (i);
} 

t_extend *initLinkedList(t_extend *mainNode, char *value)
{
    if ((mainNode = malloc(sizeof(t_extend) * 1)) == NULL)
        return (NULL);
    if ((mainNode->path = malloc(sizeof(char) * strlen(value) + 1)) == NULL)
        return (NULL);
    mainNode->next = NULL;
    strcpy(mainNode->path, value);
    return (mainNode);
}

t_extend *addNode(t_extend *mainNode, char *value)
{
    t_extend *newNode;
    t_extend *location;

    location = mainNode;
    if ((listExist(mainNode, value)) == 1)
        return (NULL);
    if ((newNode = malloc(sizeof(t_extend) * 1)) == NULL)
        return (NULL);
    if ((newNode->path = malloc(sizeof(char) * strlen(value) + 1)) == NULL)
        return (NULL);
    while (location->next != NULL)
        location = location->next;
    newNode->next = NULL;
    strcpy(newNode->path, value);
    location->next = newNode;
    
    return (mainNode);
}