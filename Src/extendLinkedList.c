#include <stdlib.h>
#include <string.h>
#include "extend.h"

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
    if ((mainNode->path = malloc(sizeof(char) * strlen(value))) == NULL)
        return (NULL);
    mainNode->next = NULL;
    strcpy(mainNode->path, value);
    return (mainNode);
}

t_extend *addNode(t_extend *mainNode, char *value)
{
    t_extend *newNode;
    t_extend *location;

    if ((newNode = malloc(sizeof(t_extend) * 1)) == NULL)
        return (NULL);
    if ((newNode->path = malloc(sizeof(char) * strlen(value))) == NULL)
        return (NULL);
    while (location->next != NULL)
        location = location->next;
    location->next = newNode;
    newNode->next = NULL;
    strcpy(newNode->path, value);
    return (mainNode);
}