#ifndef PROTOTYPES_H_
#define PROTOTYPES_H_

#include "rules.h"
#include "list.h"

//extendLinkedList.C
unsigned int listExist(t_list *mainNode, char *str);
unsigned int listLength(t_list *mainNode);
t_list *initLinkedList(t_list *mainNode, char *value);
t_list *addNode(t_list *mainNode, char *value);
void displayList(t_list *mainNode);

//KeyFunctions.C
int fillTmpRules(t_tmpRules *rules, char **tmpBuff);
int getExtend(char *line, t_tmpRules *rules, t_list *mainNode, t_list *mainExcludeNode);
int getRule(char *line, t_tmpRules *rules, t_list *mainNode, t_list *mainExcludeNode);
int getExclude(char *line, t_tmpRules *rules, t_list *mainNode, t_list *mainExcludeNode);
int getRecursive(char *line, t_tmpRules *rules, t_list *mainNode, t_list *mainExcludeNode);
int fillRuleStuct(t_tmpRules *tmpRules, t_rules *rules);
int isCFile(char* nameFile);
int isLconfFile(char* nameFile);

//Main.C
int getKey(char *line, t_mode *keys, int *currentKey);

#endif