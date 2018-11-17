#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "prototypes.h"
#include "rules.h"
#include "list.h"

int mainLinter(t_list *extendNode, t_list *excludeNode, t_rules rules)
{
    DIR *dir;
    struct dirent *info;
    //OPENDIR .
    if ((dir = opendir(".")) == NULL)
        return (-1);
    
    while ((info = readdir(dir)) != NULL)
    {
        printf("%s\n", info->d_name);
        if (isCFile(info->d_name) != -1 && listExist(excludeNode, info->d_name) == 0)
        {
            //LINTER SUR LE FICHIER
        }
    }
    return (0);
}

int readFileForLinter() {
    
}