#include <stdio.h>
#include "prototypes.h"

void maxFileLineNumbers(t_list *fileContent, int max)
{
    if (listLength(fileContent) >= max)
    {
        displayErrorMessage("maxFileLineNumbers", -1, -1);
    }
}

void indent(char *line, int size, int lineNb, int d)
{
    int i = 0;
    int space = 0;
    int tab = 0;

    while (line[i] != '\0')
    {
        if (line[i] != '\t' && line[i] != ' ')
            break;
        if (line[i] == ' ')
            space++;
        if (line[i] == '\t');
            tab++;
        i++;
    }
    if ((space * 4  + tab != size * d))
        displayErrorMessage("indent", lineNb, -1); 
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