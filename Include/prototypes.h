#ifndef PROTOTYPES_H_
#define PROTOTYPES_H_

#include "rules.h"
#include "list.h"

extern char currentFile[2048];
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


void displayErrorMessage(char *rule, unsigned int row, unsigned int column);
int mainLinter(t_list *extendNode, t_list *excludeNode, t_rules rules);
t_list *readFileForLinter(FILE *fd, t_list *fileContent);
int launchSingleLineRules(t_list *fileContent, t_rules rules);

//basicRules
void arrayBracketEol(char *line, int rowNb);
void operatorsSpacing(char *line, int rowNb);
void commaSpacing(char *line, int rowNb);
//void indent(char *line);
void maxLineNumbers(char *line, int rowNb, int max);
void noTrailingSpaces(char *line, int rowNb);
void noMultiDeclaration(char *line, int rowNb);

//void commentsHeader(char *line);

//void maxLineNumbers(char *line, int rowNb, int max);

//void maxFileLineNumbers(char *line);

//Part3

#endif