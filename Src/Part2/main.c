#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

int main(int argc, const char  * argv[]){

    char path[] = "C:/Users/libergea/Desktop/text.c";
    int a = 300;
    int b = 35;

    arrayBracketEol(path); //OK
    operatorsSpacing(path); // Gerer variable dans printf/scanf ex: %d
    commaSpacing(path); // OK
    //indent(path); //-- KO --
    commentsHeader(path); //OK
    maxLineNumbers(path, a); //OK
    maxFileLineNumbers(path, b); //OK
    noTrailingSpaces(path); //OK

}
