#ifndef PROTOTYPES_H_
#define PROTOTYPES_H_

#include "rules.h"
#include "extend.h"

//extendLinkedList.C
unsigned int listExist(t_extend *mainNode, char *str);
unsigned int listLength(t_extend *mainNode);
t_extend *initLinkedList(t_extend *mainNode, char *value);
t_extend *addNode(t_extend *mainNode, char *value);

//KeyFunctions.C
int fillTmpRules(t_tmpRules *rules, char **tmpBuff);
int getExtend(char *line, t_tmpRules *rules);
int getRule(char *line, t_tmpRules *rules);
int getExclude(char *line, t_tmpRules *rules);
int getRecursive(char *line, t_tmpRules *rules);

//Main.C
int getKey(char *line, t_mode *keys, int *currentKey);

#endif