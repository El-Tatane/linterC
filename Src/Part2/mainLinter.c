#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "prototypes.h"
#include "rules.h"
#include "list.h"

char currentFile[2048];

void displayErrorMessage(char *rule, unsigned int row, unsigned int column)
{
    printf("Error on %s , rule : %s failed at line %d column %d \n", currentFile, rule, row, column);
}

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
        printf("%s\n", info->d_name);
        //if (//Dossier);
        if (isCFile(info->d_name) != -1 && listExist(excludeNode, info->d_name) == 0)
        {
            if ((fd = fopen(info->d_name, "r")) == NULL)
                return (-1);
            strcpy(currentFile, info->d_name);
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
    int lineNb = 0;

    while (fileContent != NULL)
    {
        if (rules.arrayBracketEol == 1)
            arrayBracketEol(fileContent->path, lineNb);
        if (rules.operatorsSpacing == 1)
            operatorsSpacing(fileContent->path, lineNb); // Gerer variable dans printf/scanf ex: %d
        if (rules.commaSpacing == 1)
            commaSpacing(fileContent->path, lineNb);
        if (rules.maxLineNumbers != 0)
            maxLineNumbers(fileContent->path, lineNb rules->maxLineNumbers);
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
        lineNb++;
    }
}