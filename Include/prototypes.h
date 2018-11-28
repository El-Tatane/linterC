#ifndef PROTOTYPES_H_
#define PROTOTYPES_H_

#include "rules.h"
#include "list.h"

//extendLinkedList.C
unsigned int listExist(t_list *mainNode, char *str);
unsigned int listLength(t_list *mainNode);
t_list *initLinkedList(t_list *mainNode, char *value);
t_list *addNode(t_list *mainNode, char *value, int flag);
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

//Part2
int mainLinter(t_list *extendNode, t_list *excludeNode, t_rules rules);
t_list *readFileForLinter(FILE *fd, t_list *fileContent);
int launchPart2(t_list *fileContent, t_rules rules);

//basicRules
void arrayBracketEol(char *line, int rowNb);
/*
void operatorsSpacing(char *line, int rowNb);
void commaSpacing(char *line, int rowNb);
void indent(char *line);
void commentsHeader(char *line);
void maxLineNumbers(char *line, int );
void maxFileLineNumbers(char *line);
void noTrailingSpaces(char *line);
*/

#endif