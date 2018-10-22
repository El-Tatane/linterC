#ifndef RULES_H_
#define RULES_H_

typedef struct s_rules
{ 
    int arrayBraketEol;
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
}               t_rules;

typedef struct s_mode
{
    int flag;
    int (*func)(char *line);
}               t_mode;

#endif