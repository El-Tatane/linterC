#ifndef RULES_H_
#define RULES_H_

#include "list.h"

typedef struct s_tmpRule
{
    char    *nameInFile;
    char    *nameInStruct;
    int     value;
}               t_tmpRules;

typedef struct s_rules
{ 
    int arrayBracketEol;
    int operatorsSpacing;
    int commaSpacing;
    int indent;
    int commentsHeader;
    int maxLineNumbers;
    int maxFileLineNumbers;
    int noTrailingSpaces;
    int noMultiDeclaration;
    int unusedVariable;
    int undeclaredVariable;
    int noPrototype;
    int unusedFunction;
    int undeclaredFunction;
    int variableAssignmentType;
    int functionParametersType;
    int recursive;
}               t_rules;

typedef struct s_mode
{
    int flag;
    int (*func)(char *line, t_tmpRules *rules, t_list *mainNode, t_list *mainExcludeNode);
}               t_mode;

#endif