#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototypes.h"
#include "list.h"

int isFunctionChar(char c)
{  
    if (c >= '0' && c <= '9' || c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z' || c == '_')
    {
        printf("%c  1\n", c);
        return (1);
    }
    else
    {
        printf("%c  0\n", c);
    }
    return (0);
}


char  *getFirstPart(char *str, char c, int *nbWord)
{
    char *ret;
    int i = 0;
    
    while (str[i] != c)
    {
        if (i == 0 && isFunctionChar(str[i]) == 1)
            (*nbWord)++;
        else if (isFunctionChar(str[i]) == 1 && (str[i - 1] == ' ' || str[i - 1] == '\t'))  
            (*nbWord)++;
        i++;
    }
    if ((ret = malloc(sizeof(char) * i + 1)) == NULL)
        return (NULL);
    strncpy(ret, str, i);
    ret[i] = '\0';
    return (ret);
}

t_var *getFuncParams(char *line)
{
    int nb;
    char part[2048];
    t_var *newVarList = NULL;
    char *tmpType;
    char *tmpName;
    strcpy(part, getFirstPart(strchr(line, '('), ')', &nb));

    while ()
    if (nb == 2)
    {
        if ((tmpType = strdup(strtok(part, " "))) == NULL)
            return (NULL);
        if ((tmpName = strdup(strtok(NULL, " "))) == NULL)
            return (NULL);
        if (newVarList == NULL)
        {
            if ((newVarList = initVarList(newVarList, tmpType, tmpName, 1)) == NULL)
                return (NULL);
        }
        else
        {
            if ((newVarList = addVarList(newVarList, tmpType, tmpName, 1)) == NULL)
                return (NULL);
        }
    }

    return (newVarList);
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
            if (nbWord == 2)
            {
                strcpy(tmpType, strtok(firstPart, " "));
                strcpy(tmpName, strtok(NULL, " "));
                getFuncParams(fileContent->path); // FUNC
                if (mainScopeList == NULL)
                    mainScopeList = initScopeList(mainScopeList, tmpName, tmpType, var);
            }
            
        }
        fileContent = fileContent->next;
    }
    return (mainScopeList);
}

int main()