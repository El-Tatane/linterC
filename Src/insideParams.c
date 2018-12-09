#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "prototypes.h"
#include "list.h"

// t_var *getInsidePointerParam(t_var *mainNode, char *part, int len) // get pointer param
// {
//     char *noSpace;
//     char *tmpType;

//     if ((noSpace = removeSpaces(part)) == NULL)
//         return (NULL);

//     char *lastPart;

//     if ((lastPart = getLastPart(noSpace, '*')) == NULL)
//         return (NULL);
//     if ((tmpType = malloc(sizeof(char) * (strlen(noSpace) - strlen(lastPart + 1)) + 1)) == NULL)
//         return (NULL);
//     strncpy(tmpType, noSpace, (strlen(noSpace) - strlen(lastPart + 1)));
//     tmpType[strlen(noSpace) - strlen(lastPart + 1)] = '\0';
//     if (mainNode == NULL)
//     {
//         if (((mainNode = initVarList(mainNode, tmpType, lastPart + 1, 1, len))) == NULL)
//             return (NULL);
//     }
//     else
//     {
//         if (((mainNode = addVarNode(mainNode, tmpType, lastPart + 1, 1, len))) == NULL)
//             return (NULL);
//     }
//     return (mainNode);
// }

t_var *getMultipleParams(t_var *mainNode, char *line)
{

}

t_var *getInsideParams(char *line, int len)
{
    t_var *newVarList = NULL;
    if (strchr(line, ',') == NULL)
    {
       if ((newVarList = getOneParam(newVarList, line, len, 0)) == NULL)
            return (NULL); 
    }
    else if (strchr(line, ',') == NULL)
    {
        //getMultipleParams(t_var *mainNode, line);
    }
    return (newVarList);
}