#ifndef SCOPE_LIST_H_
#define SCOPE_LIST_H_

typedef struct s_scopeList t_scopeList;

typedef struct s_var
{
    char *type;
    char *name;
    int isParam;
} t_var;

struct s_scopeList
{
    char *funcName;
    char *returnType;
    t_scopeList *next;
    t_scopeList *deep;
    t_var *varList;
};

#endif