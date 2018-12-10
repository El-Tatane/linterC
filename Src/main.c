#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototypes.h"
#include "rules.h"
#include "list.h"

void print_rules(t_tmpRules *tmp) {
    int i;

    i = 0;
    while (i < 17)
    {
        printf("%s : %d\n", tmp[i].nameInFile, tmp[i].value);
        i++;
    }
}

void print_final_rules(t_list *extendMainNode, t_list *excludeMainNode, t_rules rules)
{
    printf("arrayBracketEol : %d\n", rules.arrayBracketEol);
    printf("operatorsSpacing : %d\n", rules.operatorsSpacing);
    printf("commaSpacing : %d\n", rules.commaSpacing);
    printf("indent : %d\n", rules.indent);
    printf("commentsHeader : %d\n", rules.commentsHeader);
    printf("maxLineNumbers : %d\n", rules.maxLineNumbers);
    printf("maxFileLineNumbers : %d\n", rules.maxFileLineNumbers);
    printf("noTrailingSpaces : %d\n", rules.noTrailingSpaces);
    printf("noMultiDeclaration : %d\n", rules.noMultiDeclaration);
    printf("unusedVariable : %d\n", rules.unusedVariable);
    printf("undeclaredVariable : %d\n", rules.undeclaredVariable);
    printf("noPrototype : %d\n", rules.noPrototype);
    printf("unusedFunction : %d\n", rules.unusedFunction);
    printf("undeclaredFunction : %d\n", rules.undeclaredFunction);
    printf("variableAssignmentType : %d\n", rules.variableAssignmentType);
    printf("functionParametersType : %d\n", rules.functionParametersType);
    printf("recursive : %d\n", rules.recursive);
    displayList(extendMainNode);
    displayList(excludeMainNode);

}

