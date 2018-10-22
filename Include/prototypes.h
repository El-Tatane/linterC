#ifndef PROTOTYPES_H_
#define PROTOTYPES_H_

#include "rules.h"

int getExtend(char *file);
int getRule(char *file);
int getExclude(char *file);
int getRecursive(char *file);
int getFlag(char *line, t_mode *keys);

#endif