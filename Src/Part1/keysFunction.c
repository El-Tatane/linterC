#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rules.h"
#include "prototypes.h"
#include "list.h"

int getExtend(char *line, t_tmpRules *rules, t_list *mainExtendNode, t_list *mainExcludeNode) {
    (void)mainExcludeNode;

    if (line[0] == '\0')
        return (0);
    if (isLconfFile(line) == -1)
        return (-1);
    if ((mainExtendNode = addNode(mainExtendNode, line)) == NULL)
        return (-1);
    return (0);
}

int secureAtoi(char *str, int *nb)
{
    int idx;

    *nb = 0;
    idx = 0;
    while (str[idx] != '\0') {
        if (str[idx] < '0' || str[idx] > '9')
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
    return (0);
}

int getRule(char *line, t_tmpRules *rules, t_list *mainExtendNode, t_list *mainExcludeNode) {
    char **tmpBuff;
    char *buff;
    int idx = 0;
    
    (void)mainExtendNode;
    (void)mainExcludeNode;
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
    return (0);
}

int getExclude(char *line, t_tmpRules *rules, t_list *mainExtendNode, t_list *mainExcludeNode) {
    (void)mainExtendNode;

    if (line[0] == '\0')
        return (0);
    if (isCFile(line) == -1)
        return (-1);
    if ((mainExcludeNode = addNode(mainExcludeNode, line)) == NULL)
        return (-1);
    return (0);
}

int getRecursive(char *line, t_tmpRules *rules, t_list *mainExtendNode, t_list *mainExcludeNode) {
    (void)mainExtendNode;
    (void)mainExcludeNode;

    if  ((strcmp(line, "false")) == 0)
        rules[16].value = 0;
    else if ((strcmp(line, "true")) == 0)
        rules[16].value = 1;
    else
        return (-1);
    return (0);
}

int fillRuleStuct(t_tmpRules *tmpRules, t_rules *rules){

    
    for (int i = 0; i < 17; i++)
    {
        rules->arrayBraketEol = (strcmp( tmpRules[i].nameInFile,"array-bracket-eol") == 0) ? tmpRules[i].value : rules->arrayBraketEol ;
        rules->operatorsSpacing = (strcmp( tmpRules[i].nameInFile,"operators-spacing") == 0) ? tmpRules[i].value : rules->operatorsSpacing ;
        rules->commaSpacing = (strcmp( tmpRules[i].nameInFile,"comma-spacing") == 0) ? tmpRules[i].value : rules->commaSpacing ;
        rules->indent = (strcmp( tmpRules[i].nameInFile,"indent") == 0) ? tmpRules[i].value : rules->indent ;
        rules->commentsHeader = (strcmp( tmpRules[i].nameInFile,"comments-header") == 0) ? tmpRules[i].value : rules->commentsHeader ;
        rules->maxLineNumbers = (strcmp( tmpRules[i].nameInFile,"max-line-numbers") == 0) ? tmpRules[i].value : rules->maxLineNumbers ;
        rules->maxFileLineNumbers = (strcmp( tmpRules[i].nameInFile,"max-file-line-numbers") == 0) ? tmpRules[i].value : rules->maxFileLineNumbers ;
        rules->noTrailingSpaces = (strcmp( tmpRules[i].nameInFile,"no-trailing-spaces") == 0) ? tmpRules[i].value : rules->noTrailingSpaces ;
        rules->noMultiDeclaration = (strcmp( tmpRules[i].nameInFile,"no-multi-declaration") == 0) ? tmpRules[i].value : rules->noMultiDeclaration ;
        rules->unusedVariable = (strcmp( tmpRules[i].nameInFile,"unused-variable") == 0) ? tmpRules[i].value : rules->unusedVariable ;
        rules->undeclaredVariable = (strcmp( tmpRules[i].nameInFile,"undeclared-variable") == 0) ? tmpRules[i].value : rules->undeclaredVariable ;
        rules->noPrototype = (strcmp( tmpRules[i].nameInFile,"no-prototype") == 0) ? tmpRules[i].value : rules->noPrototype ;
        rules->unusedFunction = (strcmp( tmpRules[i].nameInFile,"unused-function") == 0) ? tmpRules[i].value : rules->unusedFunction ;
        rules->undeclaredFunction = (strcmp( tmpRules[i].nameInFile,"undeclared-function") == 0) ? tmpRules[i].value : rules->undeclaredFunction ;
        rules->variableAssignmentType  = (strcmp(tmpRules[i].nameInFile,"variable-assignment-type") == 0) ? tmpRules[i].value : rules->variableAssignmentType ;
        rules->functionParametersType  = (strcmp(tmpRules[i].nameInFile,"function-parameters-type") == 0) ? tmpRules[i].value : rules->functionParametersType ;
        rules->recursive = (strcmp( tmpRules[i].nameInFile,"recursive") == 0) ? tmpRules[i].value : rules->recursive ;
    }
    return 0;
}

int isCFile(char* nameFile){

    if( strstr(nameFile, ".c") )
        return 0;

    return -1;
}

int isLconfFile(char* nameFile){

    if( strstr(nameFile, ".lconf") )
        return 0;
    
    return -1;
}