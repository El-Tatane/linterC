#include <stdio.h>
#include "prototypes.h"

void maxFileLineNumbers(t_list *fileContent, int max)
{
    if (listLength(fileContent) >= max)
    {
        displayErrorMessage("maxFileLineNumbers", -1, -1);
    }
}

void commentsHeader(t_list *fileContent)
{

    int nb = 0;
    while (fileContent != NULL)
    {    
        int i = 0;
        while (fileContent->path[i] != '\0')
        {
            if (fileContent->path[i] == ' ' || fileContent->path[i] == '\t' || fileContent->path[i] == '\r')
                i++;
            else if (fileContent->path[i] == '/' && fileContent->path[i + 1] == '*')
                return;
            else if (fileContent->path[i] == '/' && fileContent->path[i + 1] == '/')
            { 
                nb++; 
                if (nb >= 2)
                    return;
                break;
            }
            else
            {
                displayErrorMessage("commentsHeader", -1, -1); 
                return;
            }
        }
        fileContent = fileContent->next;
    }
}