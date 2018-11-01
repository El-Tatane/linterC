#ifndef PROTOTYPES_H_
#define PROTOTYPES_H_

#include "rules.h"

//KEYFUNCTION.C
int fillTmpRules(t_tmpRules *rules, char **tmpBuff);
int getExtend(char *line, t_tmpRules *rules);
int getRule(char *line, t_tmpRules *rules);
int getExclude(char *line, t_tmpRules *rules);
int getRecursive(char *line, t_tmpRules *rules);

//MAIN.C
int getKey(char *line, t_mode *keys, int *currentKey);

#endif