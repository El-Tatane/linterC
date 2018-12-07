#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "prototypes.h"
#include "list.h"

// t_var *getNotPointerParam(t_var *mainNode, char *part, int len) //Get a not pointer param
// {
//     int i;
//     int n;
//     int j;
//     char *type;
//     char *name;

//     i = strlen(part);
//     while (i > 0)
//     {
//         if ((part[i] != ' ' && part[i] != '\t' && part[i] != ';'))
//         {
//             if ((name = getLastWord(part, i)) == NULL)
//                 return (NULL);
//             break;
//         }
//         i--;
//     }
//     n = 0;
//     j = 0;
//     int strLen = strlen(part) - ((strlen(name) + strlen(part + i)));
//     if ((type = malloc(sizeof(char) * (strLen + 1))) == NULL)
//         return (NULL);
//     while (j < strLen)
//     {
//         if ((part[j] != ' ' && part[j] != '\t'))
//         {
//             type[n] = part[j];
//             n++;
//         }
//         j++;
//     }
//     type[n] = '\0';

//     printf("%s %s\n", type, name);
//     if (mainNode == NULL)
//     {
//         if (((mainNode = initVarList(mainNode, type, name, 1, len))) == NULL)
//             return (NULL);
//     }
//     else
//     {
//         if (((mainNode = addVarNode(mainNode, type, name, 1, len))) == NULL)
//             return (NULL);
//     }
//     return (mainNode);
// }

t_var *getInsidePointerParam(t_var *mainNode, char *part, int len) // get pointer param
{
    char *noSpace;
    char *tmpType;

    if ((noSpace = removeSpaces(part)) == NULL)
        return (NULL);

    char *lastPart;

    if ((lastPart = getLastPart(noSpace, '*')) == NULL)
        return (NULL);
    if ((tmpType = malloc(sizeof(char) * (strlen(noSpace) - strlen(lastPart + 1)) + 1)) == NULL)
        return (NULL);
    strncpy(tmpType, noSpace, (strlen(noSpace) - strlen(lastPart + 1)));
    tmpType[strlen(noSpace) - strlen(lastPart + 1)] = '\0';
    if (mainNode == NULL)
    {
        if (((mainNode = initVarList(mainNode, tmpType, lastPart + 1, 1, len))) == NULL)
            return (NULL);
    }
    else
    {
        if (((mainNode = addVarNode(mainNode, tmpType, lastPart + 1, 1, len))) == NULL)
            return (NULL);
    }
    return (mainNode);
}


t_var *getInsideOneParam(t_var *mainNode, char *part, int len) // Get One Func Param
{
    char *noSpace;
    char *tmpType;

    if ((strchr(part, '*')) != NULL)
    {
        if ((mainNode = getInsidePointerParam(mainNode, part, len)) == NULL)
            return (NULL);
    }
    // else
    // {
    //     if ((mainNode = getInsideNotPointerParam(mainNode, part, len)) == NULL)
    //         return (NULL);
    // }
    return (mainNode);
}

t_var *getInsideParams(char *line, int len)
{
    t_var *newVarList = NULL;
    if (strchr(line, ',') == NULL)
    {
       if ((newVarList = getInsideOneParam(newVarList, line, len)) == NULL)
            return (NULL); 
    }
    displayVarList(newVarList);
    return (newVarList);
}