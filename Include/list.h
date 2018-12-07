#ifndef LIST_H_
#define LIST_H_

//USED FOR TO CREATE FILE STRUCTURE (WITH SCOPE)
typedef struct s_scopeList t_scopeList;

//USED TO STORE VARIABLES IN SCOPE LIST
typedef struct s_var       t_var;

//USED FOR EXTENDED/EXCLUDED FILES
typedef struct s_list      t_list;

struct s_list
{
    char *path;
    t_list *next;
};

struct s_tmpVar
{
    char *type;
    char *name;
    int isParam;
    int  foundAtLine;
}       t_tmpVar;

struct s_var
{
    char *type;
    char *name;
    int isParam;
    int  foundAtLine;
    t_var *next;
}; 

struct s_scopeList
{
    char *funcName;
    char *returnType;
    int  foundAtLine;
    t_scopeList *next;
    t_scopeList *deep;
    t_var *varList; // MAIN Node t_var list
};
#endif