#ifndef EXTEND_H_
#define EXTEND_H_

typedef struct s_extend t_extend;

struct s_extend
{
    char *path;
    t_extend *next;
};

#endif