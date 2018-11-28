#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "prototypes.h"
#include "rules.h"
#include "list.h"

int mainLinter(t_list *extendNode, t_list *excludeNode, t_rules rules)
{
    FILE *fd;
    DIR *dir;
    struct dirent *info;
    t_list *fileContent;
    //OPENDIR .
    if ((dir = opendir(".")) == NULL)
        return (-1);
    
    while ((info = readdir(dir)) != NULL)
    {
        //printf("%s\n", info->d_name);
        //if (//Dossier);
        if (isCFile(info->d_name) != -1 && listExist(excludeNode, info->d_name) == 0)
        {
            if ((fd = fopen(info->d_name, "r")) == NULL)
                return (-1);
            if ((fileContent = readFileForLinter(fd, fileContent)) == NULL)
                return (-1);
            launchPart2(fileContent, rules);
            //utiliser la liste
            //free la liste
            if ((fclose(fd)) == -1)
                return (-1);
        }
    }
    return (0);
}

t_list *readFileForLinter(FILE *fd, t_list *fileContent) {
    char *buff = NULL;
    size_t size;
    int flag;
    char finalBuff[4096];

    flag = 0;
    size = 4096;
    while ((getline(&buff, &size, fd)) != -1)
    {
        if (strlen(buff) > 1)
        {
            strncpy(finalBuff, buff, strlen(buff) -1);
            finalBuff[strlen(buff) -1] = '\0';
        }
        else
        {
           strcpy(finalBuff, buff); 
        }
        if (flag == 0)
        {
            if ((fileContent = initLinkedList(fileContent, finalBuff)) == NULL)
                return (NULL);
            flag = 1;
        }
        else
        {
            if ((fileContent = addNode(fileContent, finalBuff, 2)) == NULL)
                return (NULL);
        }
    }
    return (fileContent);
}

int launchPart2(t_list *fileContent, t_rules rules)
{
    int line = 0;

    while (fileContent != NULL)
    {
        if (rules.arrayBracketEol == 1)
            arrayBracketEol(fileContent->path, line);
        //if (rules->operatorsSpacing == 1)
           // operatorsSpacing(fileContent->path); // Gerer variable dans printf/scanf ex: %d
        //if (rules->commaSpacing == 1)
          //  commaSpacing(fileContent->path); // OK
        //if (rules->commentsHeader == 1)
          //  commentsHeader(fileContent->path);
        /*if (rules->maxLineNumbers != 0)
            maxLineNumbers(fileContent->path, rules->maxLineNumbers);
        if (rules->maxFileLineNumbers != 0)
            maxFileLineNumbers(fileContent->path, rules->maxFileLineNumbers); //OK
        if (rules->noTrailingSpaces == 1)
            noTrailingSpaces(fileContent->path); //OK
        */
        fileContent = fileContent->next;
        line++;
    }
}