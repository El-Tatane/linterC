#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototypes.h"
#include "scopeList.h"

int isFunctionChar(char c)
{
    printf("%c\n", c);
    if (c >= '0' && c <= '9' || c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z' || c == '_')
        return (1);
     printf("0\n");
    return (0);
}

char  *getFirstPart(char *str, char c, int *nbWord)
{
    char *ret;
    int i = 0;
    
    while (str[i] != c)
    {
        if (i == 0 && isFunctionChar(str[i]) == 1)
            *nbWord++;
        else if ((str[i - 1] == ' ' || str[i - 1] == '\t') && isFunctionChar(str[i]) == 1)  
            *nbWord++;
        i++;
    }
    if ((ret = malloc(sizeof(char) * i + 1)) == NULL)
        return (NULL);
    strncpy(ret, str, i);
    ret[i] = '\0';
    return (ret);
}

t_scopeList *createScopeList(t_list *fileContent, t_scopeList *mainScopeList)
{

    while (fileContent != NULL)
    {
        char tmpName[2048];
        char tmpType[2048];
        char firstPart[2048];
        int  nbWord = 0;
        if ((strchr(fileContent->path, '(') != NULL) && (strchr(fileContent->path, ')') != NULL)
         && (strchr(fileContent->path, ';') == NULL))
        {
            strcpy(firstPart, getFirstPart(fileContent->path, '(', &nbWord));
            printf("%s %d\n", firstPart, nbWord);
            if (nbWord == 2)
            {
                strcpy(tmpType, strtok(firstPart, " "));
                strcpy(tmpName, strtok(NULL, " "));
            }
            //printf("type : %s  name :%s\n", tmpType, tmpName);
        }
        fileContent = fileContent->next;
    }
    return (mainScopeList);
}