#ifndef LIST_H_
#define LIST_H_

typedef struct s_list t_list;

struct s_list
{
    char *path;
    t_list *next;
};

#endif