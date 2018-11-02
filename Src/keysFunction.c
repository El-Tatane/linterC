#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rules.h"
#include "extend.h"

int getExtend(char *line, t_tmpRules *rules, t_extend *mainNode) {
    printf("%s\n", line);
    addNode(mainNode, line);
    return (0);
}

int secureAtoi(char *str, int *nb)
{
    int idx;

    *nb = 0;
    idx = 0;
    while (str[idx] != '\0') {
        if (str[idx] < '0' && str[idx] > '9')
            return (-1);
        idx++;
    }
    *nb = atoi(str);
    return (0);
}

int fillTmpRules(t_tmpRules *rules, char **tmpBuff)
{
    int idx;
    int nb;
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
            {   
                if ((secureAtoi(tmpBuff[3], &nb)) != -1)
                    rules[idx].value = nb;
                else
                    return (-1);
            }
        }
        idx++;
     }
}

int getRule(char *line, t_tmpRules *rules, t_extend *mainNode) {
    char **tmpBuff;
    char *buff;
    int idx = 0;
    
    (void)mainNode;
    if ((tmpBuff = malloc(sizeof(char *) * 5)) == NULL)
        return (-1);
    while (idx < 5) {
        if ((tmpBuff[idx] = malloc(sizeof(char) * 50)) == NULL)
            return (-1);
        idx++;
    }
    if ((buff = strtok(line, " ")) == NULL)
        return (0);
    strcpy(tmpBuff[0], buff);
    idx = 1;
    while ((tmpBuff[idx] = strtok(NULL, " ")) != NULL) {
        idx++;
        if (idx == 5)
            return (-1);   
    }
    if (tmpBuff[0][0] != '-')
       return (0);
    if (idx != 4)
        return (-1);
    if ((fillTmpRules(rules, tmpBuff)) == -1)
        return (-1);
    return (1);
}

int getExclude(char *line, t_tmpRules *rules, t_extend *mainNode) {
     printf("2\n");
    (void)mainNode;
    return (2);
}

int getRecursive(char *line, t_tmpRules *rules, t_extend *mainNode) {
     printf("3\n");
    (void)mainNode;
    return (3);
}