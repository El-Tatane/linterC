#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rules.h"

int getExtend(char *line, t_tmpRules *rules) {
    printf("0\n");
    return (0);
}

int getRule(char *line, t_tmpRules *rules) {
    char **tmpBuff;
    char *buff;
    int idx = 0;
    
    if ((tmpBuff = malloc(sizeof(char *) * 5)) == NULL)
        return (-1);
    while (idx < 5)
    {
        if ((tmpBuff[idx] = malloc(sizeof(char) * 50)) == NULL)
            return (-1);
        idx++;
    }

    printf("%s\n", line);
    buff = strtok(line, " ");
    if (buff == NULL)
        return 0;

    strcpy(tmpBuff[0], buff);
    printf("%s\n\n", tmpBuff[0]);
    idx = 1;
    while ((tmpBuff[idx] = strtok(NULL, " ")) != NULL)
    {
        idx++;
        if (idx == 6)
            return (-1);   
    }
    if (tmpBuff[0][0] != '-')
       return (0);

    idx = 0;

     while (idx < 16)
    {
        if ((strcmp(rules[idx].nameInFile, tmpBuff[1])) == 0)
        {
            if ((strcmp(tmpBuff[3], "on")) == 0)
                rules[idx].value = 1;
            else if ((strcmp(tmpBuff[3], "off")) == 0)
                rules[idx].value = 0;
            else
                rules[idx].value = atoi(tmpBuff[3]); // check atoi
        }
        idx++;
     }
    return (1);
}

int getExclude(char *line, t_tmpRules *rules) {
     printf("2\n");
    return (2);
}

int getRecursive(char *line, t_tmpRules *rules) {
     printf("3\n");
    return (3);
}