#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototypes.h"
#include "rules.h"



t_mode *retModeArray() {

    t_mode *keys;

    if ((keys = malloc(sizeof(t_mode) * 4)) == NULL)
        return (NULL);
    keys[0].flag = 0;
    keys[0].func = getExtend;
    keys[1].flag = 0;
    keys[1].func = getRule;
    keys[2].flag = 0;
    keys[2].func = getExclude;
    keys[3].flag = 0;
    keys[3].func = getRecursive;
    
    return (keys);
}

int getFlag(char *line, t_mode *keys) {
    if (strcmp(line, "=extends") == 0)
        keys[0].func(line); // 
    else if (strcmp(line, "=rules") == 0)
        keys[1].func(line);
    else if (strcmp(line, "=excludedFiles") == 0)
        keys[2].func(line);
    else if (strcmp(line, "=recursive") == 0)
        keys[3].func(line);
    //printf("%s\n", line);
}



int main(int ac, char **av) {
    
    FILE *fd;
    char *buff;
    size_t size;
    t_mode *keys;


    size = 256;

    if (ac != 2)
        return (-1);
    if ((buff = malloc(sizeof(char) * 256)) == NULL)
        return (-1);

    if ((fd = fopen(av[1], "r")) == NULL)
        return (-1);
    
    if ((keys = retModeArray()) == NULL)
        return (-1);
    while (getline(&buff, &size, fd) != -1)
    {   
        if (buff[strlen(buff) -1] == '\n')
        {
            buff[strlen(buff) -1] = '\0';
        }
        getFlag(buff, keys);
    }
}