#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rules.h"
#include "prototypes.h"
#include "list.h"

int getExtend(char *line, t_tmpRules *rules, t_list *mainExtendNode, t_list *mainExcludeNode)
{
    (void)mainExcludeNode;

    if (line[0] == '\0')
    {
        return (0);
    }
    if (isLconfFile(line) == -1)
    {
        return (-1);
    }
    if ((mainExtendNode = addNode(mainExtendNode, line, 0)) == NULL)
    {
        return (-1);
    }
    return (0);
}

int secureAtoi(char *str, int *nb)
{
int idx;

    *nb = 0;
    idx = 0;
    while (str[idx] != '\0')
    {
        if (str[idx] < '0' || str[idx] > '9')
        {
            return (-1);
        }
        idx++;
    }
    *nb = atoi(str);
    return (0);
}