t_mode *initModeArray() {

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

int getKey(char *line, t_mode *keys, int *currentKey) {
    if (strcmp(line, "=extends") == 0) {
        if (keys[0].flag == 1)
            return (-1);
        keys[0].flag = 1;
        *currentKey = 0;
        return (2);
    }
    else if (strcmp(line, "=rules") == 0) {
        if (keys[1].flag == 1)
            return (-1);
        keys[1].flag = 1;
        *currentKey = 1;
        return (2);
    }
    else if (strcmp(line, "=excludedFiles") == 0) {
        if (keys[2].flag == 1)
            return (-1);
        keys[2].flag = 1;
        *currentKey = 2;
        return (2);
    }
    else if (strcmp(line, "=recursive") == 0) {
        if (keys[3].flag == 1)
            return (-1);
        keys[3].flag = 1;
        *currentKey = 3;
        return (2);
    }
    return (0);
}

t_tmpRules *initTmpRulesArray() {
    t_tmpRules *tmpRules;
    int        idx; 

    idx = 0;
    if ((tmpRules = malloc(sizeof(t_tmpRules) * 17)) == NULL)
        return (NULL);
    while (idx < 17){
        if ((tmpRules[idx].nameInFile = malloc(sizeof(char) * 50)) == NULL)
            return (NULL);
        if ((tmpRules[idx].nameInStruct = malloc(sizeof(char) * 50)) == NULL)
            return (NULL);
        tmpRules[idx].value = 0;
        idx++;
    }

    strcpy(tmpRules[0].nameInFile, "array-Bracket-eol");
    strcpy(tmpRules[0].nameInStruct, "arrayBracketEol");
    strcpy(tmpRules[1].nameInFile, "operators-spacing");
    strcpy(tmpRules[1].nameInStruct, "operatorsSpacing");
    strcpy(tmpRules[2].nameInFile, "comma-spacing");
    strcpy(tmpRules[2].nameInStruct, "commaSpacing");
    strcpy(tmpRules[3].nameInFile, "indent");
    strcpy(tmpRules[3].nameInStruct, "indent");
    strcpy(tmpRules[4].nameInFile, "comments-header");
    strcpy(tmpRules[4].nameInStruct, "commentsHeader");
    strcpy(tmpRules[5].nameInFile, "max-line-numbers");
    strcpy(tmpRules[5].nameInStruct, "maxLineNumbers");
    strcpy(tmpRules[6].nameInFile, "max-file-line-numbers");
    strcpy(tmpRules[6].nameInStruct, "maxFileLineNumbers");
    strcpy(tmpRules[7].nameInFile, "no-trailing-spaces");
    strcpy(tmpRules[7].nameInStruct, "noTrailingSpaces");  
    strcpy(tmpRules[8].nameInFile, "no-multi-declaration");
    strcpy(tmpRules[8].nameInStruct, "noMultiDeclaration");
    strcpy(tmpRules[9].nameInFile, "unused-variable");
    strcpy(tmpRules[9].nameInStruct, "unusedVariable");
    strcpy(tmpRules[10].nameInFile, "no-prototype");
    strcpy(tmpRules[10].nameInStruct, "noPrototype");
    strcpy(tmpRules[11].nameInFile, "unused-function");
    strcpy(tmpRules[11].nameInStruct, "unusedFunction");
    strcpy(tmpRules[12].nameInFile, "undeclared-function");
    strcpy(tmpRules[12].nameInStruct, "undeclaredFunction");
    strcpy(tmpRules[13].nameInFile, "variable-assignment-type");
    strcpy(tmpRules[13].nameInStruct, "variableAssignmentType");
    strcpy(tmpRules[14].nameInFile, "undeclared-variable");
    strcpy(tmpRules[14].nameInStruct, "undeclaredVariable");
    strcpy(tmpRules[15].nameInFile, "function-parameters-type");
    strcpy(tmpRules[15].nameInStruct, "functionParametersType");
    strcpy(tmpRules[16].nameInFile, "recursive");
    strcpy(tmpRules[16].nameInStruct, "recursive");
    return (tmpRules); 
}

int getDataFromFile(char *filepath, t_mode *keys, t_tmpRules *tmpRulesList, t_list *extendMainNode, t_list *excludeMainNode)
{
    char *buff;
    size_t size;
    int ret;
    int currentKey;
    FILE *fd;
    currentKey = -1;
    size = 256;

    if ((fd = fopen(filepath, "r")) == NULL)
    {
        return (-1);  
    }
    if ((buff = malloc(sizeof(char) * 256)) == NULL)
        return (-1);
    while (getline(&buff, &size, fd) != -1)
    {
        if (buff[strlen(buff) - 1] == '\n')
            buff[strlen(buff) - 1] = '\0';
        if ((ret = getKey(buff, keys, &currentKey)) == -1)
            return (-1);
        if (ret != 2 && currentKey != -1)
        {
            if ((keys[currentKey].func(buff, tmpRulesList, extendMainNode, excludeMainNode)) == -1)
                return (-1);
        }
    }
    return (0);
}


int main(int ac, char **av) { 
    t_mode *keys;
    t_tmpRules *tmpRulesList;
    t_rules rules;
    t_list *extendMainNode;
    t_list *excludeMainNode;
    t_list *tmpNode;
    
    
    excludeMainNode = NULL;
    if (ac != 2)
        return (-1);

    if ((extendMainNode = initLinkedList(extendMainNode, av[1])) == NULL)
        return (-1);
    if ((excludeMainNode = initLinkedList(excludeMainNode, "LINTER_EXCLUDE")) == NULL)
        return (-1);
    if ((keys = initModeArray()) == NULL)
        return (-1);
    if ((tmpRulesList = initTmpRulesArray()) == NULL)
        return (-1);
    tmpNode = extendMainNode;
    while (tmpNode != NULL)
    {
        if ((getDataFromFile(tmpNode->path, keys, tmpRulesList, extendMainNode, excludeMainNode)) == -1)
            return (-1);
        keys[0].flag = 0;
        keys[1].flag = 0;
        keys[2].flag = 0;
        keys[3].flag = 0;
        tmpNode = tmpNode->next;
    }
    fillRuleStuct(tmpRulesList, &rules);
    mainLinter(extendMainNode, excludeMainNode, rules, ".");
    if (keys != NULL)
        free(keys);
    if (tmpRulesList != NULL)
        free(tmpRulesList);
    if (extendMainNode != NULL)
        free(extendMainNode);
    if (excludeMainNode != NULL)
        free(excludeMainNode);
    if (tmpNode != NULL)
        free(tmpNode);

    return (0);
}