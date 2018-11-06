#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "list.h"

void displayList(t_list *mainNode)
{
    while (mainNode != NULL)
    {
        printf("NODE %s\n", mainNode->path);
        mainNode = mainNode->next;
    }
}

unsigned int listExist(t_list *mainNode, char *str)
{
    while (mainNode->next != NULL)
    {
        if ((strcmp(mainNode->path, str)) == 0)
            return (1);
        mainNode = mainNode->next;
    }
    return (0);
} 

unsigned int listLength(t_list *mainNode)
{
    int i = 0;
    
    if (mainNode == NULL)
        return (0);
    while (mainNode->next != NULL)
    {
        i++;
        mainNode = mainNode->next;
    }
    return (i);
} 

t_list *initLinkedList(t_list *mainNode, char *value)
{
    if ((mainNode = malloc(sizeof(t_list) * 1)) == NULL)
        return (NULL);
    if ((mainNode->path = malloc(sizeof(char) * strlen(value) + 1)) == NULL)
        return (NULL);
    mainNode->next = NULL;
    strcpy(mainNode->path, value);
    return (mainNode);
}

t_list *addNode(t_list *mainNode, char *value)
{
    t_list *newNode;
    t_list *location;

    location = mainNode;
    if ((listExist(mainNode, value)) == 1)
        return (NULL);
    if ((newNode = malloc(sizeof(t_list) * 1)) == NULL)
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